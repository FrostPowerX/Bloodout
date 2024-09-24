#pragma once

#ifndef CONSTANTS
#define CONSTANTS

#include <iostream>

const std::string resourcesDir = "res/";
const std::string fontDir = resourcesDir + "fonts/";

const std::string GameName = "BloodOut";

const int screenWidth = 800;
const int screenHeight = 900;

const int MaxPlayers = 1;
const int MaxBalls = 5000;
const int MaxBricks = 5000;
const int maxPowerUps = 42;

const int PalletteWidth = 20;
const int PalletteHeight = 120;
const int PalletSpeed = 250;

const int PalletsOffset = 10;

const int ButtonsInMenu = 4;
const int ButtonsInGamePlay = 3;

const int TextsInGamePlay = 6;

const float maxBounceAngle = 60.f;

const int OffSetSpawnPlayer = 50;
const int OffSetSpawnBrick = 5;

#endif // !CONSTANTS
