/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Barrack.h"
#include <iostream>

namespace state{
    
    Barrack::Barrack(){
        this->productionByTurn = 50;
        //std::cout << "Créationd'une Barrack" << std::endl;
    }
    
    bool Barrack::isProducing() const{
        if(ressourcesToBuild == 0) return false;
        else return true;
    }

    ConstructionTypeId Barrack::getConstructionId() const {
        return BARRACK;
    }

    int Barrack::getSoldiersCost() const {
        return 100;
    }

    int Barrack::getSoldiersFood() const {
        return 250;
    }

    
}