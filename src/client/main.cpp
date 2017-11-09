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
#include "engine.h"



using namespace std;
using namespace state;
using namespace render;
using namespace engine;

int main(int argc,char* argv[]) 
{

    sf::RenderWindow window(sf::VideoMode(800, 480), "Rendu");
        
    Monde *m = new Monde(3);

    State state(*m);
    state.addPlayer(new Player("Joueur 1"));
    state.addPlayer(new Player("Joueur 2"));
    
    cout << state.getPlayer(1)->getFood() << endl;
    //Monde m = state.getMonde();
    
    m->set(2,2,2,new Army());
    state.getMonde().set(2,3,2,new Army()); 
    
    Engine e(state);
    
    MoveCharCommand move(2,3,10,10);
    e.runCommand(&move);
    
    m->set(8,2,2,new Army());

    
    MapLayer map1(*m->getLayer(0));
    MapLayer map2(*m->getLayer(1));
    CharactersLayer chars(*m->getLayer(2));
     
    
    map1.initDrawer();
    map2.initDrawer();
    chars.initDrawer();
    
    //sf::View view = window.getDefaultView();
    //view.zoom(0.5f);   

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
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
