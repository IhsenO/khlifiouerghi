#include <iostream>
// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"
#include "Tests.hpp"
#include "render.h"
#include "engine.h"
#include "utils.hpp"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;

int main(int argc,char* argv[]) 
{

    sf::RenderWindow window(sf::VideoMode(336, 224), "Rendu");
    
    int i = 0;
        
    Monde *m = new Monde("MapTestEngine", 3);

    
    
    State state(*m);
    state.addPlayer(new Player("Joueur 1"));
    state.addPlayer(new Player("Joueur 2"));

    
    m->set(4,4,2,new Army());
    state.getMonde().get(4,4,2)->setIdPlayer(1);
    state.getMonde().get(2,2,1)->setIdPlayer(1);
    
    state.getMonde().get(18,11,1)->setIdPlayer(2);
    
    Engine e(state);     
    //m->set(8,2,2,new Army());

       
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
            else if(event.type == sf::Event::KeyReleased){
                testsEngine(i, e, state);
                i++;
            }
        }
        window.clear();
        
        //window.setView(view);
        
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
