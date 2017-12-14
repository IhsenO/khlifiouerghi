/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Engine.h"
#include "ai/AI.h"
#include <iostream>
#include <stack>
#include "unistd.h"
#include "ArmyFusionCommand.h"
#include "AttackArmyCommand.h"
#include "AttackCityCommand.h"
#include "ConstructCommand.h"
#include "EnterCityCommand.h"
#include "EndOfTurnCommand.h"
#include "LeaveCityCommand.h"
#include "MakeSoldiersCommand.h"
#include "MoveCharCommand.h"
#include "SplitArmyCommand.h"
#include "UpgradeCommand.h"
#include <thread>
#include <chrono>

using namespace std;
using namespace state;

namespace engine {

    Engine::Engine(state::State& state) : currentState(state) {
        player = 0;
        listCommandPlayer = new Json::Value();
        //Json::Value listCommandPlayer;
    }

    void Engine::runThread(ai::AI* aiPlayer1, ai::AI* aiPlayer2) {
        stack<Action*> pile;
        while(1){
            //std::cout << player << std::endl;
            //std::cout << this->player << std::endl;
            std::lock_guard<std::mutex> l(mutexFlag);
            if(this->player == 1){
                std::cout << "Joueur 1" << std::endl;
                aiPlayer1->run(*this, pile, false);
                player = 0;
                currentState.setIdPlayer(2);
            }
            else if(this->player == 2){
                std::cout << "Joueur 2" << std::endl;
                aiPlayer2->run(*this, pile, false);
                player = 0;
                currentState.setIdPlayer(1);
            }           
            else if(this->player == -1){
                break;
            }
            else{
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
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

    void Engine::runCommand(Command* command, std::stack<Action*>& actionStack, bool serialize) {
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

    //const Json::Value*& Engine::getListCommandPlayer() const {
    //    return *listCommandPlayer;
    //}

    Json::Value* Engine::getValueJson() const {
        return listCommandPlayer;
    }

    void Engine::runCommandJson(Json::Value& commandJson, std::stack<Action*>& actionStack) {
        if(commandJson["Type"].asString() == "ArmyFusion"){
            ArmyFusionCommand *fusCmd = new ArmyFusionCommand(-1,-1,-1,-1);
            fusCmd = fusCmd->deserialize(commandJson);
            fusCmd->execute(currentState, actionStack);
            delete fusCmd;
        }
        else if(commandJson["Type"].asString() == "AttackArmy"){
            AttackArmyCommand *attAr = new AttackArmyCommand(-1,-1,-1,-1);
            attAr = attAr->deserialize(commandJson);
            attAr->execute(currentState, actionStack);
            delete attAr;
        }
        else if(commandJson["Type"].asString() == "AttackCity"){
            AttackCityCommand *atCity = new AttackCityCommand(-1,-1,-1,-1);
            atCity = atCity->deserialize(commandJson);
            atCity->execute(currentState, actionStack);
            delete atCity;
        }
        else if(commandJson["Type"].asString() == "Construct"){
            ConstructCommand *cmdConst = new ConstructCommand(-1,-1,NULL);
            cmdConst = cmdConst->deserialize(commandJson);
            cmdConst->execute(currentState, actionStack);
            delete cmdConst;
        }
        else if(commandJson["Type"].asString() == "EndOfTurn"){
            EndOfTurnCommand *end = new EndOfTurnCommand();
            end = end->deserialize(commandJson);
            end->execute(currentState, actionStack);
            delete end;
        }
        else if(commandJson["Type"].asString() == "EnterCity"){
            EnterCityCommand *enter = new EnterCityCommand(-1,-1,-1,-1,-1);
            enter = enter->deserialize(commandJson);
            enter->execute(currentState, actionStack);
            delete enter;
        }
        else if(commandJson["Type"].asString() == "LeaveCity"){
            LeaveCityCommand *leave = new LeaveCityCommand(-1,-1,-1,-1,-1);
            leave = leave->deserialize(commandJson);
            leave->execute(currentState, actionStack);
            delete leave;
        }
        else if(commandJson["Type"].asString() == "MakeSoldiers"){
            MakeSoldiersCommand *make = new MakeSoldiersCommand(-1,-1);
            make = make->deserialize(commandJson);
            make->execute(currentState, actionStack);
        }
        else if(commandJson["Type"].asString() == "MoveChar"){
            MoveCharCommand *move = new MoveCharCommand(-1,-1,-1,-1);
            move = move->deserialize(commandJson);
            move->execute(currentState, actionStack);
            delete move;
        }
        else if(commandJson["Type"].asString() == "SplitArmy"){
            SplitArmyCommand *split = new SplitArmyCommand(-1,-1,-1,-1,-1);
            split = split->deserialize(commandJson);
            split->execute(currentState, actionStack);
            delete split;
        }
        else if(commandJson["Type"].asString() == "Upgrade"){
            UpgradeCommand *up = new UpgradeCommand(-1,-1);
            up = up->deserialize(commandJson);
            up->execute(currentState, actionStack);
            delete up;
        }
        else{
            cout << "Problème !" << endl;
            cout << commandJson["Type"].asString() << endl;
        }
        
    }

    void Engine::runListCommandJson(Json::Value& listCommandsJson, std::stack<Action*>& stack) {
        for(int i = 0; i < (int)listCommandsJson.size(); i++){
            this->runCommandJson(listCommandsJson[i], stack);
        }
    }
    
}