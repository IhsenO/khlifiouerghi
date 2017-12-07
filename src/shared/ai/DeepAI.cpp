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

namespace ai{
    
    
    DeepAI::DeepAI(state::State& state, engine::Engine& engine) : AI(state, engine)  {

    }

    void DeepAI::createTree(std::stack<engine::Action*>& actionStack) {
        Node *root = new Node();
        std::stack<Command*> todo;
        findCommands(todo);
    }

    void DeepAI::run(engine::Engine& engine, std::stack<engine::Action*>& actionStack) {
        
    }

    void DeepAI::findCommands(std::stack<engine::Command*>& stackCommands) {
        for (int i = 0; i < state.getMonde().getHeight(); i++)
            for (int j = 0; j < state.getMonde().getWidth(); j++) {
               if (state.getMonde().get(j, i, 2) != NULL) {
                    if (state.getMonde().get(j, i, 2)->getTypeID() == ARMY && state.getMonde().get(j, i, 2)->getIdPlayer() == state.getIdPlayer()){
                       Army *playerArmy = (Army*) state.getMonde().get(j, i, 2);
                        for (int k = i - 2; k < i + 3; k++)
                            for (int l = j - 2; l < j + 3; l++) {
                                if (isInMap(state, l, k) && enemyArmy(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange())) {
                                    stackCommands.push(new AttackArmyCommand(j,i,l,k));
                                }
                                else if(isInMap(state, l, k) && enemyCity(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange())){
                                    stackCommands.push(new AttackCityCommand(j,i,l,k));
                                }
                                else if(isInMap(state, l, k) && canReachImprovedAI(j, i, l, k, playerArmy->getRange()) && canAccessAI(state,l,k)){
                                    stackCommands.push(new MoveCharCommand(j,i,l,k));
                                }
                            } 
                    }
                }                 
            }
        std::cout << stackCommands.size() << std::endl;
    }

    
}