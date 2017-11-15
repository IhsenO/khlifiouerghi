/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "UpgradeCommand.h"
#include "state/City.h"
#include <iostream>
using namespace state;

namespace engine{

    UpgradeCommand::UpgradeCommand(int x, int y) : x(x), y(y) {

    }

    CommandTypeId UpgradeCommand::getCommandTypeId() const {
        return UPGRADE;
    }

    void UpgradeCommand::execute(State& state) {
        std::cout << "UpgradeCommand" << std::endl;
        if(state.getMonde().get(x, y, 1) == NULL) return;
        if(state.getMonde().get(x, y, 1)->getTypeID() == state::CITY){
            City *c = (City*)state.getMonde().get(x, y, 1);
            if(c->getIdPlayer() != state.getIdPlayer()) return;
            if(c->getDefense() < 3 && state.getPlayer(state.getIdPlayer())->getGold() > 250 && state.getPlayer(state.getIdPlayer())->getFood() > 250){
                c->setDefense(c->getDefense() + 1);
                state.getPlayer(state.getIdPlayer())->setFood(state.getPlayer(state.getIdPlayer())->getFood() - 250);
                state.getPlayer(state.getIdPlayer())->setGold(state.getPlayer(state.getIdPlayer())->getGold() - 250);
            }
            //if (c != NULL) delete c;
        }      
    }
  
    
}