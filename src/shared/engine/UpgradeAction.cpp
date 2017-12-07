/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "UpgradeAction.h"
#include "state/City.h"

using namespace std;
using namespace state;

namespace engine{

    UpgradeAction::UpgradeAction(int x, int y) : x(x), y(y) {
        
    }

    void UpgradeAction::undo(state::State& state) {
        City *c = (City*)state.getMonde().get(x, y, 1);
        c->setDefense(c->getDefense() - 1);
        state.getPlayer(state.getIdPlayer())->setFood(state.getPlayer(state.getIdPlayer())->getFood() + 250);
        state.getPlayer(state.getIdPlayer())->setGold(state.getPlayer(state.getIdPlayer())->getGold() + 250);
        //state.getPlayer(1)->setFood(state.getPlayer(1)->getFood() + 250);
        //state.getPlayer(1)->setGold(state.getPlayer(1)->getGold() + 250);
    }
    
    
}
