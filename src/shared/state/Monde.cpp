/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Monde.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "utils.hpp"

namespace state{
    Monde::Monde(int width, int height, int depth) : height(height), width(width), nbLayers(depth), layers(depth) {
        for(int i = 0; i < depth; i++){
            layers[i] = new Layer(width, height);
        }
        
        layers[0]->loadLayer("res/MapTestEngine0.csv");
        layers[1]->loadLayer("res/MapTestEngine1.csv");
    }

    Monde::Monde(int depth) : nbLayers(depth), layers(depth) {
        for(int i = 0; i < depth; i++){
            layers[i] = new Layer(100,100);
        }
        
        layers[0]->loadLayer("res/MapLayer0.csv");
        layers[1]->loadLayer("res/MapLayer1.csv");
    
    }

    Monde::Monde(std::string mondeFile, int depth) : nbLayers(depth), layers(depth){
        std::vector<int> dim = getDimentionsCSV("res/"+mondeFile+"0.csv");
        this->width = dim[0];
        this->height = dim[1];
        
        for(int i = 0; i < depth; i++){
            layers[i] = new Layer(width, height);
        }
        
        layers[0]->loadLayer("res/"+mondeFile+"0.csv");
        layers[1]->loadLayer("res/"+mondeFile+"1.csv");
    }
    
    
    Monde::~Monde() {
        for(auto e : layers)
            delete e;
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
        return layers[layer]->get(x, y);
    }

    Layer* Monde::getLayer(const int nb) const {
        return layers[nb];
    }


}