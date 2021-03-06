/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "SplitArmyCommand.h"
#include "state/Army.h"
#include "UtilsEngine.hpp"

using namespace state;

namespace engine{

    SplitArmyCommand::SplitArmyCommand(int xFrom, int yFrom, int xTo, int yTo, int soldiers) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo), soldiers(soldiers) {

    }

    CommandTypeId SplitArmyCommand::getCommandTypeId() const {
        return SPLITARMY;
    }

    void SplitArmyCommand::execute(state::State& state, std::stack<Action*>& actionStack) {
        if(!inMap(state,xTo,yTo)) return;
        if(!inMap(state,xFrom,yFrom)) return;
        if(state.getMonde().get(xFrom,yFrom, 2) == NULL) return;
        if(state.getMonde().get(xTo,yTo, 2) != NULL) return;
        
        if(state.getMonde().get(xFrom,yFrom, 2)->getTypeID() == ARMY){
            Army *army = (Army*)state.getMonde().get(xFrom,yFrom, 2);
            if(!canMoveImproved(state, xFrom, yFrom, xTo, yTo, army->getRange())) return;
            if(army->getIdPlayer() != state.getIdPlayer()) return;
            if(army->getSoldiers() > this->soldiers){
                actionStack.push(new SplitArmyAction(xFrom, yFrom, xTo, yTo, soldiers));
                army->setSoldiers(army->getSoldiers() - this->soldiers);
                state.getMonde().set(xTo,yTo,2,new Army(soldiers, state.getIdPlayer()));
            }
            
        }
    }

    void SplitArmyCommand::serialize(Json::Value& out) const {
        out["Type"] = "SplitArmy";
        out["xFrom"] = xFrom;
        out["yFrom"] = yFrom;
        out["xTo"] = xTo;
        out["yTo"] = yTo;
        out["soldiers"] = soldiers;
    }

    SplitArmyCommand* SplitArmyCommand::deserialize(const Json::Value& in) {
        return new SplitArmyCommand(in["xFrom"].asInt(), in["yFrom"].asInt(), in["xTo"].asInt(), in["yTo"].asInt(), in["soldiers"].asInt());
    }


    
    
}