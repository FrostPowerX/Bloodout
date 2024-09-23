#include "Player.h"

Player CreatePlayer(Pallette p, float health, int score, int id)
{
	Player newPlayer;

	newPlayer.pallette = p;
	newPlayer.score = score;
	newPlayer.id = id;

	newPlayer.health = CreateHealth(health);

	return newPlayer;
}

void AddScore(Player& p, int score)
{
	p.score += score;
}

int GetId(Player& p)
{
	return p.id;
}
