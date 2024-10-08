#ifndef PLAYER
#define PLAYER

#include "Pallette.h"
#include "HealthSystem.h"

struct Player
{
	Pallette pallette;

	HealthSystem health;

	int score = 0;
	int id = 0;
};

Player CreatePlayer(Pallette pallette, float health, int score, int id);

void AddScore(Player& player, int score);

int GetId(Player& player);

#endif // !PLAYER
