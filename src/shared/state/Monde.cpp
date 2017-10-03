/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Monde.h"
#include <iostream>

namespace state{
    Monde::Monde(int width, int height, int depth) : width(width), height(height), nbLayers(depth), layers(depth) {
        for(int i = 0; i < depth; i++){
            //layers[i] = std::unique_ptr<Layer>(new Layer(width, height));
            layers[i] = new Layer(width, height);
        }
        std::cout << "Monde " << layers.size() << std::endl;
    }
    
    Monde::~Monde() {
    }
    
    std::vector<Layer*> Monde::getLayers() const {
        return this->layers;
    }
       
    void Monde::set(int x, int y, int layer, Element* e) {
        layers[layer]->set(x,y,e);
    }
    int Monde::getWidth() const {
        return this->width;
    }    
    int Monde::getHeight() const {
        return this->height;
    }

    Element* Monde::get(int x, int y, int layer) const {
        //std::cout << "getMonde" << std::endl;
        return layers[layer]->get(x, y);
    }



}