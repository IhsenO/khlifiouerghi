/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AttackArmyAction.h"
#include "state/Army.h"

using namespace std;
using namespace state;

namespace engine {

    AttackArmyAction::AttackArmyAction(int xFrom, int yFrom, int xTo, int yTo, int soldiersAttacker, int soldiersAttacked, int playerA, int playerB) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiersAttacker(soldiersAttacker), soldiersAttacked(soldiersAttacked), playerA(playerA), playerB(playerB) {

    }

    void AttackArmyAction::undo(state::State& state) {
        
        state.getMonde().set(xFrom, yFrom, 2, new Army(this->soldiersAttacker, playerA));
        state.getMonde().set(xTo, yTo, 2, new Army(this->soldiersAttacked, playerB));
    }
    
    
}