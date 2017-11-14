/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SplitArmyCommand.h"
#include "state/Army.h"
#include "UtilsEngine.hpp"

using namespace state;

namespace engine{

    SplitArmyCommand::SplitArmyCommand(int xFrom, int yFrom, int xTo, int yTo, int soldiers) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiers(soldiers) {

    }

    CommandTypeId SplitArmyCommand::getCommandTypeId() const {
        return SPLITARMY;
    }

    void SplitArmyCommand::execute(state::State& state) {
        if(state.getMonde().get(xFrom,yFrom, 2) == NULL) return;
        if(state.getMonde().get(xTo,yTo, 2) != NULL) return;
        
        if(state.getMonde().get(xFrom,yFrom, 2)->getTypeID() == ARMY){
            Army *army = (Army*)state.getMonde().get(xFrom,yFrom, 2);
            if(!canMoveSimple(state, xFrom, yFrom, xTo, yTo, army->getRange())) return;
            if(army->getIdPlayer() != state.getIdPlayer()) return;
            if(army->getSoldiers() > this->soldiers){
                army->setSoldiers(army->getSoldiers() - this->soldiers);
                state.getMonde().set(xTo,yTo,2,new Army(soldiers, state.getIdPlayer()));
            }
            
        }
    }
    
    
    
}