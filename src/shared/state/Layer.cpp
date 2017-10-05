/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Layer.h"

#include "Element.h"
#include <iostream>

namespace state{

    Layer::Layer(int width, int height) : tab(width*height), width(width), height(height){
        //std::cout << "Layer " << tab.size() << std::endl;
    }
    Element* Layer::get(int x, int y) const {
        return tab[y*width + x];
    }
    void Layer::set(int x, int y, Element* e) {
        tab[y*width + x] = e;
    }

}