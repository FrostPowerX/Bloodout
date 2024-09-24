#include "SceneGamePlay.h"

#include "sl.h"

#include "GameLoop.h"

#include "Constants.h"
#include "Utils.h"
#include "Input.h"

#include "Pallette.h"
#include "Ball.h"
#include "Brick.h"
#include "PowerUp.h"
#include "Player.h"

#include "Button.h"
#include "Panel.h"
#include "Text.h"

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
		Brick bricks[MaxBricks];

		Player player;

		float palleteWidth;
		float palleteHeight;
		float palleteSpeed;

		float ballRadius;
		float ballSpeed;

		float brickWidth;
		float brickHeight;
		int brickStartPosX;
		int brickStartPosY;

		float maxBrickHealth;
		int maxBrickLines;

		float timeAccum;
		float timeUpDiff;

		bool endGameMenu;
		bool pauseGame;

		bool firstScreen;

		void InitMap();
		void InitUI();
		void InitPlayers();
		void InitBalls();
		void InitBricks();
		void InitPowerUps();

		void PlayersInputs();

		void MoveObjects();
		void CheckAllCollisions();
		void LoseCondition();
		void RoundPassCondition();

		void DrawUI();
		void DrawPlayers();
		void DrawBalls();
		void DrawBricks();
		void DrawPowerUps();
		void DrawMap();

		void RestartRound();
		void RestartGame();

		void AddBalls(int cant);
		void RemoveBalls(int cant);
		void AddPower();



		void Init()
		{
			InitMap();

			pauseGame = false;
			endGameMenu = false;

			timeUpDiff = 10.f;

			timeAccum = 0;

			firstScreen = true;

			palleteWidth = 60.f;
			palleteHeight = 10.f;
			palleteSpeed = 300.f;

			ballRadius = 5.f;
			ballSpeed = 500.f;

			brickWidth = 50;
			brickHeight = 25;
			brickStartPosX = mapLimits.x + (brickWidth / 2) + OffSetSpawnBrick;
			brickStartPosY = (mapLimits.height / 2) - (brickHeight / 2) - OffSetSpawnBrick;

			maxBrickLines = 1;
			maxBrickHealth = 1;

			InitUI();

			InitPlayers();
			InitBalls();
			InitBricks();
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

			for (int i = 0; i < MaxBricks; i++)
			{
				if (!bricks[i].isActive)
					continue;

				if (!IsAlive(bricks[i].health))
					bricks[i].isActive = false;
			}

			if (balls[0].freeze)
				TeleportBall(balls[0], player.pallette.rect.x, player.pallette.rect.y + balls[0].cir.radius + (palleteHeight / 2));

			MoveObjects();

			CheckAllCollisions();

			LoseCondition();
			RoundPassCondition();
		}

		void Draw()
		{
			DrawPlayers();
			DrawBalls();
			DrawBricks();
			DrawPowerUps();
			DrawMap();

			DrawUI();
		}



		void InitMap()
		{
			mapLimits.x = screenWidth / 3;
			mapLimits.y = 0;
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
			Pallette pallette = CreatePallette(Vector2{ screenWidth / 2, OffSetSpawnPlayer }, RED, palleteWidth, palleteHeight, palleteSpeed);

			player = CreatePlayer(pallette, 3.f, 0, 1);
		}

		void InitBalls()
		{
			for (int i = 0; i < MaxBalls; i++)
			{
				balls[i] = CreateBall(GRAY, player.pallette.rect.x, player.pallette.rect.y + ballRadius, ballRadius, ballSpeed);
			}

			balls[0].isActive = true;
			SetFreeze(balls[0], true);
		}

		void InitBricks()
		{
			Rectangle rect;
			rect.width = brickWidth;
			rect.height = brickHeight;
			rect.x = brickStartPosX;
			rect.y = brickStartPosY;

			float health = 1.f;

			int maxLines = 0;
			int bricksPerLine = 0;

			float totalWidth = abs(mapLimits.x - mapLimits.width);
			float totalHeight = abs(mapLimits.y - mapLimits.height) / 2;

			float useWidth = 0;
			float useHeight = 0;

			int actualBrick = 0;

			while (useWidth < totalWidth)
			{
				useWidth += brickWidth + OffSetSpawnBrick;
				bricksPerLine++;
			}

			while (useHeight < totalHeight && maxLines <= maxBrickLines)
			{
				useHeight += brickHeight + OffSetSpawnBrick;
				maxLines++;
			}

			for (int i = 0; i < maxLines - 1; i++)
			{
				int additional = actualBrick;
				health += (health < maxBrickHealth) ? 1.f : 0.f;

				for (int j = 0; j < bricksPerLine - 1; j++)
				{
					bricks[additional + j] = CreateBrick(rect, health, GREEN, BLUE, RED);

					rect.x += brickWidth + OffSetSpawnBrick;
					bricks[additional + j].isActive = true;

					actualBrick++;
				}

				rect.x = brickStartPosX;
				rect.y += brickHeight + OffSetSpawnBrick;
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

			if (GetKeyDown('W'))
				if (balls[0].freeze)
					SetFreeze(balls[0], false);
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
			// Collisions Balls
			for (int i = 0; i < MaxBalls; i++)
			{
				if (!balls[i].isActive)
					continue;

				// Collision with Bricks
				for (int j = 0; j < MaxBricks; j++)
				{
					if (!bricks[j].isActive)
						continue;

					if (CheckCollision(balls[i].cir, bricks[j].rect))
					{
						switch (SolveCollision(balls[i].cir, bricks[j].rect))
						{
						case TYPE_PENETRATION::HORIZONTAL:
							balls[i].dirX *= -1;
							break;

						case TYPE_PENETRATION::VERTICAL:
							balls[i].dirY *= -1;
							break;
						}

						TakeDamage(bricks[j].health, 1.f);
						AddScore(player, 10);
					}

				}

				// Collisions with Player
				if (CheckCollision(balls[i].cir, player.pallette.rect))
				{
					SolveCollision(balls[i].cir, player.pallette.rect);
					BouncingAngle(balls[i], player.pallette.rect);
				}

				// Collisions with map
				if (CheckBorderCollision(balls[i].cir, mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y))
					switch (SolveCollisionMap(balls[i], mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y))
					{
					case TYPE_PENETRATION::VERTICAL:
						if (balls[i].cir.y < mapLimits.height)
							balls[i].isActive = false;
						break;
					}
			}

			// Collisions Player with map
			if (CheckBorderCollision(player.pallette.rect, mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y))
				SolveCollisionMap(player.pallette.rect, mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y);
		}

		void LoseCondition()
		{
			int ballsActive = 0;

			for (int i = 0; i < MaxBalls; i++)
			{
				if (balls[i].isActive)
					ballsActive++;
			}

			if (ballsActive <= 0)
			{
				TakeDamage(player.health, 1.f);
				InitBalls();
			}

			if (!IsAlive(player.health))
				endGameMenu = true;
		}

		void RoundPassCondition()
		{
			int count = 0;

			for (int i = 0; i < MaxBricks; i++)
			{
				if (!bricks[i].isActive)
					continue;

				count++;
			}

			if (count <= 0)
				RestartRound();
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

		void DrawBricks()
		{
			for (int i = 0; i < MaxBricks; i++)
			{
				if (!bricks[i].isActive)
					continue;

				DrawBrick(bricks[i]);
			}
		}

		void DrawPowerUps()
		{

		}

		void DrawMap()
		{
			float mapWidth = abs(mapLimits.x - mapLimits.width);
			float mapHeight = abs(mapLimits.y - mapLimits.height);

			int mapCenterX = mapLimits.x + (mapWidth / 2);
			int mapCenterY = mapLimits.y + (mapHeight / 2);

			SetForeColor(WHITE);
			slRectangleOutline(mapCenterX, mapCenterY, mapWidth, mapHeight);
		}



		void RestartRound()
		{
			InitBalls();

			if ((maxBrickLines % 2) == 0)
			{
				maxBrickHealth++;
			}
			else if (maxBrickLines % 3 == 0)
			{
				maxBrickLines--;
			}
			else
				maxBrickLines++;

			InitBricks();

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