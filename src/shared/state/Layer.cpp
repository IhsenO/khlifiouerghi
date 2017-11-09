/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Layer.h"
#include "utils.hpp"
#include "Element.h"
#include "Landscape.h"
#include "City.h"
#include <iostream>

namespace state{

    Layer::Layer(int width, int height) : tab(width*height), width(width), height(height){
    }

    Layer::Layer() {
    }
    
    Element* Layer::get(int x, int y) const {
        return tab[y*width + x];
    }
    void Layer::set(int x, int y, Element* e) {
        tab[y*width + x] = e;
    }

    Layer::~Layer() {
        for(auto l : tab)
            delete l;
    }

    void Layer::loadLayer(const std::string fileName) {
        std::vector<int> vcarteInit = loadCSV(fileName);
        std::vector<int> tileToElem = loadCSV("res/TileToElement.csv");
        
        for(int i = 0; i<height; i++)
            for(int j = 0; j<width; j++){

                if(vcarteInit[i*width + j]<0){
                    this->set(j,i,NULL);
                }
                else if(tileToElem[vcarteInit[i*width + j]] == 0){
                    this->set(j,i,(new Landscape(vcarteInit[i*width + j], false)));
                }
                else if(tileToElem[vcarteInit[i*width + j]] == 1){
                    this->set(j,i,(new Landscape(vcarteInit[i*width + j], true)));

                }
                else if(tileToElem[vcarteInit[i*width + j]] == 2){
                    this->set(j,i,(new City(0,true)));
                }
                else if(tileToElem[vcarteInit[i*width + j]] == 3)
                    this->set(j,i,(new City(1,false)));
                else if(tileToElem[vcarteInit[i*width + j]] == 4)
                    this->set(j,i,(new City(2,false))); 
                else if(tileToElem[vcarteInit[i*width + j]] == 5)
                    this->set(j,i,(new City(3,false)));
                else if(tileToElem[vcarteInit[i*width + j]] == -1){
                    this->set(j,i,NULL);
                }
                else
                    std::cout << "Error tile inutilisée" << std::endl;
               
              
                 
        }
    }    
        
    
    void Layer::add(Element* e){
            tab.push_back(e);
    }

    int Layer::getHeight() const {
        return this->height;
    }

    int Layer::getWidth() const {
        return this->width;
    }
        
    }

    
