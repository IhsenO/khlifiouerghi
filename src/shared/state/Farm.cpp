/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Farm.h"
#include <iostream>

namespace state{
    
    Farm::Farm(){
        this->productionByTurn = 500;
        //std::cout << "Créationd'une Farm" << std::endl;
    }
    
    bool Farm::isProducing() const{
        if(ressourcesToBuild == 0) return false;
        else return true;
    }
  
    ConstructionTypeId Farm::getConstructionId () const{
        return FARM;
    }

}