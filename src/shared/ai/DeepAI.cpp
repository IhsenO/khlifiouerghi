/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DeepAI.h"
#include "engine/Command.h"
#include "engine/AttackArmyCommand.h"
#include "engine/ArmyFusionCommand.h"
#include "engine/AttackCityCommand.h"
#include "engine/MoveCharCommand.h"
#include <iostream>
#include <queue>
#include "UtilsAI.hpp"

using namespace state;
using namespace engine;
using namespace std;

namespace ai{
    
    
    DeepAI::DeepAI(state::State& state, engine::Engine& engine, int depth) : AI(state, engine), depth(depth)  {
        this->map.init(state.getMonde().getWidth(), state.getMonde().getHeight());
    }

    Node* DeepAI::createTree(std::stack<engine::Action*>& actionStack, int player) {
        state.setIdPlayer(player);
        int a = 0;
        int player2;
        if(player == 1) player2 = 2;
        if(player == 2) player2 = 1;
        vector<Command*> vec;
        Node *root = new Node(0,-1,player,vec);
        queue<Node*> todo;
        todo.push(root);
        //findCommands(todo);
        //root->addSon(todo.top());
        while(!todo.empty()){
            while(!actionStack.empty()){
                actionStack.top()->undo(state);
                actionStack.pop();
            }
            
            Node *node = todo.front();
            
            todo.pop();
            
            for(int i = 0; i < (int)node->getCommands().size(); i++){
                if(i%2 == 0) state.setIdPlayer(player);
                else state.setIdPlayer(player2);
                node->getCommands()[i]->execute(state, actionStack);
            }
            //cout << "2" << endl;
            if(node->getProf() < depth){
                state.setIdPlayer(node->getPlayer());
                vector<Command*> commands = findCommands();            
                for(int i = 0; i < (int)commands.size(); i++){
                    //cout << "3" << endl;
                    int pl;
                    if(node->getPlayer() == 1) pl = 2;
                    else pl = 1;
                    node->addSon(new Node(node->getProf()+1, -1, pl, node->getCommands()));
                    node->getSon(i)->addCommand(commands[i]);
                    todo.push(node->getSon(i));
                }            
            }
            else if(node->getProf() == depth){
                //cout << "4" << endl;
                node->setValue(getHeuristic(player));
                a++;
            }
        }
        while(!actionStack.empty()){
                actionStack.top()->undo(state);
                actionStack.pop();
        }
        //cout << a << endl;
        return root;
    }

    void DeepAI::run(engine::Engine& engine, std::stack<engine::Action*>& actionStack, bool serialize) {
        
        //auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        //mt19937 mt_rand(seed);
        
        stack<engine::Action*> tmp;
        Node *root = createTree(tmp, state.getIdPlayer());
        //int bestMove = minmaxRecMin(root);
        int bestMove = -9999;
        //cout << root->getSon(0)->getSon(0)->getCommands().size() << endl;
        //cout << bestMove << endl;
        Command *comMax = root->getSon(0)->getCommands()[0];
        int max;
        //int id = 0;
        for(int i = 0; i < root->getSize(); i++){
            //cout << root->getSon(i)->getValue() << endl;
            
           //cout << minmaxRecMax(root->getSon(i)) << " " << root->getSon(i)->getCommands()[0]->getCommandTypeId() << endl;
            max = minmaxRecMax(root->getSon(i));
            cout << i << endl;
            if(max > bestMove){
                comMax = root->getSon(i)->getCommands()[0];
                bestMove = max;
                //id = i;
                //root->getSon(i)->getCommands()[0]->execute(state, actionStack);
                //break;
                //cout << root->getSon(i)->getCommands().size() << endl; 
                //cout << i << endl;
            }
            //cout << id << endl;
            //cout << comMax->getCommandTypeId() << endl;
            //comMax->execute(state, actionStack);
            //root->getSon(id)->getCommands()[0]->execute(state, actionStack);
            
        }
        cout << comMax->getCommandTypeId() << endl;
        comMax->execute(state, actionStack);
    }

