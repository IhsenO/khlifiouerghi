/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "UtilsEngine.hpp"

bool inMap(State& state, int x, int y){
    
    if(x < 0 || x >= state.getMonde().getWidth() || y < 0 || y >= state.getMonde().getHeight()) return false;
    else return true;
    
}


bool canAccess(State& state, int x, int y){
    
    if(!inMap(state,x,y)) return false;
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

bool hasWonBattle(float a, float b){
    //srand(time(NULL));
    mt19937 mt_rand(time(0));
    float meanSoldiers = (a+b)/2;
    float difference = (a - b) / meanSoldiers;
    float probability = 1/(1+exp(-4*difference));
    float randNumber = (float)(mt_rand() % 100);
    //float randNumber = rand() % 100;
    //std:: cout << difference << " proba " << probability << std::endl;
    //std:: cout << randNumber << " PROBA " << probability*100 << std::endl;
    if(randNumber <= probability*100){
        std:: cout << "Victoire" << std::endl;
        return true;
    }
    else{
        std::cout << "Defaite" << std::endl;
        return false;
    }   
}

bool canReachSimple(int xFrom, int yFrom, int xTo, int yTo, int range){

    if(abs(xFrom - xTo) <= range && abs(yFrom - yTo) <= range)
        return true;
    else
        return false;
}

bool canMoveSimple(State& state,int xFrom, int yFrom, int xTo, int yTo, int range){
    if(canReachSimple(xFrom, yFrom, xTo, yTo, range)){
        if(canAccess(state, xTo, yTo))
            return true;        
        else 
            return false;        
    }
    else
        return false;
}

bool canReachImproved(int xFrom, int yFrom, int xTo, int yTo, int range){

    //if(abs(xFrom - xTo) <= range && abs(yFrom - yTo) <= range)
    if(sqrt((xFrom-xTo)*(xFrom-xTo) + (yFrom-yTo)*(yFrom-yTo)) <= range)
        return true;
    else
        return false;
}

bool canMoveImproved(State& state,int xFrom, int yFrom, int xTo, int yTo, int range){
    if(canReachImproved(xFrom, yFrom, xTo, yTo, range)){
        if(canAccess(state, xTo, yTo))
            return true;        
        else 
            return false;        
    }
    else
        return false;
}


