/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CharactersLayer.h"
#include "CharactersSet.h"

namespace render{

    CharactersLayer::CharactersLayer(const state::Layer& tab) : tab(tab) {
        this->tileSet = new CharactersSet();
        this->drawer = new Drawer();
        this->drawer->loadTexture(this->tileSet->getFile());
        drawer->initVertex();
        
    }

    void CharactersLayer::initDrawer() {
        for(unsigned int i = 0; i < 100; i++)
            for(unsigned int j = 0; j < 100; j++){
                this->drawer->setVertexLocation(((i + j*100) * 4), i ,j);
                this->drawer->setVertexTexture(((i + j*100) * 4), this->tileSet->getTile(*tab.get(i,j)));
            }
    }

    const state::Layer& CharactersLayer::getTab() const {
        return this->tab;
    }
    
}