    std::vector<Command*> DeepAI::findCommands() {
        
        std::vector<Command*> commands;
        for (int i = 0; i < state.getMonde().getHeight(); i++)
            for (int j = 0; j < state.getMonde().getWidth(); j++) {
               if (state.getMonde().get(j, i, 2) != NULL) {
                    if (state.getMonde().get(j, i, 2)->getTypeID() == ARMY && state.getMonde().get(j, i, 2)->getIdPlayer() == state.getIdPlayer()){
                       Army *playerArmy = (Army*) state.getMonde().get(j, i, 2);
                        for (int k = i - 2; k < i + 3; k++)
                            for (int l = j - 2; l < j + 3; l++) {
                                if (isInMap(state, l, k) && enemyArmy(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange())) {
                                    commands.push_back(new AttackArmyCommand(j,i,l,k));
                                    //cout << "ouais" << endl;
                                }
                                else if(isInMap(state, l, k) && enemyCity(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange())){
                                    commands.push_back(new AttackCityCommand(j,i,l,k));
                                }
                                else if(isInMap(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange()) && canAccessAI(state,l,k)){
                                    commands.push_back(new MoveCharCommand(j,i,l,k));
                                }
                            } 
                    }
                }                 
            }
        //std::cout << commands.size() << std::endl;
        return commands; 
    }

    int DeepAI::getHeuristic(int player) {
        int nbCity = 0;
        int mySoldiers = 0;
        int enemySoldiers = 0;
        int bestDist = 0;
        for (int i = 0; i < state.getMonde().getHeight(); i++)
            for (int j = 0; j < state.getMonde().getWidth(); j++) {
                if (state.getMonde().get(j, i, 1) != NULL) {
                    if (state.getMonde().get(j, i, 1)->getTypeID() == CITY && state.getMonde().get(j, i, 1)->getIdPlayer() == player) {
                        nbCity++;
                    }
                }
                else if (state.getMonde().get(j, i, 2) != NULL) {
                    if (state.getMonde().get(j, i, 2)->getTypeID() == ARMY && state.getMonde().get(j, i, 2)->getIdPlayer() == player) {
                        Army *myArmy = (Army*)state.getMonde().get(j,i,2);
                        mySoldiers+=myArmy->getSoldiers();
                        //cout << "Ouais" << endl;
                        /*
                        for (int k = 0; k < state.getMonde().getHeight(); k++)
                            for (int l = 0; l < state.getMonde().getWidth(); l++) {
                                if (state.getMonde().get(l, k, 1) != NULL) {
                                    if (state.getMonde().get(l, k, 1)->getTypeID() == CITY && state.getMonde().get(l, k, 1)->getIdPlayer() != player) {
                                        //City *c = (City*)state.getMonde().get(l,k,1);
                                        //cout << "Ouais" << endl;
                                        map.update(state);
                                        map.addQueue(l, k);
                                        vector<int> map2 = map.dijkstra();
                                        int score =  1 / map2[i*state.getMonde().getWidth()+i];
                                        if(score*10 > bestDist)
                                            bestDist = score*10;
                                    }
                                }
                            }
                        */
                    }
                    else if (state.getMonde().get(j, i, 2)->getTypeID() == ARMY && state.getMonde().get(j, i, 2)->getIdPlayer() != player) {
                        Army *enemyArmy = (Army*)state.getMonde().get(j,i,2);
                        enemySoldiers+=enemyArmy->getSoldiers();
                    }
                }
            }
        
        return nbCity * 1000 + (mySoldiers-enemySoldiers) + bestDist;
    }

    int DeepAI::minmaxRecMin(Node* node) {
        if(node->getValue() != -1)
            return node->getValue();
        int min = 0;
        for(int i = 0; i < node->getSize(); i++){
            Node* child = node->getSon(i);
            int value = minmaxRecMax(child);
            if(value < min)
                min = value;
        }
        //node->setValue(min);
        return min;
        }

    

    int DeepAI::minmaxRecMax(Node* node) {
        if(node->getValue() != -1)
            return node->getValue();
        int max = 0;
        for(int i = 0; i < node->getSize(); i++){
            Node* child = node->getSon(i);
            int value = minmaxRecMin(child);
            if(value > max)
                max = value;
        }
        //node->setValue(max);
        return max;
        }
    
    
    
}