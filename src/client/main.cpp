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

    sf::RenderWindow window(sf::VideoMode(800, 480), "Rendu");
        
    Monde *m = new Monde(3);
    
    m->set(2,2,2,new Army());
    
    m->set(8,2,2,new Army());

    
    MapLayer map1(*m->getLayer(0));
    MapLayer map2(*m->getLayer(1));
    CharactersLayer chars(*m->getLayer(2));
    
    map1.initDrawer();
    map2.initDrawer();
    chars.initDrawer();
    
   
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        map1.initDrawer();
        map2.initDrawer();
        chars.initDrawer();
        window.draw(*map1.getDrawer());
        window.draw(*map2.getDrawer());
        window.draw(*chars.getDrawer());
        window.display();
    }
    
    delete m;
  
    return 0;
}
