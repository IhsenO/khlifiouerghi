/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "HeuristicAI.h"
#include <iostream>
#include "UtilsAI.hpp"
#include <vector>
#include <queue>
#include "Point.h"
#include <random>
#include <chrono>

using namespace state;
using namespace engine;
using namespace std;

namespace ai {

    HeuristicAI::HeuristicAI(state::State& state, engine::Engine& engine) : AI(state, engine) {
        this->map.init(state.getMonde().getWidth(), state.getMonde().getHeight());
        //this->map.setWidth(state.getMonde().getWidth());
        //this->map.setHeight(state.getMonde().getHeight());
        //for(int i = 0; i < state.getMonde().getWidth()*state.getMonde().getHeight(); i++)
        //    this->map.getMap().push_back(true);

    }

    void HeuristicAI::run(engine::Engine& engine, std::stack<engine::Action*>& actionStack) {


        cout << "Tour du Joueur " << this->state.getIdPlayer() << endl;
        cout << "Ressources ---> OR : " << this->state.getPlayer(state.getIdPlayer())->getGold() << " Nourriture : " << this->state.getPlayer(state.getIdPlayer())->getGold() << endl;
        cout << "\n";
        map.update(state);
        //map.afficher();
        vector<CommandsWeights> cw;
        vector<Command*> listCommands;
        EndOfTurnCommand end;
        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        mt19937 mt_rand(seed);

        for (int i = 0; i < state.getMonde().getHeight(); i++)
            for (int j = 0; j < state.getMonde().getWidth(); j++) {
                if (state.getMonde().get(j, i, 2) != NULL) state.getMonde().get(j, i, 2)->setHasPlayed(false);

            }
        //cout << "MM" << endl;
        for (int i = 0; i < state.getMonde().getHeight(); i++)
            for (int j = 0; j < state.getMonde().getWidth(); j++) {

                if (state.getMonde().get(j, i, 1) != NULL) {
                    if (state.getMonde().get(j, i, 1)->getTypeID() == CITY && state.getMonde().get(j, i, 1)->getIdPlayer() == state.getIdPlayer()) {
                        City *c = (City*) state.getMonde().get(j, i, 1);

                        Barrack *b = new Barrack();
                        //listCommands.push_back(new ConstructCommand(j,i,new Barrack()));
                        listCommands.push_back(new ConstructCommand(j, i, b));
                        Mine *m = new Mine();
                        //listCommands.push_back(new ConstructCommand(j,i,new Mine()));
                        listCommands.push_back(new ConstructCommand(j, i, m));
                        Farm *f = new Farm();
                        //listCommands.push_back(new ConstructCommand(j,i,new Farm()));
                        listCommands.push_back(new ConstructCommand(j, i, f));

                        listCommands.push_back(new UpgradeCommand(j, i));

                        listCommands.push_back(new MakeSoldiersCommand(j, i));

                        //cout << c->getSoldiers() <<endl;
                        if (c->getSoldiers() > 50) {
                            listCommands.push_back(new LeaveCityCommand(j, i, j + 1, i, c->getSoldiers() / 2));
                            listCommands.push_back(new LeaveCityCommand(j, i, j - 1, i, c->getSoldiers() / 2));
                            listCommands.push_back(new LeaveCityCommand(j, i, j, i + 1, c->getSoldiers() / 2));
                            listCommands.push_back(new LeaveCityCommand(j, i, j, i - 1, c->getSoldiers() / 2));

                        }

                        int random = (int) (mt_rand() % listCommands.size());

                        if (random != 0) delete b;
                        if (random != 1) delete m;
                        if (random != 2) delete f;
                        if (listCommands.size() > 0) engine.runCommand(listCommands[random], actionStack);


                        for (auto& command : listCommands)
                            delete command;

                        listCommands.clear();
                    }
                }

                if (state.getMonde().get(j, i, 2) != NULL) {
                    if (state.getMonde().get(j, i, 2)->getTypeID() == ARMY && state.getMonde().get(j, i, 2)->getIdPlayer() == state.getIdPlayer() && !state.getMonde().get(j, i, 2)->getHasPlayed()) {

                        Army *playerArmy = (Army*) state.getMonde().get(j, i, 2);

                        for (int k = i - 2; k < i + 3; k++)
                            for (int l = j - 2; l < j + 3; l++) {

                                if (isInMap(state, l, k) && enemyArmy(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange())) {
                                    Army *ennemyArmy = (Army*) state.getMonde().get(l, k, 2);
                                    int diff = playerArmy->getSoldiers() - ennemyArmy->getSoldiers();
                                    cw.push_back(CommandsWeights(new AttackArmyCommand(j, i, l, k), diff));
                                } 
                                else if (isInMap(state, l, k) && enemyCity(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange())) {
                                    cout << cw.size() << endl;
                                    City *ennemyCity = (City*) state.getMonde().get(l, k, 1);
                                    int diff = playerArmy->getSoldiers() - (ennemyCity->getSoldiers() + ennemyCity->getDefense()*100);
                                    cw.push_back(CommandsWeights(new AttackCityCommand(j, i, l, k), diff));

                                }
                                else if (isInMap(state, l, k) && friendlyArmy(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange())) {
                                    if (j != l || i != k) {
                                        Army *friendlyA = (Army*) state.getMonde().get(l, k, 2);
                                        //int diff = 100;
                                        cw.push_back(CommandsWeights(new ArmyFusionCommand(j, i, l, k), 100));
                                        friendlyA->setHasPlayed(true);
                                    }

                                }

                            }
                        if (cw.size() > 0) {
                            int idCmd = 0;
                            int cmdValueMax = cw[0].getWeight();
                            for (int i = 0; i < (int)cw.size(); i++) {
                                if (cw[i].getWeight() > cmdValueMax) {
                                    idCmd = i;
                                    cmdValueMax = cw[i].getWeight();
                                }
                            }
                            cw[idCmd].getCommand()->execute(state, actionStack);
                            playerArmy->setHasPlayed(true);
                            cw.clear();

                        }



                        map.addQueue(j, i);
                        vector<int> map1 = map.dijkstra();
                        //map.afficherPoids();
                        cout << '\n';

                        if (!playerArmy->getHasPlayed()) {
                            for (int k = 0; k < state.getMonde().getHeight(); k++)
                                for (int l = 0; l < state.getMonde().getWidth(); l++) {
                                    if (state.getMonde().get(l, k, 1) != NULL) {
                                        if (state.getMonde().get(l, k, 1)->getTypeID() == CITY && state.getMonde().get(l, k, 1)->getIdPlayer() != state.getIdPlayer()) {
                                            City *ennemyCity = (City*) state.getMonde().get(l, k, 1);
                                            map.addQueue(l, k);
                                            vector<int> map2 = map.dijkstra();
                                            //map.afficherPoids();
                                            int xBest = j;
                                            int yBest = i;
                                            findBestMoveAI(state, xBest, yBest, playerArmy->getRange(), map2);
                                            //int weight = map1[k * state.getMonde().getWidth() + l]*10;
                                            int diff = playerArmy->getSoldiers() - (ennemyCity->getSoldiers() + ennemyCity->getDefense()*100);
                                            cw.push_back(CommandsWeights(new MoveCharCommand(j, i, xBest, yBest), diff));
                                            //cout << xBest << " " << yBest << endl;
                                        }

                                    }
                                }
                            for (int k = 0; k < state.getMonde().getHeight(); k++)
                                for (int l = 0; l < state.getMonde().getWidth(); l++) {
                                    if (state.getMonde().get(l, k, 1) != NULL) {
                                        if (state.getMonde().get(l, k, 1)->getTypeID() == ARMY && state.getMonde().get(l, k, 1)->getIdPlayer() != state.getIdPlayer()) {
                                            Army *ennemyArmy = (Army*) state.getMonde().get(l, k, 1);
                                            map.addQueue(l, k);
                                            vector<int> map2 = map.dijkstra();
                                            map.afficherPoids();
                                            int xBest = j;
                                            int yBest = i;
                                            findBestMoveAI(state, xBest, yBest, playerArmy->getRange(), map2);
                                            int diff = playerArmy->getSoldiers() - ennemyArmy->getSoldiers();
                                            cw.push_back(CommandsWeights(new MoveCharCommand(j, i, xBest, yBest), diff));
                                        }

                                    }
                                }
                            if (cw.size() > 0) {
                                int idCmd = 0;
                                int cmdValueMax = cw[0].getWeight();
                                for (int i2 = 0; i2 < (int)cw.size(); i2++) {
                                    if (cw[i2].getWeight() > cmdValueMax) {
                                        idCmd = i2;
                                        cmdValueMax = cw[i2].getWeight();
                                    }
                                }
                                cw[idCmd].getCommand()->execute(state, actionStack);
                                playerArmy->setHasPlayed(true);
                                cw.clear();
                            }
                        }
                    }
                }





            }
        cout << "\n";

        engine.runCommand(&end, actionStack);
        cw.clear();


    }

}
