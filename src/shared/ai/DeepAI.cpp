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
        
    }

    Node* DeepAI::createTree(std::stack<engine::Action*>& actionStack, int player) {
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

    void DeepAI::run(engine::Engine& engine, std::stack<engine::Action*>& actionStack) {
        stack<engine::Action*> tmp;
        Node *root = createTree(tmp, state.getIdPlayer());
        int bestMove = minmaxRecMax(root);
        //cout << "Ocedc" << endl;
        //cout << bestMove << endl;
        for(int i = 0; i < root->getSize(); i++){
            //cout << root->getSon(i)->getValue() << endl;
            if(root->getSon(i)->getValue() == bestMove){
                root->getSon(i)->getCommands()[0]->execute(state, actionStack);
                break;
                //cout << root->getSon(i)->getCommands().size() << endl; 
            }
            
        }
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
                    }
                    else if (state.getMonde().get(j, i, 2)->getTypeID() == ARMY && state.getMonde().get(j, i, 2)->getIdPlayer() != player) {
                        Army *enemyArmy = (Army*)state.getMonde().get(j,i,2);
                        enemySoldiers+=enemyArmy->getSoldiers();
                    }
                }
            }
        
        return nbCity * 1000 + (mySoldiers-enemySoldiers);
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
        node->setValue(min);
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
        node->setValue(max);
        return max;
        }
    
    
    
}