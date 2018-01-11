/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdexcept>
#include "Game.h"

namespace server{

    Game::Game(int playersLimit) : players(playersLimit) {
        for(int i = 0; i < 2; i++)
            players[i] = NULL;
    }

    int Game::getPlayersLimit() const {
        return playersLimit;
    }
    
//    const std::vector<Player>& Game::getPlayers() const {
//        return this->players;
//    }

    Player* Game::player(int i) {
        if(i >= 0 && i < (int)players.size()) return this->players[i];
        else return NULL;
    }

    int Game::addPlayer(Player *player) {
        for(int i = 0; i < (int)players.size(); i++){
            if(players[i] == NULL){
                players[i] = player;
                return i;
            }
            
        }
        return -1;
    }

    void Game::removePlayer(int id) {
        if(id>=0 && id < (int)players.size()) players[id] = NULL;
    }

    bool Game::isFullOfPlayers() {
        //if(players[0] != NULL && players[1] != NULL) return true;
        //else return false;
        bool full = true;
        for(int i = 0; i < (int)players.size(); i++){
            if(players[i] == NULL){
                return false;
            }
        }
        return full;
    }
    
    
}