#include <iostream>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <stack>
#include <thread>
#include "unistd.h"
#include <stdio.h>
#include <fstream>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include "Tests.hpp"
#include "render.h"
#include "engine.h"
#include "utils.hpp"
#include "client.h"
//#include "client/Client.h"


using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace client;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        menu();
        return 2;
    }

    string mode = argv[1];
    if (mode == "hello")
        cout << "Hello world !" << endl;

    else if (mode == "state")
        testsUnitaires();

    else if (mode == "render") {

        sf::RenderWindow window(sf::VideoMode(800, 480), "Rendu");
        window.setFramerateLimit(60);
        Monde *m = new Monde(3);

        m->set(2, 2, 2, new Army());

        m->set(8, 2, 2, new Army());


        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));
        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        //sf::View view = window.getDefaultView();
        //view.zoom(0.5f);   

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();

            //window.setView(view);

            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();

        }

        delete m;
    }
    else if (mode == "engine") {


        sf::RenderWindow window(sf::VideoMode(336, 224), "Engine");
        window.setFramerateLimit(60);
        int i = 0;

        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));


        m->set(4, 4, 2, new Army());
        state.getMonde().get(4, 4, 2)->setIdPlayer(1);
        state.getMonde().get(2, 2, 1)->setIdPlayer(1);

        state.getMonde().get(18, 11, 1)->setIdPlayer(2);
        Engine e(state);

        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));

        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyReleased && i < 23) {
                    testsEngine(i, e, state);
                    i++;
                }
            }
            window.clear();

            //window.setView(view);

            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();


        }

        delete m;
    }
    else if (mode == "random_ai") {

        sf::RenderWindow window(sf::VideoMode(336, 224), "Random_IA");
        window.setFramerateLimit(60);
        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));

        //state.getMonde().get(2,2,1)->setIdPlayer(1);
        //state.getMonde().get(18,11,1)->setIdPlayer(2);   
        Engine e(state);

        state.setIdPlayer(2);

        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));

        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        cout << "Bienvenue dans le mode avec une IA random !" << endl;
        cout << "Pour faire défiler les epoques, appuyez sur n'importe quelle touche." << endl;
        cout << "En restant appuyé, les epoques défilent plus vite !" << endl;

        RandomAI random(state, e);
        stack<Action*> pile;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed) {
                    //testsAIRandom(e, state);
                    random.run(e, pile, false);
                    if (state.getIdPlayer() == 1) state.setIdPlayer(2);
                    else if (state.getIdPlayer() == 2) state.setIdPlayer(1);
                }
            }
            window.clear();

            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();


        }

        delete m;

    }
    else if (mode == "heuristic_ai") {



        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));
        //m->set(4,4,2,new Army());
        //state.getMonde().get(4,4,2)->setIdPlayer(1);

        //m->set(10,8,2,new Army());
        //state.getMonde().get(10,8,2)->setIdPlayer(2);

        //state.getMonde().get(2,2,1)->setIdPlayer(1);
        //state.getMonde().get(18,11,1)->setIdPlayer(2);   
        Engine e(state);

        state.setIdPlayer(2);

        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));

        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        stack<Action*> pile;

        cout << "Bienvenue dans le mode avec une IA heuristique !" << endl;
        cout << "Pour faire défiler les epoques, appuyez sur n'importe quelle touche." << endl;
        cout << "En restant appuyé, les epoques défilent plus vite !" << endl;

        cout << "Choisissez l'IA du joueur 1 avec les batiments rouges et unités or !" << endl;
        cout << "Tapez 1 pour une IA Random et 2 pour une Heuristique !" << endl;
        AI *ai1;
        int IA1 = 1;
        cin >> IA1;
        if (IA1 == 1) {
            ai1 = new RandomAI(state, e);
        } else if (IA1 == 2) {
            ai1 = new HeuristicAI(state, e);
        } else {
            cout << "Erreur, Du coup on choisi l'IA Random." << endl;
            ai1 = new RandomAI(state, e);
        }


        cout << "Choisissez l'IA du joueur 2 avec les batiments Jaunes et unités Argent !" << endl;
        cout << "Tapez 1 pour une IA Random et 2 pour une Heuristique !" << endl;
        AI *ai2;
        int IA2 = 1;
        cin >> IA2;
        if (IA2 == 1) {
            ai2 = new RandomAI(state, e);
        } else if (IA2 == 2) {
            ai2 = new HeuristicAI(state, e);
        } else {
            cout << "Erreur, Du coup on choisi l'IA Random." << endl;
            ai2 = new RandomAI(state, e);
        }

        //HeuristicAI heuristic(state, e);
        //RandomAI random(state, e);
        //AI *ai1 = new HeuristicAI(state,e); 
        sf::RenderWindow window(sf::VideoMode(336, 224), "Heuristic_IA");
        window.setFramerateLimit(60);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed) {
                    //testsAIRandom(e, state);
                    //heuristic.run(e);
                    if (state.getIdPlayer() == 1) {
                        //heuristic.run(e);
                        ai1->run(e, pile, false);
                        state.setIdPlayer(2);
                    } else if (state.getIdPlayer() == 2) {
                        ai2->run(e, pile, false);
                        state.setIdPlayer(1);
                    }
                }
            }
            window.clear();

            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();


        }

        delete m;

    }
    else if (mode == "rollback") {



        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));

        m->set(2, 4, 2, new Army(1000, 1));


        //m->set(4,6,2,new Army(100, 2));


        Engine e(state);

        state.setIdPlayer(1);

        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));

        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        AI *ai1;

        ai1 = new HeuristicAI(state, e);

        AI *ai2;
        ai2 = new RandomAI(state, e);

        cout << "Bienvenue dans le mode avec un rollback !" << endl;
        cout << "Pour faire défiler les epoques, appuyez sur n'importe quelle touche." << endl;
        cout << "En restant appuyé, les epoques défilent plus vite !" << endl;
        cout << "Au bout de 50 commandes le jeu reviens en arrière !" << endl;

        stack<Action*> pile;
        //HeuristicAI heuristic(state, e);
        //RandomAI random(state, e);
        //AI *ai1 = new HeuristicAI(state,e); 
        sf::RenderWindow window(sf::VideoMode(336, 224), "Rollback");
        window.setFramerateLimit(60);
        int i = 0;



        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed) {

                    //MoveCharCommand move(2,4,3,4);
                    //e.runCommand(&move, pile);
                    //cout << pile.size() << endl;

                    if (i < 50) {
                        //cout << "Okay" << endl;
                        if (state.getIdPlayer() == 1) {
                            //cout << "J1" << endl;
                            ai1->run(e, pile, false);
                            state.setIdPlayer(2);
                            //cout << "Okay" << endl;
                        } else if (state.getIdPlayer() == 2) {
                            ai2->run(e, pile, false);
                            //cout << "J2" << endl;
                            state.setIdPlayer(1);
                        }
                        i++;
                    }
                    else {
                        //cout << pile.size() << endl;
                        e.undo(pile);
                        //i++;
                    }


                }
            }
            window.clear();

            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();
            //usleep(50);

        }

        delete m;

    }
    else if (mode == "deep_ai") {



        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));

        m->set(2, 4, 2, new Army(1000, 1));
        m->set(16, 2, 2, new Army(1000, 1));
        m->set(8, 2, 2, new Army(10, 2));
        m->set(4, 11, 2, new Army(10, 2));

        //m->set(4,6,2,new Army(100, 2));


        Engine e(state);

        state.setIdPlayer(1);

        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));

        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        //AI *ai1;
        cout << "Bienvenue dans le mode avec une IA Avancé!" << endl;
        cout << "Pour faire défiler les epoques, appuyez sur n'importe quelle touche." << endl;
        cout << "En restant appuyé, les epoques défilent plus vite !" << endl;
        cout << "L'IA avancé ne fonctionne actuellement pas helas, il semble y avoir un soucis que nous avons pas eu le temps de régler... !" << endl;
        //ai1 = new DeepAI(state,e); 

        DeepAI deepJ1(state, e, 2);
        DeepAI deepJ2(state, e, 2);

        stack<Action*> pile;

        sf::RenderWindow window(sf::VideoMode(336, 224), "DeepAI");
        window.setFramerateLimit(60);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed) {

                    if (state.getIdPlayer() == 1) {

                        deepJ1.run(e, pile, false);
                        state.setIdPlayer(2);

                    } else if (state.getIdPlayer() == 2) {
                        deepJ2.run(e, pile, false);
                        state.setIdPlayer(1);
                    }






                }
            }
            window.clear();

            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();


        }

        delete m;

    }
    else if (mode == "thread") {



        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));

        Engine e(state);

        state.setIdPlayer(1);

        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));

        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        //AI *ai1;
        cout << "Bienvenue dans le mode avec Tread !" << endl;
        cout << "Pour faire défiler les epoques, appuyez sur n'importe quelle touche." << endl;
        cout << "En restant appuyé, les epoques défilent plus vite !" << endl;

        stack<Action*> pile;

        sf::RenderWindow window(sf::VideoMode(336, 224), "Thread");
        
        window.setFramerateLimit(60);
        AI *ai1;
        ai1 = new HeuristicAI(state, e);

        AI *ai2;
        ai2 = new RandomAI(state, e);

        thread th(&Engine::runThread, &e, ai1, ai2);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    //th.join();
                }
                else if (event.type == sf::Event::KeyPressed) {

                    if (state.getIdPlayer() == 1) {
                        //cout << "Okay" << endl;
                        e.setPlayer(1);
                        //cout << e.getPlayer() << endl;
                        //state.setIdPlayer(2);
                    } else if (state.getIdPlayer() == 2) {
                        e.setPlayer(2);
                        //cout << e.getPlayer() << endl;
                        //state.setIdPlayer(1);
                    }

                }

            }
            window.clear();
            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();
            //usleep(2);
        }
        e.setPlayer(-1);
        th.join();
        
        delete m;

    }
    else if(mode == "replay"){
        
        cout << "Mode Replay !!!" << endl;
        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));
    
        Engine e(state);

        state.setIdPlayer(1);

        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));

        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        stack<Action*> pile;

        Json::Reader reader;
        Json::Value replay;   
        
        ifstream fichier("res/replay.json");
        if(fichier){
            reader.parse(fichier, replay);
        }      
        int size = replay.size();
        int i = 0;
        //HeuristicAI heuristic(state, e);
        //RandomAI random(state, e);
        //AI *ai1 = new HeuristicAI(state,e); 
        sf::RenderWindow window(sf::VideoMode(336, 224), "Replay");
        window.setFramerateLimit(60);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed) {
                    //testsAIRandom(e, state);
                    //heuristic.run(e);
                    if(i < size){
                        if(state.getIdPlayer() == 1){
                            Json::Value tmp = replay[i];
                            e.runListCommandJson(tmp, pile);
                            cout << i << endl;
                            i++;
                            state.setIdPlayer(2);
                        }
                        else if(state.getIdPlayer() == 2){
                            Json::Value tmp = replay[i];
                            e.runListCommandJson(tmp, pile);
                            cout << i << endl;
                            i++;
                            state.setIdPlayer(1);
                        }
                    }
                    
                }
            }
            window.clear();

            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();


        }

        delete m;
        
    }
    /*
    else if(mode == "network"){
        string nameIn;
        cout << "Connexion au Server ! Donnez votre nom :"<< endl;
        cin >> nameIn;
        //fflush(stdin);
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Put);
        request.setUri("/player");
        request.setHttpVersion(1,1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setBody("{\"name\":\""+nameIn+"\"}");
        
        sf::Http http("http://localhost/", 4040);
        sf::Http::Response response = http.sendRequest(request);

        
        if(response.getStatus() == 201){
            cout << nameIn+" Bienvenue dans la liste du serveur " << endl;
            cout << response.getBody() << endl;
        }
        else{
            cout << "Oups, on dirai que le serveur est rempli.." << endl;
           
            //throw runtime_error("Plus de place");
            //cout << "Impossible d'entrer ds la liste, Status "+response.getStatus() << endl;;
        }
        
        
        string id = "-1";
        Json::Reader reader;
        Json::Value jsonResponse;
        if(!reader.parse(response.getBody(),jsonResponse)){
            //cout << "Pb.." << endl;
        }
        else{
            if(jsonResponse["id"].asString().size() == 1){
                id = jsonResponse["id"].asString();
                
            }
            
        }
        
        cout << "Les joueurs présents sur ce serveur sont : \n" << endl;
        
        sf::Http::Request request2;
        request2.setMethod(sf::Http::Request::Get);
        request2.setUri("/player");
        request2.setHttpVersion(1,1);
        request2.setField("Content-Type", "application/x-www-form-urlencoded");
        //request.setBody("{\"name\":\"Jean\"}");
        
        
        //sf::Http http("http://localhost/", 4040);
        sf::Http::Response response2 = http.sendRequest(request2);
        if(response2.getStatus() != 200){
            cout << "Il y a un soucis, Status : "+response2.getStatus() << endl;
        } 
        cout << response2.getBody() << endl;
        
        cout << "\n\nPour quitter, pressez <entrée> " << endl;
        //(void) getc(stdin);
        cin.ignore();
        cin.get();
        
        if(id.size() == 1){
            sf::Http::Request request3;
            request3.setMethod(sf::Http::Request::Delete);
            request3.setUri("/player/"+id);
            request3.setHttpVersion(1,1);
            request3.setField("Content-Type", "application/x-www-form-urlencoded");
        
            sf::Http::Response response3 = http.sendRequest(request3);
            if(response3.getStatus() != 204){
                cout << "Il y a un soucis, Status : "+response3.getStatus() << endl;
        } 
        //cout << response3.getBody() << endl;
        }
        cout << "Au revoir, voici les joueurs actuellement connectés : " << endl;
        
        sf::Http::Response response4 = http.sendRequest(request2);
        if(response4.getStatus() != 200){
            cout << "Il y a un soucis, Status : "+response4.getStatus() << endl;
        } 
        
       
        cout << response4.getBody() << endl;
        
        
    }
     */
    else if(mode == "network"){
        
        string nameIn;
        cout << "Connexion au Server ! Donnez votre nom :"<< endl;
        cin >> nameIn;
        //fflush(stdin);
        sf::Http::Request request;
        request.setMethod(sf::Http::Request::Put);
        request.setUri("/player");
        request.setHttpVersion(1,1);
        request.setField("Content-Type", "application/x-www-form-urlencoded");
        request.setBody("{\"name\":\""+nameIn+"\"}");
        
        sf::Http http("http://localhost/", 4040);
        sf::Http::Response response = http.sendRequest(request);
        
        if(response.getStatus() == 201){
            cout << nameIn+" Bienvenue dans la liste du serveur " << endl;
            cout << response.getBody() << endl;
        }
        else{
            cout << "Oups, on dirai que le serveur est rempli.." << endl;
           
            //throw runtime_error("Plus de place");
            //cout << "Impossible d'entrer ds la liste, Status "+response.getStatus() << endl;;
        }
        
        
        int idPlayer = -1;
        string id = "-1";
        Json::Reader reader;
        Json::Value jsonResponse;
        if(!reader.parse(response.getBody(),jsonResponse)){
            //cout << "Pb.." << endl;
        }
        else{
            if(jsonResponse["id"].asString().size() == 1){
                id = jsonResponse["id"].asString();
                idPlayer = stoi(id) + 1;
            }
            
        }
        id = std::to_string(idPlayer);
        
        cout << "Les joueurs présents sur ce serveur sont : \n" << endl;
        
        sf::Http::Request request2;
        request2.setMethod(sf::Http::Request::Get);
        request2.setUri("/player");
        request2.setHttpVersion(1,1);
        request2.setField("Content-Type", "application/x-www-form-urlencoded");
        //request.setBody("{\"name\":\"Jean\"}");
        
        
        //sf::Http http("http://localhost/", 4040);
        sf::Http::Response response2 = http.sendRequest(request2);
        if(response2.getStatus() != 200){
            cout << "Il y a un soucis, Status : "+response2.getStatus() << endl;
        } 
        cout << response2.getBody() << endl;
        
        
        sf::Http::Request requestPlayer;
        requestPlayer.setMethod(sf::Http::Request::Get);
        requestPlayer.setUri("/game");
        requestPlayer.setHttpVersion(1,1);
        requestPlayer.setField("Content-Type", "application/x-www-form-urlencoded");
        
        //cout << "Mode Replay !!!" << endl;
        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));
    
        state.setIdPlayer(1);
        Engine e(state);

        AI *ai1;
        ai1 = new HeuristicAI(state, e);
        
        state.setIdPlayer(1);

        MapLayer map1(*m->getLayer(0));
        MapLayer map2(*m->getLayer(1));

        CharactersLayer chars(*m->getLayer(2));

        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();

        stack<Action*> pile;
        
        
        sf::Http::Request requestGetCommands;
        requestGetCommands.setMethod(sf::Http::Request::Get);
        requestGetCommands.setUri("/commands/"+id);
        requestGetCommands.setHttpVersion(1,1);
        requestGetCommands.setField("Content-Type", "application/x-www-form-urlencoded");
        
        sf::Http::Request requestSendCommands;
        requestSendCommands.setMethod(sf::Http::Request::Put);
        requestSendCommands.setUri("/commands");
        requestSendCommands.setHttpVersion(1,1);
        requestSendCommands.setField("Content-Type", "application/x-www-form-urlencoded");
        
        
        sf::RenderWindow window(sf::VideoMode(336, 224), nameIn);
        window.setFramerateLimit(20);
        while (window.isOpen()) {
            sf::Event event;

            sf::Http::Response responseGet = http.sendRequest(requestGetCommands);
            
            //cout << responseGet.getStatus() << endl;
            
            if(responseGet.getStatus() == 200){
            Json::Value tmp;
            if(reader.parse(responseGet.getBody(), tmp)){
                e.runListCommandJson(tmp, pile);
                if(idPlayer == 1) state.setIdPlayer(1);
                else state.setIdPlayer(2);
            }
            } 
            
            
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed) {
                    
                    if (event.key.code == sf::Keyboard::Space){
                    
                        sf::Http::Response responsePlayer = http.sendRequest(requestPlayer);
                        cout << responsePlayer.getStatus() << endl;
                        Json::Value tmpPlayer;
                        int playerTurn = -1;
                        if(reader.parse(responsePlayer.getBody(),tmpPlayer))
                            playerTurn = stoi(tmpPlayer["idPlayer"].asString());
                    
                        if(idPlayer == playerTurn){
                            ai1->run(e, pile, true);
                            Json::Value tmp = *(e.getValueJson());
                    
                            requestSendCommands.setBody(tmp.toStyledString());
        
                            sf::Http::Response responseSend = http.sendRequest(requestSendCommands);
                            if(idPlayer == 1) state.setIdPlayer(2);
                            else state.setIdPlayer(1);
                     
                        }
                    }
                    else if(event.key.code == sf::Keyboard::R){
                        
                    }
                    
                }
            }
            window.clear();

            map1.initDrawer();
            map2.initDrawer();
            chars.initDrawer();
            window.draw(*map1.getDrawer());
            window.draw(*map2.getDrawer());
            window.draw(*chars.getDrawer());
            window.display();


        }

        delete m;
        
    }
        
    


    
    return 0;
}
