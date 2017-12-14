/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "EndOfTurnCommand.h"
#include "state/City.h"
#include "EndOfTurnAction.h"
#include <iostream>

using namespace state;

namespace engine{

    EndOfTurnCommand::EndOfTurnCommand() {

    }

    CommandTypeId EndOfTurnCommand::getCommandTypeId() const {
        return EOT;
    }

    void EndOfTurnCommand::execute(State& state, std::stack<Action*>& actionStack) {
        actionStack.push(new EndOfTurnAction());
        std::cout << "Fin du tour !" << std::endl;
        for(int i = 0; i < state.getMonde().getHeight(); i++)
            for(int j = 0; j < state.getMonde().getWidth(); j++){
                if(state.getMonde().get(j,i,1) != NULL){
                    if(state.getMonde().get(j,i,1)->getTypeID() == CITY && state.getMonde().get(j,i,1)->getIdPlayer() == state.getIdPlayer()){
                        City *c = (City*)state.getMonde().get(j,i,1);
                        for(unsigned int k = 0; k < c->getListConst().size(); k++){
                            if(c->getListConst()[k]->getConstructionId() == MINE){
                                int gold = state.getPlayer(state.getIdPlayer())->getGold();
                                state.getPlayer(state.getIdPlayer())->setGold(gold + c->getListConst()[k]->getProductionByTurn());
                            }
                            else if(c->getListConst()[k]->getConstructionId() == FARM){
                                int food = state.getPlayer(state.getIdPlayer())->getFood();
                                state.getPlayer(state.getIdPlayer())->setFood(food + c->getListConst()[k]->getProductionByTurn());
                            }
                            
                        }
                    }
                }
            }
    }

    void EndOfTurnCommand::serialize(Json::Value& out) const {
        out["Type"] = "EndOfTurn";
    }

    EndOfTurnCommand* EndOfTurnCommand::deserialize(const Json::Value& in) {
        return new EndOfTurnCommand();
    }

    
    
}