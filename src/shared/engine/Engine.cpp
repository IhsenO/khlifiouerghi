/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Engine.h"
#include <iostream>

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

    void Engine::runCommand(Command* command, std::stack<Action*>& actionStack) {
        command->execute(this->currentState, actionStack);
    }

    void Engine::undo(std::stack<Action*>&  actionStack) {
        if(actionStack.size()>0){
            std::cout << actionStack.size() << std::endl;
            actionStack.top()->undo(currentState);
            actionStack.pop();
            std::cout << actionStack.size() << std::endl;
        }
    }

    
}