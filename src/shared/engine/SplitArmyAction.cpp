/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SplitArmyAction.h"
#include "state/Army.h"

using namespace state;

namespace engine{

    SplitArmyAction::SplitArmyAction(int xFrom, int yFrom, int xTo, int yTo, int soldiers) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiers(soldiers) {
        
    }

    void SplitArmyAction::undo(state::State& state) {
        Army *a1 = (Army*)state.getMonde().get(xFrom,yFrom,2);
        Army *a2 = (Army*)state.getMonde().get(xTo,yTo,2);
        state.getMonde().set(xFrom,yFrom,2,new Army(a1->getSoldiers() + a2->getSoldiers(), a1->getIdPlayer()));
        state.getMonde().set(xTo, yTo,2, NULL);
    }

    
}