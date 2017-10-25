/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Drawer.h"

namespace render{

    void Drawer::loadTexture(const std::string fileName) {
        try{
            m_tileset.loadFromFile(fileName);
        }
        catch(std::exception const& e){
            throw std::runtime_error("Probleme ouverture Fichier");
        }
    }

    void Drawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    }

    void Drawer::initVertex() {
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(100 * 100 * 4);
    }

    void Drawer::setVertexLocation(int x, int y) {
        
        sf::Vertex* quad = &m_vertices[(x + y * 100) * 4];
                
        quad[0].position = sf::Vector2f(x * 16, y * 16);
        quad[1].position = sf::Vector2f((x + 1) * 16, y * 16);
        quad[2].position = sf::Vector2f((x + 1) * 16, (y + 1) * 16);
        quad[3].position = sf::Vector2f(x * 16, (y + 1) * 16);
                                               
        
    }

    void Drawer::setVertexTexture(int i, const Tile& tex) {

    }



    
}