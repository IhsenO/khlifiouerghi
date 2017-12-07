/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ArmyFusionAction.h"
#include "state/Army.h"

using namespace state;

namespace engine{

    ArmyFusionAction::ArmyFusionAction(int xFrom, int yFrom, int xTo, int yTo, int soldiersA, int soldiersB) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiersA(soldiersA), soldiersB(soldiersB) {

    }

    void ArmyFusionAction::undo(state::State& state) {
        int player = state.getMonde().get(xTo,yTo, 2)->getIdPlayer();
        state.getMonde().set(xFrom, yFrom, 2, new Army(soldiersA, player));
        state.getMonde().set(xTo, yTo, 2, new Army(soldiersB, player));
    }
    
    
}