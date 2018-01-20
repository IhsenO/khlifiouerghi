/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GameService.h"
#include "Game.h"

namespace server{

    GameService::GameService(Game& game) : AbstractService("/game"), game(game) {

    }

    HttpStatus GameService::get(Json::Value& out, int id) const {
        out["idPlayer"] = this->game.getIdPlayer();
        return HttpStatus::OK;
    }
    
    
}