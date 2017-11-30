/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CommandsWeights.h"

using namespace std;
using namespace engine;

namespace ai{

    CommandsWeights::CommandsWeights(engine::Command* command, int weight) : command(command), weight(weight) {
        
    }

    engine::Command* CommandsWeights::getCommand() const {
        return this->command;
    }

    

//    const engine::Command*& CommandsWeights::getCommand() const {
//        return this->command;
//    }

    int CommandsWeights::getWeight() const {
        return this->weight;
    }
        
    void CommandsWeights::setWeight(int weight) {
        this->weight = weight;
    }
    
    
    
}