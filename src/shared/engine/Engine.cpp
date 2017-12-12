/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Engine.h"
#include "ai/AI.h"
#include <iostream>
#include <stack>

using namespace std;
using namespace state;

namespace engine {

    Engine::Engine(state::State& state) : currentState(state) {
        player = 0;
    }

    void Engine::runThread(ai::AI* aiPlayer1, ai::AI* aiPlayer2) {
        stack<Action*> pile;
        while(1){
            //std::cout << player << std::endl;
            //std::cout << this->player << std::endl;
            std::lock_guard<std::mutex> l(mutexFlag);
            if(this->player == 1){
                std::cout << "Joueur 1" << std::endl;
                aiPlayer1->run(*this, pile);
                player = 0;
                currentState.setIdPlayer(2);
            }
            else if(this->player == 2){
                std::cout << "Joueur 2" << std::endl;
                aiPlayer2->run(*this, pile);
                player = 0;
                currentState.setIdPlayer(1);
            }           
            else if(this->player == -1){
                break;
            }
            else{
                
            }
            
                
        }
    }

    int Engine::getPlayer() const {
        std::lock_guard<std::mutex> l(std::mutex);
        return player;
    }

    void Engine::setPlayer(int player) {
        std::lock_guard<std::mutex> l(std::mutex);
        this->player = player;
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