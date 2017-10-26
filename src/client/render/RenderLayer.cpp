/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "RenderLayer.h"

namespace render{

    //RenderLayer::RenderLayer() {

    //}

    RenderLayer::~RenderLayer() {
        delete this->drawer;
    }

    Drawer* RenderLayer::getDrawer() const {
        return this->drawer;
    }
    
    
    
}