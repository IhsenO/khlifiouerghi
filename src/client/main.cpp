#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    
    Monde monde(10,10,3);
   
    vector<Layer*> a = monde.getLayers();
        
    //for(Element* i = 0; i<a[0].size(); i++){
    //    i = new Landscape();
    //}
    
    cout << "Bonjour de la part de Mohamed et Ihsen !" << endl;

    return 0;
}
