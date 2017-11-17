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
        this->soldiers = 100;
    }

    City::~City() {
        std::cout << "Delete" << std::endl;
        //for(int i = 0; i < this->listConst.size(); i++)
        //    delete this->listConst[i];
        for(auto& construction : listConst)
            delete construction;
    }
    
    
    City::City(int defense, bool free) : defense(defense), free(free) {
        this->soldiers = 100;
    }
    
    City::City(int defense, bool free, int player) : defense(defense), free(free) {
        this->idPlayer = player;
        this->soldiers = 100;
    }

    int City::getDefense() const {
        return this->defense;
    }

    void City::setDefense(int defense) {
        this->defense = defense;
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

    bool City::canBuild(int id) const {
        if(this->listConst.size()==3) return false;
        for(unsigned int i = 0; i < listConst.size(); i++){
            if(listConst[i]->getConstructionId() == id)
                return false;
        }
        return true;
    }

    const std::vector<Construction*>& City::getListConst() const {
        return this->listConst;
    }

    int City::getSoldiers() const {
        return this->soldiers;
    }

    void City::setSoldiers(int soldiers) {
        this->soldiers = soldiers;
    }

    void City::setFree(bool free) {
        this->free = free;
    }

    bool City::getFree() const {
        return this->free;
    }

    

}
