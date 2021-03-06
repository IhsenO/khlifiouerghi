/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "ConstructCommand.h"
#include "UtilsEngine.hpp"
#include <iostream>
using namespace state;

namespace engine{

    ConstructCommand::ConstructCommand(int x, int y, Construction* construction) : x(x), y(y), construction(construction) {

    }

    CommandTypeId ConstructCommand::getCommandTypeId() const {
        return CONSTRUCT;
    }

    
    void ConstructCommand::execute(State& state, std::stack<Action*>& actionStack) { 
        //std::cout << "ConstructCommand" << std::endl;
        if(!inMap(state,x,y)) return;
        if(state.getMonde().get(x, y, 1) == NULL) return;
        if(state.getMonde().get(x, y, 1)->getTypeID() == state::CITY){
            City *c = (City*)state.getMonde().get(x, y, 1);
            if(c->getIdPlayer() != state.getIdPlayer()) return;            
            if(c->canBuild(this->construction->getConstructionId())){
                actionStack.push(new ConstructAction(x,y,construction));
                c->addConstruction(this->construction);
                Player *p = state.getPlayer(c->getIdPlayer());
                p->setGold(p->getGold() - construction->getCost());
            }
        }                
    }

    void ConstructCommand::serialize(Json::Value& out) const {
        out["Type"] = "Construct";
        out["x"] = x;
        out["y"] = y;
        out["constructType"] = (int)construction->getConstructionId();
    }

    ConstructCommand* ConstructCommand::deserialize(const Json::Value& in) {
        if(in["constructType"] == 1){
            return new ConstructCommand(in["x"].asInt(), in["y"].asInt(), new Farm());
        }
        else if(in["constructType"] == 2){
            return new ConstructCommand(in["x"].asInt(), in["y"].asInt(), new Mine());
        }
        else if(in["constructType"] == 3){
            return new ConstructCommand(in["x"].asInt(), in["y"].asInt(), new Barrack());
        }  
        else{
            std::cout << "Probleme ConstructTypeID" << std::endl;
            return NULL;
        }
    }
    
 
    
}