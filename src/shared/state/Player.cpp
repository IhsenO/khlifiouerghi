/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "Player.h"

namespace state{
    
    Player::Player() : gold(0), food(0), playing(false), id(-1) {
        //std::cout << "Création Player" << std::endl;
    }

    Player::Player(std::string nom) : name(nom) {
        this->food = 1000;
        this->gold = 1000;
    }

    
    bool Player::isPlaying () const {return playing;}

    const std::string& Player::getName() const {return name;}
    void Player::setName(const std::string& name) { this->name = name; }
    int Player::getGold() const {return gold;}
    void Player::setGold(int gold) { this->gold = gold;}
    int Player::getFood() const {return food;}
    void Player::setFood(int food) { this->food = food;}
    void Player::setPlaying(bool playing) { this->playing = playing;}
    int Player::getId() const {return id;}
    void Player::setId(int id) { this->id = id;} 
    
    Player::~Player(){
        //std::cout << "Destruction Player" << std::endl;
    } 
    
    
    
}