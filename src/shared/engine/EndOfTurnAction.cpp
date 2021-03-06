/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "EndOfTurnAction.h"
#include <iostream>
#include "state/City.h"

using namespace state;
using namespace std;


namespace engine{

    EndOfTurnAction::EndOfTurnAction() {

    }

    void EndOfTurnAction::undo(state::State& state) {
        
        std::cout << "Fin du tour undo !" << std::endl;
        for(int i = 0; i < state.getMonde().getHeight(); i++)
            for(int j = 0; j < state.getMonde().getWidth(); j++){
                if(state.getMonde().get(j,i,1) != NULL){
                    if(state.getMonde().get(j,i,1)->getTypeID() == CITY && state.getMonde().get(j,i,1)->getIdPlayer() == state.getIdPlayer()){
                        City *c = (City*)state.getMonde().get(j,i,1);
                        for(unsigned int k = 0; k < c->getListConst().size(); k++){
                            if(c->getListConst()[k]->getConstructionId() == MINE){
                                int gold = state.getPlayer(state.getIdPlayer())->getGold();
                                state.getPlayer(state.getIdPlayer())->setGold(gold - c->getListConst()[k]->getProductionByTurn());
                            }
                            else if(c->getListConst()[k]->getConstructionId() == FARM){
                                int food = state.getPlayer(state.getIdPlayer())->getFood();
                                state.getPlayer(state.getIdPlayer())->setFood(food - c->getListConst()[k]->getProductionByTurn());
                            }
                            
                        }
                    }
                }
            }
        
    }
    
    
    
}