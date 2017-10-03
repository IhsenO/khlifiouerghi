/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Monde.h"

namespace state{
    Monde::Monde(int width, int height, int depth) : width(width), height(height), nbLayers(depth) {
        layers = new Layer[depth];
        //for(int i = 0; i < nbLayers; i++){
        //    layers[i] = std::unique_ptr<Layer>(new Layer(width, height));
        //}
    }
    
    Monde::~Monde() {
        delete[] layers;
    }


}