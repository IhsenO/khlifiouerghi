/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UtilsEngine.hpp
 * Author: ihsen
 *
 * Created on 13 novembre 2017, 22:15
 */

#ifndef UTILSENGINE_HPP
#define UTILSENGINE_HPP

#include "state.h"
#include "engine.h"
#include <cmath>
#include <time.h>
#include <iostream>
#include <random>
using namespace std;
using namespace state;
using namespace engine;

bool inMap(State&, int, int);
bool canAccess(State&, int, int);
bool hasWonBattle(float, float);
bool canReachSimple(int,int,int,int,int);
bool canMoveSimple(State&,int,int,int,int,int);



#endif /* UTILSENGINE_HPP */

