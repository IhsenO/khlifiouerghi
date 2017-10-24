#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include "state/Tests.h"
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[]) 
{
    
    Monde *m = new Monde(1);
    
    // j'essaye de récupérer le type du Landscape :
   // la ligne dessous ne marche pas
    //m->get(0,0,0)->getType();
    
    //std::cout << dynamic_cast<Landscape*>(m->get(0,99,0)->getType()) << std::endl;

    //std::cout << dynamic_cast<City*>(m->get(1,1,0)->getDefense()) << std::endl;
    //m.loadTilesetToElement();
    
    //cout << m.tilesetToElement.size() << endl;
    
/*
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
        
    TileMap map;
    std::vector<int> level = map.loadLayer();

    std::cout << level.size() << std::endl;
   
    
    if (!map.load("../res/tileset.png", level))
        return -1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(map);
        window.display();
    }
    
    cout << "Bonjour de la part de Mohamed et Ihsen !" << endl;
*/   
    return 0;
}
