#pragma once

#ifndef CONSTANTS
#define CONSTANTS

#include <iostream>

#include "sl.h"
#include "Color.h"

const std::string GameName = "WuPong";

const int screenWidth = 800;
const int screenHeight = 600;

const int MaxPlayers = 2;
const int MaxBalls = 500;

const int PalletteWidth = 20;
const int PalletteHeight = 120;
const int PalletSpeed = 250;

const int PalletsOffset = 10;

const int ButtonsInMenu = 5;
const int ButtonsInGamePlay = 3;

const int TextsInGamePlay = 6;

const int maxPowerUps = 6;

const int OffSetSpawn = 50;

const Color GreenWu = Color{ 89,215,57,255 };
const Color DarkBrownWu = Color{ 48,10,10,255 };
const Color OpaYellowWu = Color{ 194,156,72,255 };
const Color RedWu = Color{ 170,28,28,255 };
const Color DarkRedWu = Color{ 123,12,0,255 };
const Color BlackTransparent = Color{ 0,0,0,200 };
const Color GrayTransparent = Color{ 130,130,130,200 };

#endif // !CONSTANTS
