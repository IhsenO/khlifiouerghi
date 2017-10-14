/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Landscape.h"
#include <iostream>


namespace state{
    
    Landscape::Landscape() {
    }

    int Landscape::getType() const { return type; }
    
    TypeID Landscape::getTypeID() const {
        return LANDSCAPE;
    }

    bool Landscape::isAccessible() const {
        return accessible;
    }

    
    bool Landscape::isInteractive() const { return false; }
    
    bool Landscape::isStatic() const { return true; }
    
    void Landscape::setType(int type) {
        this->type = type;
    }
}
