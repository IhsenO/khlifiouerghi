/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Army.h"
#include <iostream>

namespace state{

    Army::Army() {
        this->range = 5;
        std::cout << "Création d'une Army" << std::endl;
    }


    int Army::getSoldiers() const { return soldiers; }


    TypeID Army::getTypeID() const {  }


    bool Army::isInCity() const { }


    bool Army::isInteractive() const { return true; }

    bool Army::isStatic() const { return false; }


    bool Army::isMoving() const { }


    void Army::setSoldiers(int soldiers) {
        this->soldiers = soldiers;
    }

}