/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MakeSoldiersAction.h"
#include "state/City.h"
#include "state/Barrack.h"

using namespace state;

namespace engine{

    MakeSoldiersAction::MakeSoldiersAction(int x, int y) : x(x), y(y) {
        
    }

    void MakeSoldiersAction::undo(state::State& state) {
        City *c = (City*)state.getMonde().get(x,y,1);
        Barrack b;
        c->setSoldiers(c->getSoldiers() - b.getProductionByTurn());
        state.getPlayer(state.getIdPlayer())->setGold(state.getPlayer(state.getIdPlayer())->getGold() + b.getSoldiersCost());
        state.getPlayer(state.getIdPlayer())->setFood(state.getPlayer(state.getIdPlayer())->getFood() + b.getSoldiersFood());
    }
    
    
    
}