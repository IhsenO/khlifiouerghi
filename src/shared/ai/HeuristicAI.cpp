/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "HeuristicAI.h"
#include <iostream>
#include "UtilsAI.hpp"
#include <vector>
#include <queue>
#include "Point.h"
#include <random>

using namespace state;
using namespace engine;
using namespace std;

namespace ai{

    HeuristicAI::HeuristicAI(state::State& state, engine::Engine& engine) : AI(state, engine){
        this->map.init(state.getMonde().getWidth(), state.getMonde().getHeight());
        //this->map.setWidth(state.getMonde().getWidth());
        //this->map.setHeight(state.getMonde().getHeight());
        //for(int i = 0; i < state.getMonde().getWidth()*state.getMonde().getHeight(); i++)
        //    this->map.getMap().push_back(true);
        
    }

    void HeuristicAI::run(engine::Engine& engine) {
        //cout << "Affiché" << endl;
        this->map.update(state);
        //cout << "Affiché" << endl;
        this->map.afficher();
        map.addQueue(4,4);
        map.addQueue(10,4);
        map.dijkstra();
        map.afficherPoids();
        //queue<Point> test;
        //for(int i = 0; i < 100; i++)
        //    test.push(Point(rand() % 10, rand() % 10, rand() % 50));
        
        //cout << test.size() << endl;
        //map.sortQueue(test);
        //cout << test.size() << endl;
        //for(int i = 0; i < 100; i++){
         //   cout << test.front().getWeight() << endl;
         //   test.pop();
        //}
    }
    
    
}
