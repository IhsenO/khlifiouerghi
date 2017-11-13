/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ConstructCommand.h"
#include <iostream>
using namespace state;

namespace engine{

    ConstructCommand::ConstructCommand(int x, int y, Construction* construction) : x(x), y(y), construction(construction) {

    }

    CommandTypeId ConstructCommand::getCommandTypeId() const {
        return CONSTRUCT;
    }

    void ConstructCommand::execute(State& state) {
        if(state.getMonde().get(x, y, 1) == NULL) return;
        if(state.getMonde().get(x, y, 1)->getTypeID() == state::CITY){
            City *c = (City*)state.getMonde().get(x, y, 1);
            if(c->getIdPlayer() != state.getIdPlayer()) return;            
            if(c->canBuild(this->construction->getConstructionId())){
                c->addConstruction(this->construction);
                Player *p = state.getPlayer(c->getIdPlayer());
                p->setGold(p->getGold() - 250);
            }
        }                
    }
    
    
}