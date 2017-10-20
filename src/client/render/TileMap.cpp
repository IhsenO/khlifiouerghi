/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TileMap.h"

namespace render {

    bool TileMap::loadLayer(const std::string layer) {

    }


    bool TileMap::load(const std::string& tileset, const int* tiles) {
        
        int width = 10;
        int height = 10;
        int sizeX = 21;
        int sizeY = 9;
        
        if (!m_tileset.loadFromFile(tileset))
            return false;
        
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);
        
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // on récupère le numéro de tuile courant
                int tileNumber = tiles[i + j * width];

                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (m_tileset.getSize().x / 16);
                int tv = tileNumber / (m_tileset.getSize().x / 16);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // on définit ses quatre coins
                quad[0].position = sf::Vector2f(i * 16, j * 16);
                quad[1].position = sf::Vector2f((i + 1) * 16, j * 16);
                quad[2].position = sf::Vector2f((i + 1) * 16, (j + 1) * 16);
                quad[3].position = sf::Vector2f(i * 16, (j + 1) * 16);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * 16, tv * 16);
                quad[1].texCoords = sf::Vector2f((tu + 1) * 16, tv * 16);
                quad[2].texCoords = sf::Vector2f((tu + 1) * 16, (tv + 1) * 16);
                quad[3].texCoords = sf::Vector2f(tu * 16, (tv + 1) * 16);
            }
        
        return true;
    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }




    
}
 