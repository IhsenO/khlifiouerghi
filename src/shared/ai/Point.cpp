/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Point.h"
#include <iostream>

namespace ai{

    Point::Point(int x, int y, int weight) : x(x), y(y), weight(weight) {

    }

    Point Point::transform(Direction d) {
        
        /*
        if(d == UP) this->y++;
        else if(d == RIGHT) this->x++;
        else if(d == LEFT) this->x--;
        else if(d == DOWN) this->y--;
        else std::cout << "Probleme direction" << std::endl;
        */
        Point p(x,y,weight);
        
        if(d == UP) p.y++;
        else if(d == RIGHT) p.x++;
        else if(d == LEFT) p.x--;
        else if(d == DOWN) p.y--;
        else std::cout << "Probleme direction" << std::endl;
        
        
        return p;  
    }

    int Point::getWeight() const {
        return this->weight;
    }

    int Point::getX() const {
        return this->x;
    }

    int Point::getY() const {
        return this->y;
    }

    void Point::setWeight(int weight) {
        this->weight = weight;
    }
    
    
}