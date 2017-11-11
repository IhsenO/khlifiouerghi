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

using namespace state;

namespace engine {

    AttackArmyCommand::AttackArmyCommand(int xFrom, int yFrom, int xTo, int yTo) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo) {

    }

    void AttackArmyCommand::execute(state::State& state) {
        if(state.getMonde().get(xFrom,yFrom, 2) == NULL) return;
        if(state.getMonde().get(xTo,yTo, 2) == NULL) return;
        if(state.getMonde().get(xFrom,yFrom, 2)->getTypeID() == ARMY){
            if(state.getMonde().get(xTo,yTo,2)->getTypeID() == ARMY){
                Army *army1 = (Army*)state.getMonde().get(xFrom,yFrom, 2);                
                Army *army2 = (Army*)state.getMonde().get(xTo,yTo, 2);
                if(army1->getIdPlayer() == army2->getIdPlayer()) return;
                if(solveFightArmy(army1, army2)){
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
        float meanSoldiers = (a+b)/2;
        float difference = (a - b) / meanSoldiers;
        float probability = 1/(1+exp(-4*difference));
        float randNumber = rand() % 100;
        //std:: cout << difference << " proba " << probability << std::endl;
        //std:: cout << randNumber << " PROBA " << probability*100 << std::endl;
        if(randNumber <= probability*100){
            std:: cout << "Victoire" << std::endl;
            return true;
        }
        else{
            std::cout << "Defaite" << std::endl;
            return false;
        }
    }

    CommandTypeId AttackArmyCommand::getCommandTypeId() const {
        return ATTACKARMY;
    }
   
    
}