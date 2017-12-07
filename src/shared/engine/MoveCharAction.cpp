/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MoveCharAction.h"
#include "state/Army.h"

using namespace std;
using namespace state;

namespace engine{

    MoveCharAction::MoveCharAction(int xFrom, int yFrom, int xTo, int yTo) : xFrom(xFrom), yFrom(yFrom), xTo(xTo), yTo(yTo){
        
    }

    void MoveCharAction::undo(state::State& state) {
        //Army *chars= (Army*)state.getMonde().get(xTo, yTo, 2);
        state.getMonde().set(xFrom, yFrom, 2, state.getMonde().get(xTo, yTo, 2));
        state.getMonde().set(xTo, yTo, 2, NULL);
    }
    
}