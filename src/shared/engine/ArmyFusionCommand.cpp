/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ArmyFusionCommand.h"
#include "state/Army.h"

using namespace state;

namespace engine{

    ArmyFusionCommand::ArmyFusionCommand(int xFrom, int yFrom, int xTo, int yTo) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo) {

    }

    CommandTypeId ArmyFusionCommand::getCommandTypeId() const {
        return FUSIONARMY;
    }

    void ArmyFusionCommand::execute(state::State& state) {
        if(state.getMonde().get(xFrom,yFrom, 2) == NULL) return;
        if(state.getMonde().get(xTo,yTo, 2) == NULL) return;
        if(state.getMonde().get(xFrom,yFrom, 2)->getTypeID() == ARMY){
            if(state.getMonde().get(xTo,yTo,2)->getTypeID() == ARMY){
                Army *army1 = (Army*)state.getMonde().get(xFrom,yFrom, 2);                
                Army *army2 = (Army*)state.getMonde().get(xTo,yTo, 2);
                if(army1->getIdPlayer() != army2->getIdPlayer()) return;
                army2->setSoldiers(army2->getSoldiers() + army1->getSoldiers());
                state.getMonde().set(xFrom, yFrom, 2, NULL);
            }
            
        }
    }
    
    
    
}