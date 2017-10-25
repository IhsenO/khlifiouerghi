/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MapLayer.h"
#include "MapSet.h"
#include <iostream>

namespace render {

    MapLayer::MapLayer(const state::Layer& tab) : tab(tab) {
        this->tileSet = new MapSet();
        this->drawer = new Drawer();
    }

    void MapLayer::initDrawer() {
        this->drawer->loadTexture(this->tileSet->getFile());
    }
    
    
}