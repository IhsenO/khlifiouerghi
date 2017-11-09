/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Engine.h"

namespace engine {

    Engine::Engine(state::State& state) : currentState(state) {
        
    }

    Engine::~Engine() {
        for(auto c : currentCommands)
            delete c;
    }

    const state::State& Engine::getState() const {
        return this->currentState;
    }

    void Engine::runCommand(Command* command) {
        command->execute(this->currentState);
    }
    

    
}