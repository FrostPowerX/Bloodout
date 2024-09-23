#ifndef GAME_PLAY_SCENE
#define GAME_PLAY_SCENE


namespace game
{
	namespace gameplay
	{
		void Init();

		void Input();
		void Update();
		void Draw();

		void InitMap();
		void InitUI();
		void InitPlayers();
		void InitBalls();
		void InitPowerUps();

		void PlayersInputs();

		void MoveObjects();
		void CheckAllCollisions();
		void CheckVictoryCondition();
		void PeriodicEvent();

		void DrawUI();
		void DrawPlayers();
		void DrawBalls();
		void DrawPowerUps();

		void RestartRound();
		void RestartGame();
		
		void AddBalls(int cant);
		void RemoveBalls(int cant);
		void AddPower();
	}
}

#endif // !GAME_PLAY_SCENE
