/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AttackArmyCommand.h"
#include "state/Army.h"
#include <cmath>
#include <time.h>
#include <iostream>
#include "UtilsEngine.hpp"
using namespace state;

namespace engine {

    AttackArmyCommand::AttackArmyCommand(int xFrom, int yFrom, int xTo, int yTo) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo) {

    }

    void AttackArmyCommand::execute(state::State& state) {
        std::cout << "AttackArmy" << std::endl;
        if(!inMap(state,xTo,yTo)) return;
        if(!inMap(state,xFrom,yFrom)) return;
        if(state.getMonde().get(xFrom,yFrom, 2) == NULL) return;
        if(state.getMonde().get(xTo,yTo, 2) == NULL) return;
        if(state.getMonde().get(xFrom,yFrom, 2)->getTypeID() == ARMY){
            if(state.getMonde().get(xTo,yTo,2)->getTypeID() == ARMY){
                Army *army1 = (Army*)state.getMonde().get(xFrom,yFrom, 2);                
                Army *army2 = (Army*)state.getMonde().get(xTo,yTo, 2);
                if(army1->getIdPlayer() == army2->getIdPlayer()) return;
                if(!canReachSimple(xFrom, yFrom, xTo, yTo, army1->getRange())) return;
                if(hasWonBattle((float)army1->getSoldiers(), (float)army2->getSoldiers())){
                    state.getMonde().set(xTo, yTo, 2, NULL);
                    state.getMonde().set(xTo, yTo, 2, state.getMonde().get(xFrom, yFrom, 2));
                    state.getMonde().set(xFrom, yFrom, 2, NULL);
                }
                else{                    
                    state.getMonde().set(xFrom, yFrom, 2, NULL);                    
                }
                                                
            }
            else if(state.getMonde().get(xTo,yTo,2)->getTypeID() == SETTLERS){
                state.getMonde().set(xTo, yTo, 2, NULL);
                state.getMonde().set(xTo, yTo, 2, state.getMonde().get(xFrom, yFrom, 2));
                state.getMonde().set(xFrom, yFrom, 2, NULL);
            } 
        }
    }

    bool AttackArmyCommand::solveFightArmy(state::Army* firstArmy, state::Army* secondArmy) {
        srand(time(NULL));
        float a = (float)firstArmy->getSoldiers();
        float b = (float)secondArmy->getSoldiers();
        //std:: cout << a << " b " << b << std::endl;
        return hasWonBattle(a, b);
    }

    CommandTypeId AttackArmyCommand::getCommandTypeId() const {
        return ATTACKARMY;
    }
   
    
}