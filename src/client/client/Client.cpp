/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Client.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;


namespace client {

    Client::Client(state::State& state) : engine(state), state(state) {
        cout << "Création d'un client" << endl;
    }

    void Client::run(sf::RenderWindow& window) {
        cout << "Run Client !" << endl;
        
        while(1){
            sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){

                if(state.getIdPlayer() == 1){
                    cout << "Okay" << endl;
                    state.setIdPlayer(2);
                }
                else if(state.getIdPlayer() == 2){
                    state.setIdPlayer(1);
                }             
                    
            }
        }
        }
         
    }
    
    
}