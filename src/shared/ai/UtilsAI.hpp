/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UtilsAI.hpp
 * Author: ihsen
 *
 * Created on 14 novembre 2017, 18:41
 */

#ifndef UTILSAI_HPP
#define UTILSAI_HPP

#include "state.h"
#include "engine.h"
#include "ai.h"
#include "state/Construction.h"
#include <cmath>

using namespace std;
using namespace state;
using namespace engine;

bool isInMap(State&, int, int);
bool canBuildConstruction(State&, int, int, ConstructionTypeId);
bool canUpgrade(State&, int, int);
bool canMakeSoldiers(State&);
bool enemyArmy(State&, int, int);
bool friendlyArmy(State&, int, int);
bool enemyCity(State&, int, int);

bool canAccessAI(State&, int, int);
bool canAccessAIDist(State&, int, int);
bool canReachImprovedAI(int,int,int,int,int);
bool canMoveImprovedAI(State&,int,int,int,int,int);
void findBestMoveAI(State&, int&, int&, int, vector<int>);
#endif /* UTILSAI_HPP */

