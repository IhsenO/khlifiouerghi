/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "LeaveCityAction.h"
#include "state/City.h"

using namespace state;

namespace engine{

    LeaveCityAction::LeaveCityAction(int xFrom, int yFrom, int xTo, int yTo, int soldiers) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiers(soldiers) {

    }

    void LeaveCityAction::undo(state::State& state) {
        City *c = (City*)state.getMonde().get(xFrom, yFrom, 1);
        //Army *a = (Army*)state.getMonde().get(xTo,yTo,2);
        c->setSoldiers(c->getSoldiers() + this->soldiers);
        state.getMonde().set(xTo,yTo,2,NULL);
    }
    
    
}