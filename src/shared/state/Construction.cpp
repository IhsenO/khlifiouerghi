/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Construction.h"
#include <iostream>

namespace state{
    
    Construction::Construction() : level(1), ressourcesToBuild(0) {
        std::cout << "Création d'une Construction" << std::endl;
    }
    
    
    
}
