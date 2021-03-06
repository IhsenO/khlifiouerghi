/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveCharCommand.h"
#include "state/Landscape.h"
#include <iostream>
#include "state/Army.h"
#include "state/Settlers.h"
#include "UtilsEngine.hpp"
using namespace state;

namespace engine{

    MoveCharCommand::MoveCharCommand(int xFrom, int yFrom, int xTo, int yTo) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo){
        
    }

    void MoveCharCommand::execute(State& state, std::stack<Action*>& actionStack) {
        //std::cout << "MoveChar"  <<std::endl;
        if(!inMap(state,xTo,yTo)) return;
        if(!inMap(state,xFrom,yFrom)) return;
        if(state.getMonde().get(xFrom, yFrom, 2) == NULL) return;
        if(state.getMonde().get(xFrom, yFrom, 2)->getIdPlayer() != state.getIdPlayer()) return;
        if(state.getMonde().get(xFrom, yFrom, 2)->getTypeID() == ARMY){
            Army *chars= (Army*)state.getMonde().get(xFrom, yFrom, 2);
            if(canMoveImproved(state, xFrom, yFrom, xTo, yTo, chars->getRange())){
                //std::cout << "Add" << std::endl;
                actionStack.push(new MoveCharAction(xFrom, yFrom, xTo, yTo));
                //std::cout << actionStack.size() << std::endl;
                state.getMonde().set(xTo, yTo, 2, state.getMonde().get(xFrom, yFrom, 2));
                state.getMonde().set(xFrom, yFrom, 2, NULL);
            }               
        }
        else if(state.getMonde().get(xFrom, yFrom, 2)->getTypeID() == SETTLERS){
            Settlers *chars= (Settlers*)state.getMonde().get(xFrom, yFrom, 2);
            if(canMoveImproved(state, xFrom, yFrom, xTo, yTo, chars->getRange())){
                actionStack.push(new MoveCharAction(xFrom, yFrom, xTo, yTo));
                state.getMonde().set(xTo, yTo, 2, state.getMonde().get(xFrom, yFrom, 2));
                state.getMonde().set(xFrom, yFrom, 2, NULL);
            }               
        }
            
        /*
        if(state.getMonde().get(xFrom, yFrom, 2) != NULL && (xFrom != xTo && yFrom != yTo)){
            if(state.getMonde().get(xFrom, yFrom, 2)->getIdPlayer() != state.getIdPlayer()) return;
            if(state.getMonde().get(xTo, yTo, 1) != NULL ){
                if(state.getMonde().get(xTo, yTo, 1)->getTypeID() == LANDSCAPE){
                   Landscape *l = (Landscape*)state.getMonde().get(xTo, yTo, 1); 
                   if(l->isAccessible() == false) return;
                }
            }
            if(state.getMonde().get(xFrom, yFrom, 2)->getTypeID() == ARMY){
                Army *chars= (Army*)state.getMonde().get(xFrom, yFrom, 2);
                if(abs(xFrom - xTo) <= chars->getRange()){
                    state.getMonde().set(xTo, yTo, 2, state.getMonde().get(xFrom, yFrom, 2));
                    state.getMonde().set(xFrom, yFrom, 2, NULL);
                }   
            }
            else if(state.getMonde().get(xFrom, yFrom, 2)->getTypeID() == SETTLERS){
                Settlers *chars = (Settlers*)state.getMonde().get(xFrom, yFrom, 2);
                if(abs(xFrom - xTo) <= chars->getRange()){
                    state.getMonde().set(xTo, yTo, 2, state.getMonde().get(xFrom, yFrom, 2));
                    state.getMonde().set(xFrom, yFrom, 2, NULL);
                }
            }       
        }
        */
        
        
    }

    CommandTypeId MoveCharCommand::getCommandTypeId() const {
        return MOVECHAR;
    }

    void MoveCharCommand::serialize(Json::Value& out) const {
        out["Type"] = "MoveChar";
        out["xFrom"] = xFrom;
        out["yFrom"] = yFrom;
        out["xTo"] = xTo;
        out["yTo"] = yTo;
    }

    MoveCharCommand* MoveCharCommand::deserialize(const Json::Value& in) {
        return new MoveCharCommand(in["xFrom"].asInt(), in["yFrom"].asInt(), in["xTo"].asInt(), in["yTo"].asInt());
    }
    
    
}