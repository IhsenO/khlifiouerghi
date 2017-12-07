/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RandomAI.h"
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include "state/Construction.h"
#include "UtilsAI.hpp"

using namespace state;
using namespace engine;
using namespace std;

namespace ai{

    RandomAI::RandomAI(state::State& state, engine::Engine& engine) : AI(state, engine) {
    }

    void RandomAI::run(engine::Engine& engine, std::stack<engine::Action*>& actionStack) {
        
        vector<Command*> listCommands;
        //mt19937 mt_rand(time(0));
        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        mt19937 mt_rand(seed);
        EndOfTurnCommand end;
               
        //if(state.getIdPlayer() == 1) engine.runCommand(new ConstructCommand(2,2,new Farm()));
        //if(state.getIdPlayer() == 1) engine.runCommand(new ConstructCommand(2,2,new Barrack()));
        //if(state.getIdPlayer() == 1) engine.runCommand(new ConstructCommand(2,2,new Mine()));
        //engine.runCommand(new ConstructCommand(18,11,new Barrack()));
                               
        cout <<"Tour du Joueur " << this->state.getIdPlayer() << endl;
        cout <<"Ressources ---> OR : " << this->state.getPlayer(state.getIdPlayer())->getGold() <<" Nourriture : " << this->state.getPlayer(state.getIdPlayer())->getGold() <<endl;
        cout <<"\n";
        for(int i = 0; i < state.getMonde().getHeight(); i++)
            for(int j = 0; j < state.getMonde().getWidth(); j++){
                if(state.getMonde().get(j,i,1) != NULL){
                    if(state.getMonde().get(j,i,1)->getTypeID() == CITY && state.getMonde().get(j,i,1)->getIdPlayer() == state.getIdPlayer()){
                        City *c = (City*)state.getMonde().get(j,i,1);
                        
                        Barrack *b = new Barrack();
                        //listCommands.push_back(new ConstructCommand(j,i,new Barrack()));
                        listCommands.push_back(new ConstructCommand(j,i,b));
                        Mine *m = new Mine();
                        //listCommands.push_back(new ConstructCommand(j,i,new Mine()));
                        listCommands.push_back(new ConstructCommand(j,i,m));
                        Farm *f = new Farm();
                        //listCommands.push_back(new ConstructCommand(j,i,new Farm()));
                        listCommands.push_back(new ConstructCommand(j,i,f));
                       
                        listCommands.push_back(new UpgradeCommand(j,i));
                        
                        listCommands.push_back(new MakeSoldiersCommand(j,i));
                        
                        //cout << c->getSoldiers() <<endl;
                        if(c->getSoldiers() > 50){
                            listCommands.push_back(new LeaveCityCommand(j,i,j+1,i,c->getSoldiers()/2));
                            listCommands.push_back(new LeaveCityCommand(j,i,j-1,i,c->getSoldiers()/2));
                            listCommands.push_back(new LeaveCityCommand(j,i,j,i+1,c->getSoldiers()/2));
                            listCommands.push_back(new LeaveCityCommand(j,i,j,i-1,c->getSoldiers()/2));
                            
                        }
                        
                        int random = (int)(mt_rand() % listCommands.size());
                        
                        if(random != 0) delete b;
                        if(random != 1) delete m;
                        if(random != 2) delete f;
                        if(listCommands.size() > 0) engine.runCommand(listCommands[random], actionStack);
                        
                        
                        for(auto& command : listCommands)
                            delete command;
                        
                        listCommands.clear();
                    }                 
                }
                else if(state.getMonde().get(j,i,2)!=NULL){
                    if(state.getMonde().get(j,i,2)->getTypeID() == ARMY && state.getMonde().get(j,i,2)->getIdPlayer() == state.getIdPlayer()){
                        for(int k = i-2; k < i+3; k++)
                            for(int l = j-2; l < j+3; l++){
                                if(enemyArmy(state,l,k)){
                                    
                                    listCommands.push_back(new AttackArmyCommand(j,i,l,k));
                                }
                                else if(enemyCity(state,l,k)){
                                    //cout << "Okay" << endl;
                                    listCommands.push_back(new AttackCityCommand(j,i,l,k));
                                }
                                else if(friendlyArmy(state,l,k) && j!=l && k!=i) listCommands.push_back(new ArmyFusionCommand(j,i,l,k));
                                else{                           
                                    listCommands.push_back(new MoveCharCommand(j,i,l,k));
                                }
                            }
                        if(listCommands.size() > 0) engine.runCommand(listCommands[(int)(mt_rand() % listCommands.size())], actionStack);
                        
                        for(auto& command : listCommands)
                            delete command;
                        listCommands.clear();
                    }
                }
            }
        
        for(auto& command : listCommands)
            delete command;
        listCommands.clear();
        //listCommands.erase(listCommands.begin(), listCommands.end());
        engine.runCommand(&end, actionStack);
        cout <<"\n";
        
         
    }
    
    
}
