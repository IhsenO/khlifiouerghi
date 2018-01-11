#include <iostream>
#include <json/json.h>
#include <fstream>

#include <thread>

#include "state.h"
#include "Tests.hpp"
#include "engine.h"
#include "utils.hpp"
#include "server.h"

#include <sstream>
#include <microhttpd.h>
#include <string.h>

using namespace std;
using namespace state;
using namespace engine;
using namespace server;

//Ajout §§§§§§§


class Request {
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request() {
        if (pp) MHD_destroy_post_processor (pp);
    }
};

// Fonction pour gérer les données imporantes en upload (non implanté ici)
static int
post_iterator(void *cls,
        enum MHD_ValueKind kind,
        const char *key,
        const char *filename,
        const char *content_type,
        const char *transfer_encoding,
        const char *data, uint64_t off, size_t size) 
{
    return MHD_NO;
}

// Détruit les données d'une requête
static void
request_completed (void *cls, struct MHD_Connection *connection,
                   void **con_cls, enum MHD_RequestTerminationCode toe)
{
  Request *request = (Request*)*con_cls;
  if (request) {
      delete request;
      *con_cls = nullptr;
  }
}

// Gestionnaire principal
static int
main_handler (void *cls,      
          struct MHD_Connection *connection,
          const char *url, // 
          const char *method,
          const char *version,
          const char *upload_data, size_t *upload_data_size, void **ptr) 
{
    // Données pour une requête (en plusieurs appels à cette fonction)
    Request *request = (Request*)*ptr;

    // Premier appel pour cette requête
    if (!request) { 
        request = new Request();
        if (!request) {
            return MHD_NO;
        }
        *ptr = request;
        if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
         || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
            request->pp = MHD_create_post_processor(connection,1024,&post_iterator,request);
            if (!request->pp) {
                cerr << "Failed to setup post processor for " << url << endl;
                return MHD_NO;
            }
        }
        return MHD_YES;
    }    
    
    // Cas où il faut récupérer les données envoyés par l'utilisateur
    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0
     || strcmp(method, MHD_HTTP_METHOD_PUT) == 0) {
        MHD_post_process(request->pp,upload_data,*upload_data_size);
        if (*upload_data_size != 0) {
            request->data = upload_data;
            *upload_data_size = 0;
            return MHD_YES;
        }    
    }

    HttpStatus status;
    string response;
    try {

        ServicesManager *manager = (ServicesManager*) cls;
        status = manager->queryService(response,request->data,url,method);
    }
    catch(ServiceException& e) {
        status = e.status();
        response = e.what();
        response += "\n";
    }
    catch(exception& e) {
        status = HttpStatus::SERVER_ERROR;
        response = e.what();
        response += "\n";
    }
    catch(...) {
        status = HttpStatus::SERVER_ERROR;
        response = "Unknown exception\n";
    }

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response.size(),(void *)response.c_str(),MHD_RESPMEM_MUST_COPY);
    if (strcmp(method,MHD_HTTP_METHOD_GET) == 0) {
        MHD_add_response_header(mhd_response,"Content-Type","application/json; charset=utf-8");
    }
    int ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

void attenteJoueurs(int *stop){
    /*
    while(1){
        if(game.isFullOfPlayers() || stopped){
            return true;
        }
        usleep(1000);
    }
     */
    (void) getc(stdin);
    *stop = 1;
 
}

//FIN


int main(int argc,char* argv[]) 
{
    
    if (argc < 2) {
        menuServer();
        return 2;
    }

    string mode = argv[1];
    if (mode == "hello")
        cout << "Hello world !" << endl;
    
    else if(mode == "record"){
        
        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new state::Player("Joueur 1"));
        state.addPlayer(new state::Player("Joueur 2"));
        
        Engine e(state);
        
        state.setIdPlayer(1);
        
        stack<Action*> pile;
        
        AI *ai1;

        ai1 = new HeuristicAI(state, e);

        AI *ai2;
        ai2 = new RandomAI(state, e);
        
        cout << "Mode record !" << endl;
        cout << "Nous enregistrons des actions pendant un certain nombre de tours, et on le met dans un fichier JSON !" << endl;
        cout << "Ici on joue 80 fois ! On enregistre le fichier dans le dossier res, dans un un fichier appelé replay.json !" << endl;
               
        Json::Value listCommandSequence;
        
        int i = 0;
        
        while(i < 80){
            
            cout << i << endl;
            if(i % 2 == 0){
                state.setIdPlayer(1);
                ai1->run(e, pile, true);
                listCommandSequence.append(*(e.getValueJson()));
            }
            else{
                state.setIdPlayer(2);
                ai2->run(e, pile, true);
                listCommandSequence.append(*(e.getValueJson()));
            }            
            i++;
        }
        
        ofstream fichier("res/replay.json", ios::out|ios::trunc);
        if(fichier){
            fichier << listCommandSequence;
        }
        else cout << "Erreur " << endl;
        
        delete m;
    }
    
    else if(mode == "listen"){
        
        //cout << "Listenning !!!!" << endl;
        
        try {
        ServicesManager servicesManager;
        VersionService *vs = new VersionService();
        servicesManager.registerService(vs);
        
        Game game(2);
        PlayerService *ps = new PlayerService(game);
        servicesManager.registerService(ps);

        struct MHD_Daemon *d;
        if (argc != 2) {
            printf("%s PORT\n", argv[0]);
            return 1;
        }
        d = MHD_start_daemon(// MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
            MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
                // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
            4040,
            NULL, NULL, 
            &main_handler, (void*) &servicesManager,
            MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
            MHD_OPTION_END);
        if (d == NULL)
            return 1;
            int stop = 0; 
            //cout << "Pressez <entrée> pour arrêter le serveur" << endl;
            thread th(attenteJoueurs ,&stop);
            cout << "En attente de joueurs... Pressez <entrée> pour arrêter le serveur à tout moment" << endl;
            while(1){
                if(game.isFullOfPlayers()){
                    stop = 2;
                    break;
                }
                else if(stop == 1){
                    break;
                }
                usleep(1000);
            }
            //th.join();
            //(void) getc(stdin);
            if(stop == 1){
                cout << "Arret du serveur.. " << endl;
                th.join();
            }
            else if(stop == 2){
                cout << "La salle d'attente est remplie, Demarrage de la partie appuyez, sur <entrée> pour quitter" << endl;         
                th.join();
                cout << "Au revoir !!" << endl;       
            }
            
            MHD_stop_daemon(d);
        }
        catch(exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }
        
    }

    return 0;
}
