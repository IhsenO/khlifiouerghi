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
    
    TypeID City::getTypeID() const{
        return CITY;
    }
    
    bool City::isFree() const{ }
    
    bool City::isBuilding() const{}
    
    bool City::isAccessible() const{ return false; }
    
    bool City::isInteractive() const{ return true; }
    
    bool City::isStatic() const{ return true; }

    //void City::setListConst(const std::vector<Construction*>& listConst) { listConst(listConst); }
    void City::addConstruction(Construction* construction) {
        this->listConst.push_back(construction);
    }
    const std::vector<Construction*>& City::getListConst() const {

    }
    bool City::isFullOfConstructions() const {
        if(this->listConst.size()==3) return true;
        else return false;
    }





}
