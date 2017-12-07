/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ConstructAction.h"
#include "state/Construction.h"

using namespace std;
using namespace state;

namespace engine{

    ConstructAction::ConstructAction(int x, int y, Construction* construction) : x(x), y(y), construction(construction)  {

    }

    void ConstructAction::undo(state::State& state) {
        City *c = (City*)state.getMonde().get(x, y, 1);
        c->deleteConstruction(this->construction);
        Player *p = state.getPlayer(c->getIdPlayer());
        //Player *p = state.getPlayer(1);
        p->setGold(p->getGold() + construction->getCost());
    }

    
}