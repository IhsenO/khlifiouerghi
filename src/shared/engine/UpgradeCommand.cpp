/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "UpgradeCommand.h"
#include "state/City.h"
#include <iostream>
#include "UtilsEngine.hpp"
using namespace state;

namespace engine{

    UpgradeCommand::UpgradeCommand(int x, int y) : x(x), y(y) {

    }

    CommandTypeId UpgradeCommand::getCommandTypeId() const {
        return UPGRADE;
    }

    void UpgradeCommand::execute(State& state, std::stack<Action*>& actionStack) {
        //std::cout << "UpgradeCommand" << std::endl;
        if(!inMap(state,x,y)) return;
        if(state.getMonde().get(x, y, 1) == NULL) return;
        if(state.getMonde().get(x, y, 1)->getTypeID() == state::CITY){
            City *c = (City*)state.getMonde().get(x, y, 1);
            if(c->getIdPlayer() != state.getIdPlayer()) return;
            if(c->getDefense() < 3 && state.getPlayer(state.getIdPlayer())->getGold() > 250 && state.getPlayer(state.getIdPlayer())->getFood() > 250){
                actionStack.push(new UpgradeAction(x,y));
                c->setDefense(c->getDefense() + 1);
                state.getPlayer(state.getIdPlayer())->setFood(state.getPlayer(state.getIdPlayer())->getFood() - 250);
                state.getPlayer(state.getIdPlayer())->setGold(state.getPlayer(state.getIdPlayer())->getGold() - 250);
            }
            //if (c != NULL) delete c;
        }      
    }

    void UpgradeCommand::serialize(Json::Value& out) const {
        out["Type"] = "Upgrade";
        out["x"] = x;
        out["y"] = y;
    }

    UpgradeCommand* UpgradeCommand::deserialize(const Json::Value& in) {
        return new UpgradeCommand(in["x"].asInt(), in["y"].asInt());
    }
    
    
}