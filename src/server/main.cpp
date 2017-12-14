#include <iostream>
#include <json/json.h>
#include <fstream>

#include "state.h"
#include "Tests.hpp"
#include "engine.h"
#include "utils.hpp"


using namespace std;
using namespace state;
using namespace engine;


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
        cout << "record §§ " << endl; 
        
        
        Monde *m = new Monde("MapTestEngine", 3);
        State state(*m);
        state.addPlayer(new Player("Joueur 1"));
        state.addPlayer(new Player("Joueur 2"));
        
        Engine e(state);
        
        state.setIdPlayer(1);
        
        stack<Action*> pile;
        
        AI *ai1;

        ai1 = new HeuristicAI(state, e);

        AI *ai2;
        ai2 = new RandomAI(state, e);
        
        cout << "Mode record !" << endl;
        cout << "Nous enregistrons des actions pendant un certain nombre de tours, et on le met dans un fichier JSON !" << endl;
        
        Json::Value listCommandSequence;
        
       
        /*
        Json::Value tmp;
        MoveCharCommand move(2,2,4,4);
        move.serialize(tmp);
        
        listCommandSequence.append(tmp);
        
        tmp.clear();
        AttackArmyCommand att(2,2,4,4);
        att.serialize(tmp);
        
        listCommandSequence.append(tmp);
         */ 
        
        //ai1->run(e, pile, true);
        //listCommandSequence = e.getValueJson();
        
        
        
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

    return 0;
}
