#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

#include "state/Tests.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    
    testsUnitaires();
    /*
    Monde monde(10,10,3);
       
    for(int i = 0; i< monde.getWidth() ; i++)
        for(int j = 0; j < monde.getHeight(); j++){
            monde.set(i,j,0,new Landscape());
    }
    
    monde.set(0,3,0,new Army());
    
    for(int i = 0; i< monde.getWidth() ; i++)
        for(int j = 0; j < monde.getHeight(); j++){
            if(monde.get(i,j,0)==NULL)  cout << "Oups il y a rien" << endl;

    }
    
    cout << monde.get(0,3,0)->getTypeID() << endl;
    
    cout << "Bonjour de la part de Mohamed et Ihsen !" << endl;
    */
    return 0;
}
