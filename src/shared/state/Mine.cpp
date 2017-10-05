/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mine.h"
#include <iostream>

namespace state{
    
    Mine::Mine(){
        this->productionByTurn = 100;
        //std::cout << "Créationd'une Mine" << std::endl;
    }
    
    bool Mine::isProducing() const{
        if(ressourcesToBuild == 0) return false;
        else return true;
    }
    
}
