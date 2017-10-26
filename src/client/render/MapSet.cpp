/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MapSet.h"
#include "state/Element.h"
#include "state/Landscape.h"
#include "state/City.h"

#include <iostream>

namespace render{

    MapSet::MapSet() {
        for(int j = 0; j < this->getHeight(); j++){
            for(int i = 0; i < this->getWidth(); i++)
                map.push_back(Tile(i*16,j*16,16,16));
            }
    }
    

    const std::string MapSet::getFile() const {
        return "res/tileset.png";
    }

    int MapSet::getHeight() const {
        return 9;
    }

    int MapSet::getWidth() const {
        return 21;
    }

    const Tile& MapSet::getTile(const state::Element& e) const {
        if(&e == NULL){
            return this->map[188];
        }
        else if(e.getTypeID() == state::LANDSCAPE){
            state::Landscape *tmp = (state::Landscape*)&e;
            //std::cout << tmp->getType() << std::endl;
            return this->map[tmp->getType()];
            delete tmp;
        }
        else if(e.getTypeID() == state::CITY){
            state::City *tmp = (state::City*)&e;
            if(tmp->isFree() == true)
                return this->map[185];            
            else if(tmp->getDefense() == 1)
                return this->map[101];
            else if(tmp->getDefense() == 2)
                return this->map[80];
            else if(tmp->getDefense() == 3)
                return this->map[142];
            else{
                std::cout << "Probleme dans la transformation d'un état en une tile" << std::endl;
                return this->map[188];
            }
            delete tmp;
        }
        else{
            std::cout << "Probleme dans la transformation d'un état en une tile" << std::endl;
            return this->map[188];
        }
        
    }
    
    
    const std::vector<Tile>& MapSet::getMap() const {
        return this->map;
    }

    void MapSet::setMap(const std::vector<Tile>& map) {
        this->map = map;
    }
    
}
