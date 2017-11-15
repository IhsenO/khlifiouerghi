/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MakeSoldiersCommand.h"
#include "state/City.h"
#include "state/Barrack.h"
#include <iostream>

using namespace state;

namespace engine{
    MakeSoldiersCommand::MakeSoldiersCommand(int x, int y) :x(x), y(y) {

    }

    CommandTypeId MakeSoldiersCommand::getCommandTypeId() const {
        return MAKESOLDIERS;
    }

    void MakeSoldiersCommand::execute(state::State& state) {
        std::cout << "MakeSoldiers" << std::endl;
        if(state.getMonde().get(x, y, 1) == NULL) return;
        if(state.getMonde().get(x, y, 1)->getTypeID() == state::CITY){
            City *c = (City*)state.getMonde().get(x, y, 1);
            if(c->getIdPlayer() != state.getIdPlayer()) return;
            
            for(Construction *construction : c->getListConst()){
            //for(int i = 0; i < c->getListConst().size(); i++){
                if(construction->getConstructionId() == BARRACK){
                    Barrack *b = (Barrack*)construction;
                    if(state.getPlayer(state.getIdPlayer())->getGold() >= b->getSoldiersCost() && state.getPlayer(state.getIdPlayer())->getFood() >= b->getSoldiersFood()){
                        c->setSoldiers(c->getSoldiers() + b->getProductionByTurn());
                        state.getPlayer(state.getIdPlayer())->setGold(state.getPlayer(state.getIdPlayer())->getGold() - b->getSoldiersCost());
                        state.getPlayer(state.getIdPlayer())->setFood(state.getPlayer(state.getIdPlayer())->getFood() - b->getSoldiersFood());
                    }
                    else return;
                }
                //else{
                //    return;
                //}
            }
                       
            
        }
    }
    
    
}