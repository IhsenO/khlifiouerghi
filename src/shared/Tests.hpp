/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tests.hpp
 * Author: ihsen
 *
 * Created on 9 novembre 2017, 15:52
 */

#ifndef TESTS_HPP
#define TESTS_HPP

#include "state.h"
#include "engine.h"
#include "ai.h"
#include <iostream>
#include "engine/UtilsEngine.hpp"
using namespace std;
using namespace state;
using namespace engine;
using namespace ai;



void testsUnitaires();

void testsEngine(int i, Engine& engine, State& state); 

void testsAIRandom(Engine& engine, State& state); 

void menu();

void menuServer();


#endif /* TESTS_HPP */

