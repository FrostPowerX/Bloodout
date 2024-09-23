#include "SceneGamePlay.h"

#include "..\GameLoop.h"

#include "..\utilities\Constants.h"
#include "..\utilities\Utils.h"
#include "..\utilities\Input.h"

#include "..\entities\Pallette.h"
#include "..\entities\Ball.h"
#include "..\entities\PowerUp.h"
#include "..\entities\Player.h"

#include "..\ui\Button.h"
#include "..\ui\Panel.h"
#include "..\ui\Text.h"

namespace game
{
	namespace gameplay
	{
		enum class MENU_PAUSE
		{
			CONTINUE,
			MAIN_MENU,
			EXIT
		};

		Button buttons[ButtonsInGamePlay];
		Text infoText[TextsInGamePlay];

		Button buttonEndGame;

		Rectangle mapLimits;

		Ball balls[MaxBalls];
		Player player;

		float palleteWidth;
		float palleteHeight;
		float palleteSpeed;

		float ballRadius;
		float ballSpeed;

		float timeAccum;
		float timeUpDiff;

		bool endGameMenu;
		bool pauseGame;

		bool firstScreen;

		void Init()
		{
			pauseGame = false;
			endGameMenu = false;

			timeUpDiff = 10.f;

			timeAccum = 0;

			firstScreen = true;

			palleteWidth = 30.f;
			palleteHeight = 5.f;
			palleteSpeed = 300.f;

			ballRadius = 15.f;
			ballSpeed = 320.f;

			InitMap();

			InitUI();

			InitPlayers();

			InitBalls();

			InitPowerUps();
		}

		void Input()
		{

			if (GetKeyDown(SL_KEY_ESCAPE))
				pauseGame = !pauseGame;

			if (pauseGame || endGameMenu)
				return;

			PlayersInputs();
		}

		void Update()
		{
			if (pauseGame || endGameMenu)
			{
				if (endGameMenu)
				{
					if (MouseOnTopButton(buttonEndGame))
						if (IsButtonPressed(buttonEndGame))
						{
							gameLoop::currentScene = gameLoop::SCENE::MENU;
							RestartGame();
						}
				}
				else
				{
					for (int i = 0; i < ButtonsInGamePlay; i++)
					{
						if (MouseOnTopButton(buttons[i]))
							if (IsButtonPressed(buttons[i]))
							{
								switch (MENU_PAUSE(i))
								{
								case MENU_PAUSE::CONTINUE:
									pauseGame = !pauseGame;
									break;

								case MENU_PAUSE::MAIN_MENU:
									gameLoop::currentScene = gameLoop::SCENE::MENU;
									RestartGame();
									break;

								case MENU_PAUSE::EXIT:
									gameLoop::programLoop = false;
									break;

								default:
									break;
								}
							}
					}
				}
				return;
			}

			if (timeAccum >= timeUpDiff)
			{
				timeAccum -= timeUpDiff;
			}
			else
				timeAccum += slGetDeltaTime();

			MoveObjects();

			CheckAllCollisions();

			CheckVictoryCondition();
		}

		void Draw()
		{
			DrawPlayers();
			DrawBalls();
			DrawPowerUps();

			DrawUI();
		}



		void InitMap()
		{
			mapLimits.x = screenWidth / 2;
			mapLimits.y = screenHeight / 2;
			mapLimits.width = screenWidth;
			mapLimits.height = screenHeight;
		}

		void InitUI()
		{
			float buttonWidth = 150;
			float buttonHeight = 50;

			Vector2 buttonPos;

			buttonPos.x = (screenWidth / 2);
			buttonPos.y = screenHeight - buttonHeight - 25;

			std::string namesButtons[ButtonsInMenu];

			namesButtons[0] = "Continue";
			namesButtons[1] = "Menu";
			namesButtons[2] = "Exit";

			for (int i = 0; i < ButtonsInGamePlay; i++)
			{
				buttonPos.y -= (i * buttonHeight) + 25;

				buttons[i] = CreateButton(buttonPos, buttonWidth, buttonHeight, namesButtons[i], 25, GREEN, RED, BLUE, YELLOW);
			}

			buttonEndGame = CreateButton(buttonPos, buttonWidth, buttonHeight, "Menu", 25, GREEN, RED, BLUE, YELLOW);

			// infoTexts


		}

