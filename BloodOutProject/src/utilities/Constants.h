#pragma once

#ifndef CONSTANTS
#define CONSTANTS

#include <iostream>

#include "sl.h"

const std::string resourcesDir = "res/";
const std::string fontDir = resourcesDir + "fonts/";

const std::string GameName = "BloodOut";

const int screenWidth = 800;
const int screenHeight = 600;

const int MaxPlayers = 2;
const int MaxBalls = 500;

const int PalletteWidth = 20;
const int PalletteHeight = 120;
const int PalletSpeed = 250;

const int PalletsOffset = 10;

const int ButtonsInMenu = 4;
const int ButtonsInGamePlay = 3;

const int TextsInGamePlay = 6;

const int maxPowerUps = 6;

const float maxBounceAngle = 60.f;

const int OffSetSpawn = 50;

#endif // !CONSTANTS
