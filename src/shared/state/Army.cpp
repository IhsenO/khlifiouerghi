/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Army.h"

namespace state{

Army(){}
TypeID Army::getTypeID(){}
//bool const Army::equals (const Element& other){}
bool const Army::isMoving(){return true;}
int Army::getSoldiers() const{return this->soldiers;}
void Army::setSoldiers(int soldiers){this->soldiers=soldiers;}

}