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
        //std::cout << "Layer " << tab.size() << std::endl;
    }

    Layer::Layer() {
        //this->tab = new std::vector<Element*>;
    }

 
    Element* Layer::get(int x, int y) const {
        return tab[y*width + x];
    }
    void Layer::set(int x, int y, Element* e) {
        tab[y*width + x] = e;
    }

    Layer::~Layer() {
        std::cout << "destroy Layer" << std::endl;
        for(auto l : tab)
            delete l;
    }

    void Layer::loadLayer(const std::string fileName) {
        std::vector<int> vcarteInit = loadCSV(fileName);
        //std::cout << vcarteInit.size() << std::endl;
        /*
        static std::unique_ptr<std::vector<int>> tab;
        
        if (!tab )
        */
        std::vector<int> tileToElem = loadCSV("../res/TileToElement.csv");
        
        for(unsigned int i = 0; i<vcarteInit.size(); i++){
        
            //std::cout << tileToElem[vcarteInit[i]] << std::endl;
        
            if(tileToElem[vcarteInit[i]] == 0){
                this->add(new Landscape(vcarteInit[i], false));
                //std::cout << "ok" << std::endl; 
            }
            else if(tileToElem[vcarteInit[i]] == 1)
                this->add(new Landscape(vcarteInit[i], true));
            else if(tileToElem[vcarteInit[i]] == 2)
                this->add(new City(0,true));
            else if(tileToElem[vcarteInit[i]] == 3)
                this->add(new City(1,true));
            else if(tileToElem[vcarteInit[i]] == 4)
                this->add(new City(2,true)); 
            else if(tileToElem[vcarteInit[i]] == 5)
                this->add(new City(3,true));
            else
                std::cout << "Error tile inutilisée" << std::endl;
               
        }
    }
    
        void Layer::add(Element* e){
            tab.push_back(e);
        }
        
    }

    
