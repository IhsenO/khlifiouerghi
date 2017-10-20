/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Element.h"
#include <iostream>

namespace state{
    
    Element::Element() : x(0), y(0), idPlayer(0) {
        //std::cout << "Construction Element" << std::endl;
    }
    Element::~Element(){        
        std::cout << "destruction d'un Element" << std::endl;
    }
    
    int Element::getX() const { return x; }
    void Element::setX(int x) { this->x = x; }
    int Element::getY() const { return y; }
    void Element::setY(int y) { this->y = y; }
    int Element::getIdPlayer() const { return idPlayer; }
    void Element::setIdPlayer(int idPlayer) { this->idPlayer = idPlayer; }



}