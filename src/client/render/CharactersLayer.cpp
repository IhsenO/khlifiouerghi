/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CharactersLayer.h"
#include "CharactersSet.h"
#include <iostream>

namespace render{

    CharactersLayer::CharactersLayer(const state::Layer& tab) : tab(tab) {
        
        this->tileSet = new CharactersSet();
        this->drawer = new Drawer();
        this->drawer->loadTexture(this->tileSet->getFile());
        drawer->initVertex(tab.getWidth(), tab.getHeight());
        
        
    }

    void CharactersLayer::initDrawer() {
        
        
        
        for(int i = 0; i < tab.getHeight(); i++)
            for(int j = 0; j < tab.getWidth(); j++){
                this->drawer->setVertexLocation(((j + i*tab.getWidth()) * 4), j ,i);
                this->drawer->setVertexTexture(((j + i*tab.getWidth()) * 4), this->tileSet->getTile(*tab.get(j,i)));
            }
        
    }

    const state::Layer& CharactersLayer::getTab() const {
        return this->tab;
    }
    
}