// This code is created by Henri Laitinen
// laitinenhenri@hotmail.com

#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <vector>
#include "windows.h"
#include <string>

using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////IN THIS FILE I JUST INITIALIZE FLAGS ETC BORING FILLLER STUFF////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Flags of mouse clicking
bool middleHit = false;
bool rightHit = false;
bool leftHit = false;
bool mousePressed = false;


//Initializing the numbers needed in moving functions
int movingX;
int movingY;
//limits where windows can move
int windowXLimitMin = 80;
int windowXLimitMax = 400;
int windowYLimitMin = 80;
int windowYLimitMax = 190;

string message;
int lastNum = 0;

