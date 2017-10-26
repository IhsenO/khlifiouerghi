/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Drawer.h"
#include "Tile.h"

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
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

    void Drawer::initVertex() {
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(100 * 100 * 4);
    }

    void Drawer::setVertexLocation(int i, int x, int y) {
        
        sf::Vertex* quad = &m_vertices[i];
                
        quad[0].position = sf::Vector2f(x * 16, y * 16);
        quad[1].position = sf::Vector2f((x + 1) * 16, y * 16);
        quad[2].position = sf::Vector2f((x + 1) * 16, (y + 1) * 16);
        quad[3].position = sf::Vector2f(x * 16, (y + 1) * 16);
                                               
        
    }

    void Drawer::setVertexTexture(int i, const Tile& tex) {
        
        sf::Vertex* quad = &m_vertices[i];
        
        quad[0].texCoords = sf::Vector2f(tex.getX(), tex.getY());
        quad[1].texCoords = sf::Vector2f(tex.getX() + tex.getWidth(), tex.getY());
        quad[2].texCoords = sf::Vector2f(tex.getX() + tex.getWidth(), tex.getY() + tex.getHeight());
        quad[3].texCoords = sf::Vector2f(tex.getX(), tex.getY() + tex.getHeight());


    }



    
}