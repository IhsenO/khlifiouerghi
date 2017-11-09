/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include "MobileElement.h"

namespace state{
    
    
    MobileElement::MobileElement(int range){
        //std::cout << "Creation Element Mobile" << std::endl;
        this->range = range;
    }

    int MobileElement::getRange() const {
        return this->range;
    }
    
    
}
