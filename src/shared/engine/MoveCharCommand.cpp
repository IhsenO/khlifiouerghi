/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveCharCommand.h"
#include <iostream>

namespace engine{

    MoveCharCommand::MoveCharCommand(int xFrom, int yFrom, int xTo, int yTo) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo){
        
    }

    void MoveCharCommand::execute(state::State& state) {
        if(state.getMonde().get(xFrom, yFrom, 2) != NULL){
            if(state.getMonde().get(xFrom, yFrom, 2)->getTypeID() == state::ARMY){
                std::cout << "OK" << std::endl;
                state.getMonde().set(xTo, yTo, 2, state.getMonde().get(xFrom, yFrom, 2));
                state.getMonde().set(xFrom, yFrom, 2, NULL);
            }
        }
    }

    CommandTypeId MoveCharCommand::getCommandTypeId() const {
        return MOVECHAR;
    }
    
}