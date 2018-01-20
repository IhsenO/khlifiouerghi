/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "PlayerService.h"
#include "ServiceException.h"
#include <iostream>

namespace server{

    PlayerService::PlayerService(Game& game) : AbstractService("/player"), game(game) {

    }

    HttpStatus PlayerService::get(Json::Value& out, int id) const {
        //if(game.getPlayers().size) out["name"] = game.player(id).name;
        if(id<0){
            for(int i = 0; i < 2; i++){
                if(game.player(i)){    
                    Json::Value tmp;
                    tmp["name"] = game.player(i)->name;
                    out.append(tmp);
                }
            }
        }
        else if(id>=0 && id < game.getPlayersLimit()){
            if(game.player(id)){
                //throw ServiceException(HttpStatus::NO_CONTENT,"Le Joueur demandé n'existe pas");
                out["name"] = game.player(id)->name;
            }
            else throw ServiceException(HttpStatus::NOT_FOUND,"Le Joueur demandé n'existe pas");
        }
        return HttpStatus::OK;
    }

    HttpStatus PlayerService::post(const Json::Value& in, int id) {
        
        //if(id >= 0 && id <2)
        Player *p = game.player(id);
        if(!p) throw ServiceException(HttpStatus::NOT_FOUND,"Invalid user id");
        else{
            if(in.isMember("name")){
                p->name = in["name"].asString();
            }
        }

        return HttpStatus::NO_CONTENT;
    }

    HttpStatus PlayerService::put(Json::Value& out, const Json::Value& in) {
       
        if(game.isFullOfPlayers()){
            throw ServiceException(HttpStatus::OUT_OF_RESSOURCES,"Plus de place");
            //return HttpStatus::OUT_OF_RESSOURCES;
        }
            //std::cout << "Okay" << std::endl;
        std::string name = in["name"].asString();
        Player *newPlayer = new Player();
        newPlayer->name = name;
        int add = game.addPlayer(newPlayer);
        if(add != -1){
            out["id"] = add;
            return HttpStatus::CREATED;
        }
        else{
            throw ServiceException(HttpStatus::OUT_OF_RESSOURCES,"Plus de place");
            //return HttpStatus::OUT_OF_RESSOURCES;
        }
    }

    HttpStatus PlayerService::remove(int id) {
        game.removePlayer(id);
        return HttpStatus::NO_CONTENT;
    }
    
    
}
 