/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CommandsService.h"
#include "Game.h"
#include <iostream>



namespace server{

    CommandsService::CommandsService(Game& game) : AbstractService("/commands"), game(game) {

    }

    HttpStatus CommandsService::get(Json::Value& out, int id) const {
        
        if(!this->game.getCurrentCommands().empty() && game.getIdPlayer() != id){
            std::cout << game.getCurrentCommands() << std::endl;
            out = game.getCurrentCommands();
            game.clearCommands();
            if(game.getIdPlayer() == 1) game.setIdPlayer(2);
            else game.setIdPlayer(1);
            return HttpStatus::OK;
        }
        else{
            return HttpStatus::NO_CONTENT;
        }
    }

    HttpStatus CommandsService::put(Json::Value& out, const Json::Value& in) {
        //std::cout << game.getCurrentCommands() << std::endl;
        if(this->game.getCurrentCommands().empty()){
            game.setCurrentCommands(in);
            out["idP"] = game.getIdPlayer();
            //std::cout << game.getCurrentCommands() << std::endl;
            return HttpStatus::CREATED;
        }
        else{
            out["idP"] = game.getIdPlayer();
            return HttpStatus::OUT_OF_RESSOURCES;
        }
    }

    
}