		void InitPlayers()
		{
			Pallette pallette = CreatePallette(Vector2{ screenWidth / 2, OffSetSpawn }, RED, palleteWidth, palleteHeight, palleteSpeed);

			//CreatePlayer(pallette, 0, 1);
		}

		void InitBalls()
		{
			for (int i = 0; i < MaxBalls; i++)
			{
				balls[i] = CreateBall(GRAY, player.pallette.rect.x, player.pallette.rect.y + ballRadius, ballRadius, ballSpeed);
			}
		}

		void InitPowerUps()
		{

		}



		void PlayersInputs()
		{
			if (GetKeyPress('A'))
				MovePallette(player.pallette, -1, 0);

			if (GetKeyPress('D'))
				MovePallette(player.pallette, 1, 0);
		}

		void MoveObjects()
		{
			for (int i = 0; i < MaxBalls; i++)
			{
				if (!balls[i].isActive)
					continue;

				MoveBall(balls[i]);
			}
		}

		void CheckAllCollisions()
		{
			for (int i = 0; i < MaxBalls; i++)
			{
				if (!balls[i].isActive)
					continue;

				if (CheckCollision(balls[i].cir, player.pallette.rect))
					switch (SolveCollision(balls[i].cir, player.pallette.rect))
					{
					case TYPE_PENETRATION::HORIZONTAL:
						balls[i].dirX *= -1;
						break;

					case TYPE_PENETRATION::VERTICAL:
						balls[i].dirY *= -1;
						break;
					}

				if (CheckBorderCollision(balls[i].cir, mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y))
					SolveCollisionMap(balls[i], mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y);
			}
		}

		void CheckVictoryCondition()
		{
			int ballsActive = 0;

			for (int i = 0; i < MaxBalls; i++)
			{
				if (balls[i].isActive)
					ballsActive++;
			}

			if (ballsActive <= 0)
				endGameMenu = true;
		}

		void PeriodicEvent()
		{

		}

		void DrawUI()
		{
			if (pauseGame || endGameMenu)
			{
				if (endGameMenu)
				{
					DrawButton(buttonEndGame);
				}
				else
				{
					for (int i = 0; i < ButtonsInGamePlay; i++)
					{
						DrawButton(buttons[i]);
					}
				}
			}
		}

		void DrawPlayers()
		{
			DrawPallette(player.pallette);
		}

		void DrawBalls()
		{
			for (int i = 0; i < MaxBalls; i++)
			{
				if (balls[i].isActive)
					DrawBall(balls[i]);
			}
		}

		void DrawPowerUps()
		{

		}



		void RestartRound()
		{
			InitBalls();

			timeAccum = 0;
		}

		void RestartGame()
		{
			Init();
			firstScreen = true;
		}

		void AddBalls(int cant)
		{
			int count = cant;

			for (int i = 0; i < MaxBalls; i++)
			{
				if (!balls[i].isActive && count > 0)
				{
					balls[i].isActive = true;
					count--;
				}
			}
		}

		void RemoveBalls(int cant)
		{
			int count = cant;

			for (int i = 0; i < MaxBalls; i++)
			{
				if (balls[i].isActive && count > 0)
				{
					balls[i].isActive = false;
					count--;
				}
			}
		}

		void AddPower()
		{
			bool done = true;

			int chances = 20;

			while (done && chances > 0)
			{
				int indexToActive = GetRandomValue(0, maxPowerUps - 1);

				/*if (!powerUps[indexToActive].isActive)
				{
					powerUps[indexToActive].isActive = true;
					done = false;
				}*/

				chances--;
			}
		}
	}
}