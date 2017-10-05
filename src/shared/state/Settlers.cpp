/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "Settlers.h"

namespace state{
    
    Settlers::Settlers() {
        this->range = 10;
        //std::cout << "Création d'un Settler" << std::endl;
    }
    Settlers::~Settlers(){
        //std::cout << "Destruction d'un Settler" << std::endl;
        
    }
  
    //bool Settlers::getRange(){ return this->range; }
    //void Settlers::setRange(int range){ this->range = range;}
    
    TypeID Settlers::getTypeID() const{
        return SETTLERS;
    }
   

    bool Settlers::isInCity() const {

    }

    bool Settlers::isInteractive() const {
        return true;
    }

    bool Settlers::isStatic() const{ return false; }

    bool Settlers::isMoving() const{

    }
    
}