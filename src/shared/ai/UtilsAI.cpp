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

bool canAccessAI(State& state, int x, int y){
    
    if(!isInMap(state,x,y)) return false;
    if(state.getMonde().get(x,y,2) != NULL) return false;
    if(state.getMonde().get(x,y,1) != NULL){
        if(state.getMonde().get(x,y,1)->getTypeID() == LANDSCAPE){
            Landscape *l = (Landscape*)state.getMonde().get(x,y,1);
            if(l->isAccessible())
                return true;
            else
                return false;
        }
        else
            return false;
        
    }
    else  
        return true;
       
}

bool canAccessAIDist(State& state, int x, int y){
    
    if(!isInMap(state,x,y)) return false;
    //if(state.getMonde().get(x,y,2) != NULL) return false;
    if(state.getMonde().get(x,y,1) != NULL){
        if(state.getMonde().get(x,y,1)->getTypeID() == LANDSCAPE){
            Landscape *l = (Landscape*)state.getMonde().get(x,y,1);
            if(l->isAccessible())
                return true;
            else
                return false;
        }
        else if(state.getMonde().get(x,y,1)->getTypeID() == CITY) 
            return true;
        else 
            return false;
        
    }
    else  
        return true;
       
}

bool canReachImprovedAI(int xFrom, int yFrom, int xTo, int yTo, int range){

    //if(abs(xFrom - xTo) <= range && abs(yFrom - yTo) <= range)
    if(sqrt((xFrom-xTo)*(xFrom-xTo) + (yFrom-yTo)*(yFrom-yTo)) <= range)
        return true;
    else
        return false;
}

bool canMoveImprovedAI(State& state,int xFrom, int yFrom, int xTo, int yTo, int range){
    if(canReachImprovedAI(xFrom, yFrom, xTo, yTo, range)){
        if(canAccessAI(state, xTo, yTo))
            return true;        
        else 
            return false;        
    }
    else
        return false;
}

void findBestMoveAI(State& state, int& xBest, int& yBest, int range, vector<int> map){
    int x = xBest;
    int y = yBest;
    int best = map[yBest*state.getMonde().getWidth() + xBest];
    for(int k = y-2; k < y+3; k++)
        for(int l = x-2; l < x+3; l++){
            if(canMoveImprovedAI(state, x, y, l, k, range)){
                if(map[k*state.getMonde().getWidth() + l] < best){
                    best = map[k*state.getMonde().getWidth() + l];
                    xBest = l;
                    yBest = k;
                }
            }
        }
        
                                
    
}