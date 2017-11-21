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
    
    if (argc < 2 ){
        menu();
        return 2;
    }
    
    string mode = argv[1];
    if (mode == "hello")
        cout << "Hello world !" << endl;
    
    else if(mode == "state")
        testsUnitaires();
    
    else if(mode == "render"){
        
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
    }
    
    else if(mode == "engine"){
        
    
    sf::RenderWindow window(sf::VideoMode(336, 224), "Engine");
    
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
            else if(event.type == sf::Event::KeyReleased && i < 23){
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
    }
    
    else if(mode == "random_ai"){
        
    sf::RenderWindow window(sf::VideoMode(336, 224), "Random_IA");

    Monde *m = new Monde("MapTestEngine", 3); 
    State state(*m);
    state.addPlayer(new Player("Joueur 1"));
    state.addPlayer(new Player("Joueur 2"));

    //state.getMonde().get(2,2,1)->setIdPlayer(1);
    //state.getMonde().get(18,11,1)->setIdPlayer(2);   
    Engine e(state);
     
    state.setIdPlayer(2);
    
    MapLayer map1(*m->getLayer(0));
    MapLayer map2(*m->getLayer(1));
    
    CharactersLayer chars(*m->getLayer(2));
    
    map1.initDrawer();   
    map2.initDrawer();  
    chars.initDrawer();
    
    cout << "Bienvenue dans le mode avec une IA random !" << endl;
    cout << "Pour faire défiler les epoques, appuyez sur n'importe quelle touche." << endl;
    cout << "En restant appuyé, les epoques défilent plus vite !" << endl;
    
    RandomAI random(state, e);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){
                //testsAIRandom(e, state);
                random.run(e);
                if(state.getIdPlayer() == 1) state.setIdPlayer(2);
                else if(state.getIdPlayer() == 2) state.setIdPlayer(1);
            }
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
        
    }
    
    else if(mode == "heuristic_ai"){
        
    sf::RenderWindow window(sf::VideoMode(336, 224), "Random_IA");

    Monde *m = new Monde("MapTestEngine", 3); 
    State state(*m);
    state.addPlayer(new Player("Joueur 1"));
    state.addPlayer(new Player("Joueur 2"));

    //state.getMonde().get(2,2,1)->setIdPlayer(1);
    //state.getMonde().get(18,11,1)->setIdPlayer(2);   
    Engine e(state);
     
    state.setIdPlayer(2);
    
    MapLayer map1(*m->getLayer(0));
    MapLayer map2(*m->getLayer(1));
    
    CharactersLayer chars(*m->getLayer(2));
    
    map1.initDrawer();   
    map2.initDrawer();  
    chars.initDrawer();
    
    cout << "Bienvenue dans le mode avec une IA random !" << endl;
    cout << "Pour faire défiler les epoques, appuyez sur n'importe quelle touche." << endl;
    cout << "En restant appuyé, les epoques défilent plus vite !" << endl;
    
    HeuristicAI heuristic(state, e);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){
                //testsAIRandom(e, state);
                heuristic.run(e);
                if(state.getIdPlayer() == 1) state.setIdPlayer(2);
                else if(state.getIdPlayer() == 2) state.setIdPlayer(1);
            }
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
        
    }
 
  
    return 0;
}
