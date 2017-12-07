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
#include "UtilsAI.hpp"

using namespace state;
using namespace engine;
using namespace std;

namespace ai{
    
    
    DeepAI::DeepAI(state::State& state, engine::Engine& engine, int depth) : AI(state, engine), depth(depth)  {
        
    }

    void DeepAI::createTree(std::stack<engine::Action*>& actionStack) {
        Node *root = new Node(0,0,NULL);
        stack<Node*> todo;
        todo.push(root);
        //findCommands(todo);
        //root->addSon(todo.top());
        while(!todo.empty()){
            Node *node = todo.top();
            todo.pop();
            if(node->getProf() < depth){
                vector<Command*> commands = findCommands();            
                for(int i = 0; i < commands.size(); i++){
                    node->addSon(new Node(node->getProf()+1, 0, commands[i]));
                }            
            }
        }
    }

    void DeepAI::run(engine::Engine& engine, std::stack<engine::Action*>& actionStack) {
        
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
        std::cout << commands.size() << std::endl;
        return commands; 
    }

    
}