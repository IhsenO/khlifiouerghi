/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "EnterCityCommand.h"
#include "state/Army.h"
#include "state/City.h"
#include "UtilsEngine.hpp"

using namespace state;

namespace engine{

    EnterCityCommand::EnterCityCommand(int xFrom, int yFrom, int xTo, int yTo, int soldiers) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiers(soldiers) {

    }

    CommandTypeId EnterCityCommand::getCommandTypeId() const {
        return ENTERCITY;
    }

    void EnterCityCommand::execute(state::State& state) {
        if(!inMap(state,xTo,yTo)) return;
        if(!inMap(state,xFrom,yFrom)) return;
        if(state.getMonde().get(xFrom, yFrom, 2) == NULL || state.getMonde().get(xTo, yTo, 1) == NULL) return;
        if(state.getIdPlayer() != state.getMonde().get(xFrom, yFrom, 2)->getIdPlayer()) return;
        if(state.getIdPlayer() != state.getMonde().get(xTo, yTo, 1)->getIdPlayer()) return;
        if(state.getMonde().get(xFrom, yFrom, 2)->getIdPlayer() != state.getMonde().get(xTo, yTo, 1)->getIdPlayer()) return;
        if(state.getMonde().get(xFrom, yFrom, 2)->getTypeID() != ARMY || state.getMonde().get(xTo, yTo, 1)->getTypeID() != CITY) return;
        Army *a = (Army*)state.getMonde().get(xFrom, yFrom, 2);
        City *c = (City*)state.getMonde().get(xTo,yTo,1);
        if(!canReachImproved(xFrom, yFrom, xTo, yTo, a->getRange())) return;
        if(a->getSoldiers() > soldiers){
            a->setSoldiers(a->getSoldiers() - soldiers);
            c->setSoldiers(c->getSoldiers() + soldiers);
        }
        else if(a->getSoldiers() == soldiers){
            c->setSoldiers(c->getSoldiers() + soldiers);
            state.getMonde().set(xFrom, yFrom, 2, NULL);
        }
        else return;
        
        
    }
    
    
}
