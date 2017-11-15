/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "UtilsAI.hpp"

bool canBuildConstruction(State& state, int xFrom, int yFrom, ConstructionTypeId type){
    if(state.getPlayer(state.getIdPlayer())->getGold() > 500){
        City *c = (City*)state.getMonde().get(xFrom, yFrom, 1); 
        if(c->canBuild(type))
            return true;
        else
            return false;
            
    }
    else return false;
}

bool canUpgrade(State& state, int x, int y){
    if(state.getPlayer(state.getIdPlayer())->getGold() > 500 && state.getPlayer(state.getIdPlayer())->getFood() > 500){
        City *c = (City*)state.getMonde().get(x, y, 1); 
        if(c->getDefense() < 3)
            return true;
        else return false;        
    }
    else return false;
    
}

bool canMakeSoldiers(State& state){
    
    Barrack b;
    if(state.getPlayer(state.getIdPlayer())->getGold() > b.getSoldiersCost() && state.getPlayer(state.getIdPlayer())->getFood() > b.getSoldiersFood())
        return true;
    else
        return false;
}