/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AttackCityCommand.h"
#include "state/City.h"
#include "state/Army.h"
#include <time.h>
#include <cmath>
#include <iostream>

using namespace state;

namespace engine{

    AttackCityCommand::AttackCityCommand(int xFrom, int yFrom, int xTo, int yTo) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo) {

    }

    CommandTypeId AttackCityCommand::getCommandTypeId() const {
        return ATTACKCITY;
    }

    void AttackCityCommand::execute(state::State& state) {
        if(state.getMonde().get(xFrom,yFrom, 2) == NULL) return;
        if(state.getMonde().get(xTo,yTo, 1) == NULL) return;
        if(state.getMonde().get(xFrom,yFrom, 2)->getTypeID() == ARMY){
            if(state.getMonde().get(xTo,yTo,1)->getTypeID() == CITY){
                if(state.getMonde().get(xTo,yTo, 1)->getIdPlayer() == state.getMonde().get(xFrom,yFrom, 2)->getIdPlayer()) return;
                Army *army = (Army*)state.getMonde().get(xFrom,yFrom,2);
                City *city = (City*)state.getMonde().get(xTo,yTo,1);
                if(solveCityAttack(army, city)){
                    city->setIdPlayer(army->getIdPlayer());
                    state.getMonde().set(xTo, yTo, 2, state.getMonde().get(xFrom, yFrom, 2));
                    state.getMonde().set(xFrom, yFrom, 2, NULL);
                }
                else{
                    state.getMonde().set(xFrom, yFrom, 2, NULL);
                }
            }                            
        }
    }

    bool AttackCityCommand::solveCityAttack(state::Army* army, state::City* city) {
        if(city->isFree()){
            return true;
        }
        srand(time(NULL));
        float a = (float)army->getSoldiers();
        float b = (float)city->getDefense() * 100;
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

    
}