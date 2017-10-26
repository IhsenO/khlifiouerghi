/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CharactersSet.h"
#include "state/Element.h"
#include <iostream>

namespace render {

    CharactersSet::CharactersSet() {
        this->characters.push_back(Tile(0*16,2*16,16,16));
        this->characters.push_back(Tile(2*16,2*16,16,16));
        this->characters.push_back(Tile(8*16,1*16,16,16));
        
    }

    const std::string CharactersSet::getFile() const {
        return "res/sprite.png";
    }

    int CharactersSet::getHeight() const {
        return 13;
    }

    int CharactersSet::getWidth() const {
        return 21;
    }

    const Tile& CharactersSet::getTile(const state::Element& e) const {
        if(&e == NULL)
            return this->characters[2];
        else if(e.getTypeID() == state::ARMY || e.getTypeID() == state::SETTLERS){
            return this->characters[0];
            std::cout << "OK" << std::endl;
        }
        else
            return this->characters[2];
    }

    const std::vector<Tile>& CharactersSet::getCharacters() const {
        return this->characters;
    }

    void CharactersSet::setCharacters(const std::vector<Tile>& characters) {
        this->characters = characters;
    }
    
    
}
