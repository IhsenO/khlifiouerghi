/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "MapSet.h"

namespace render{

    MapSet::MapSet() {
        for(int i = 0; i < this->getWidth(); i++)
            for(int j = 0; j < this->getHeight(); j++){
                map.push_back(Tile(i,j,16,16));
            }
    }
    

    const std::string MapSet::getFile() const {
        return "../res/TileSet.png";
    }

    int MapSet::getHeight() const {
        return 9;
    }

    int MapSet::getWidth() const {
        return 21;
    }

    const Tile& MapSet::getTile(const state::Element& e) const {
        
    }
    
    
    const std::vector<Tile>& MapSet::getMap() const {
        return this->map;
    }

    void MapSet::setMap(const std::vector<Tile>& map) {
        this->map = map;
    }
    
}
