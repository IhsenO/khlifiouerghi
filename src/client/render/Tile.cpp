/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Tile.h"

namespace render{

    Tile::Tile(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {

    }

    Tile::Tile() {

    }

    int Tile::getX() const {
        return this->x;
    }

    int Tile::getY() const {
        return this->y;
    }

    
}