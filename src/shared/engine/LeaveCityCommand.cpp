/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "LeaveCityCommand.h"
#include "state/City.h"
#include "state/Army.h"
#include "UtilsEngine.hpp"
#include <iostream>

using namespace state;

namespace engine{

    LeaveCityCommand::LeaveCityCommand(int xFrom, int yFrom, int xTo, int yTo, int soldiers) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiers(soldiers) {
        
    }

    CommandTypeId LeaveCityCommand::getCommandTypeId() const {
        return LEAVECITY;
    }

    void LeaveCityCommand::execute(state::State& state, std::stack<Action*>& actionStack) {
        //std::cout << "LeaveCity" << std::endl;
        if(!inMap(state,xTo,yTo)) return;
        if(!inMap(state,xFrom,yFrom)) return;
        if(state.getMonde().get(xFrom, yFrom, 1) == NULL) return;
        if(state.getIdPlayer() != state.getMonde().get(xFrom, yFrom, 1)->getIdPlayer()) return;
        if(state.getMonde().get(xFrom, yFrom, 1)->getTypeID() == state::CITY){
            City *c = (City*)state.getMonde().get(xFrom, yFrom, 1);
            if(!canMoveImproved(state, xFrom, yFrom, xTo, yTo, 2)) return;
            if(c->getSoldiers() < this->soldiers || this->soldiers < 0) return;
            actionStack.push(new LeaveCityAction(xFrom, yFrom, xTo, yTo, soldiers));
            c->setSoldiers(c->getSoldiers() - this->soldiers);
            state.getMonde().set(xTo,yTo,2,new Army(this->soldiers, c->getIdPlayer()));
            
        } 
    }

    void LeaveCityCommand::serialize(Json::Value& out) const {
        out["Type"] = "LeaveCity";
        out["xFrom"] = xFrom;
        out["yFrom"] = yFrom;
        out["xTo"] = xTo;
        out["yTo"] = yTo;
        out["soldiers"] = soldiers;
    }

    LeaveCityCommand* LeaveCityCommand::deserialize(const Json::Value& in) {
        return new LeaveCityCommand(in["xFrom"].asInt(), in["yFrom"].asInt(), in["xTo"].asInt(), in["yTo"].asInt(), in["soldiers"].asInt());
    }
  
    
}