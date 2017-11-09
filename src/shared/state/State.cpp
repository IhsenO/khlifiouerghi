/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "State.h"

namespace state{

    State::State(Monde& monde): monde(monde) {
        this->nbTurns = 0;
        this->idPlayer = 1;
    }

    Monde& State::getMonde() const {
        return this->monde;
    }

    void State::addPlayer(Player* player) {
        player->setId(this->players.size());
        this->players.push_back(player);
    }

    Player* State::getPlayer(int idPlayer) const {
        return this->players[idPlayer];
    }

    State::~State() {
        for(auto p : players)
            delete p;
    }

    
}