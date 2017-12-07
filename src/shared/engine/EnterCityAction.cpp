/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "EnterCityAction.h"
#include "state/City.h"
#include "state/Army.h"
#include <iostream>

using namespace state;

namespace engine{

    EnterCityAction::EnterCityAction(int xFrom, int yFrom, int xTo, int yTo, int soldiers) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiers(soldiers) {

    }

    void EnterCityAction::undo(state::State& state) {
        if(state.getMonde().get(xFrom, yFrom, 2) == NULL){
            
            City *c = (City*)state.getMonde().get(xTo, yTo, 1);
            state.getMonde().set(xFrom, yFrom, 2, new Army(soldiers, c->getIdPlayer()));
            c->setSoldiers(c->getSoldiers() - soldiers);
            std::cout << soldiers << std::endl;
        }
        else{
            
            City *c = (City*)state.getMonde().get(xTo, yTo, 1);
            Army *a = (Army*)state.getMonde().get(xFrom, yFrom, 2);
            a->setSoldiers(a->getSoldiers() + soldiers);
            c->setSoldiers(c->getSoldiers() - soldiers);
        }
            
    }
    
    
}