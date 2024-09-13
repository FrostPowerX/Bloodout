#ifndef PLAYER
#define PLAYER

#include "Pallette.h"

struct Player
{
	Pallette pallette;

	int score = 0;
	int id = 0;
};

Player CreatePlayer(Pallette, int score, int id);

void AddScore(Player&, int score);

int GetId(Player&);

#endif // !PLAYER
