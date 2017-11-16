/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "UtilsAI.hpp"

bool isInMap(State& state, int x, int y){
    
    if(x < 0 || x >= state.getMonde().getWidth() || y < 0 || y >= state.getMonde().getHeight()) return false;
    else return true;
    
}

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

bool enemyArmy(State& state, int x, int y){
    
    if(!isInMap(state,x,y)) return false;
    if(state.getMonde().get(x,y,2) == NULL) return false;
    if(state.getMonde().get(x,y,2)->getTypeID() == ARMY){
        if(state.getMonde().get(x,y,2)->getIdPlayer() != state.getIdPlayer()) return true;
        else return false;
    }
    else return false;
    
}


bool friendlyArmy(State& state, int x, int y){
    
    if(!isInMap(state,x,y)) return false;
    if(state.getMonde().get(x,y,2) == NULL) return false;
    if(state.getMonde().get(x,y,2)->getTypeID() == ARMY){
        if(state.getMonde().get(x,y,2)->getIdPlayer() == state.getIdPlayer()) return true;
        else return false;
    }
    else return false;
    
}

bool enemyCity(State& state, int x, int y){
    
    if(!isInMap(state,x,y)) return false;
    if(state.getMonde().get(x,y,1) == NULL) return false;
    if(state.getMonde().get(x,y,1)->getTypeID() == CITY){
        if(state.getMonde().get(x,y,1)->getIdPlayer() != state.getIdPlayer()) return true;
        else return false;
    }
    else return false;
    
}