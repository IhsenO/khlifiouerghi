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

using namespace std;
using namespace state;
using namespace engine;

bool canBuildConstruction(State&, int, int, ConstructionTypeId);
bool canUpgrade(State&, int, int);
bool canMakeSoldiers(State&);

#endif /* UTILSAI_HPP */

