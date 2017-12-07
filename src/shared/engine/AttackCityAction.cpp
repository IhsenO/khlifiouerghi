/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AttackCityAction.h"
#include "state/Army.h"
#include "state/City.h"
#include <iostream>

using namespace state;

namespace engine {

    AttackCityAction::AttackCityAction(int xFrom, int yFrom, int xTo, int yTo, int playerA, int playerB, int soldiersAttacker, int soldiersCity, int defense, bool free) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), playerA(playerA), playerB(playerB), soldiersAttacker(soldiersAttacker), soldiersCity(soldiersCity), defense(defense), free(free) {

    }


    void AttackCityAction::undo(state::State& state) {
        City *c = (City*)state.getMonde().get(xTo,yTo,1);
        c->setIdPlayer(playerB);
        c->setFree(free);
        c->setSoldiers(soldiersCity);
        c->setDefense(defense);
        state.getMonde().set(xFrom, yFrom, 2, new Army(soldiersAttacker,playerA));
        
    }
    
    
    
}