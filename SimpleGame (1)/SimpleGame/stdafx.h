#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream>
using namespace std;
#include <tchar.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

const int MAX_OBJECTS_COUNT = 10000;
//object Type define
const int OBJECT_BULDING = 1;
const int OBJECT_CHARACTER = 2;
const int OBJECT_BULLET = 3;
const int OBJECT_ARROW = 4;
const int OBJECT_BACKGROUND = 5;
const int OBJECT_MARINE = 6;
const int OBJECT_SUBBUILDING = 7; 
const int OBJECT_EFFECT = 8;
const int OBJECT_SCOURGE = 9;
const int OBJECT_SCOURGEEFFECT = 10;
const int OBJECT_MARINEEFFECT = 11;

const int SIZEWINDOWWIDTH = 500;
const int SIZEWINDOWHEIGHT = 800;

const int ATEAM = 1;
const int BTEAM = 2;


const float RenderLevel_GOD = 0.f;
const float RenderLevel_SKY = 0.1f;
const float RenderLevel_GROUND = 0.2f;
const float RenderLevel_UNDERGROUND = 0.3f;

const float RenderLevel_BULDING = 0.1f;
const float RenderLevel_CHARACTER = 0.2f;
const float RenderLevel_BULLET = 0.3f;
const float RenderLevel_ARROW = 0.3f;
const float RenderLevel_PARTICLE = 0.3f;
const float RenderLevel_BACKGROUND = 0.9f;

const float MaxLife_CHARACTER = 100.f;
const float MaxLife_BUILDING = 500.f;
const float MaxLife_SUBBUILDING = 400.f;
const float MaxLife_BULLET = 15.f;
const float MaxLife_ARROW = 10.f;
const float MaxLife_MARINE = 40.f;
const float MaxLife_Scourege = 50.f;

const int AI_ATTACK = 10;
const int AI_WALK = 11;
const int AI_RUN = 12;
const int AI_DAMAGED_GUN = 13;