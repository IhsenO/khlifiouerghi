/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "City.h"
#include <iostream>

namespace state{
    
    City::City() {
        this->defense = 1;
        //std::cout << "Création d'une City" << std::endl;
    }

    City::City(int defense, bool free) : defense(defense), free(free) {
        
    }


    
    TypeID City::getTypeID() const{
        return CITY;
    }
    
    bool City::isFree() const{ return free; }
    
    bool City::isBuilding() const{ return building; }
    
    bool City::isAccessible() const{ return false; }
    
    bool City::isInteractive() const{ return true; }
    
    bool City::isStatic() const{ return true; }

    //void City::setListConst(const std::vector<Construction*>& listConst) { listConst(listConst); }
    void City::addConstruction(Construction* construction) {
        this->listConst.push_back(construction);
    }

    bool City::isFullOfConstructions() const {
        if(this->listConst.size()==3) return true;
        else return false;
    }





}
