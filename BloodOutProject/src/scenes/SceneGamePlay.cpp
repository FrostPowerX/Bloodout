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
		Rectangle barrier;

		Ball balls[MaxBalls];
		Brick bricks[MaxBricks];
		PowerUp powerUps[maxPowerUps];

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
		float timeActiveBarrier;

		bool activeBarrier;

		bool endGameMenu;
		bool pauseGame;

		bool firstScreen;

		void InitMap();
		void InitBarrier();
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
		void DrawBarrier();
		void DrawMap();

		void RestartRound();
		void RestartGame();

		void AddBalls(int cant, float posX, float posY);
		void RemoveBalls(int cant);
		void AddPower(float posX, float posY);



		void Init()
		{
			InitMap();

			pauseGame = false;
			endGameMenu = false;
			activeBarrier = false;

			timeActiveBarrier = 10.f;

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

			InitBarrier();
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

			if (timeAccum >= timeActiveBarrier)
			{
				timeAccum -= timeActiveBarrier;
				activeBarrier = false;
			}
			else if (activeBarrier)
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
			DrawBarrier();
			DrawMap();

			DrawUI();
		}



		void InitMap()
		{
			mapLimits.x = screenWidth / 2;
			mapLimits.y = 0;
			mapLimits.width = screenWidth;
			mapLimits.height = screenHeight;
		}

		void InitBarrier()
		{
			float totalWidth = abs(mapLimits.x - mapLimits.width);

			barrier.x = mapLimits.x + totalWidth / 2;
			barrier.y = mapLimits.y + (OffSetSpawnPlayer / 2);

			barrier.width = totalWidth;
			barrier.height = OffSetSpawnBrick;

			activeBarrier = false;
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
			Rectangle rect;
			rect.x = 0;
			rect.y = 0;
			rect.width = 20;
			rect.height = 20;

			int count = 0;
			int powersPerType = 5;

			for (int i = 0; i < maxPowerUps; i++)
			{
				if (count < powersPerType)
					powerUps[i] = CreatePowerUp(rect, WHITE, 10, 0, 0, 0);
				else if (count < powersPerType * 2)
					powerUps[i] = CreatePowerUp(rect, WHITE, 0, 25, 0, 0);
				else if (count < powersPerType * 3)
					powerUps[i] = CreatePowerUp(rect, WHITE, 0, 0, 0, 2);
				else if (count < powersPerType * 4)
					powerUps[i] = CreatePowerUp(rect, WHITE, 0, 0, 10.f, 0);

				powerUps[i].speed = 300;

				count++;
			}
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

			for (int i = 0; i < maxPowerUps; i++)
			{
				if (!powerUps[i].isActive)
					continue;

				MovePowerUp(powerUps[i], 0, -1);
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

						AddPower(bricks[j].rect.x, bricks[j].rect.y);
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
						if (balls[i].cir.y < screenHeight / 2)
							balls[i].isActive = false;
						break;
					}

				// Collision with Barrier
				if (activeBarrier)
					if (CheckCollision(balls[i].cir, barrier))
						switch (SolveCollision(balls[i].cir, barrier))
						{
						case TYPE_PENETRATION::VERTICAL:
							balls[i].dirY *= -1;
							break;

						case TYPE_PENETRATION::HORIZONTAL:
							balls[i].dirX *= -1;
							break;
						}
			}

			// Collisions Player with map
			if (CheckBorderCollision(player.pallette.rect, mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y))
				SolveCollisionMap(player.pallette.rect, mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y);

			// Collisions PowerUp with Player
			for (int i = 0; i < maxPowerUps; i++)
			{
				if (!powerUps[i].isActive)
					continue;

				if (CheckCollision(player.pallette.rect, powerUps[i].rect))
				{
					for (int j = 0; j < MaxBalls; j++)
					{
						if (balls[j].isActive)
						{
							AddBalls(powerUps[i].addBalls, balls[j].cir.x, balls[j].cir.y);
							break;
						}
					}

					player.pallette.rect.width += powerUps[i].addWidth;
					player.pallette.speed += powerUps[i].addSpeed;

					if (powerUps[i].secondsInvulerable > 0)
					{
						timeActiveBarrier = powerUps[i].secondsInvulerable;
						timeAccum = 0;
						activeBarrier = true;
					}

					powerUps[i].isActive = false;
				}
			}
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
			for (int i = 0; i < maxPowerUps; i++)
			{
				if (!powerUps[i].isActive)
					continue;

				DrawPowerUp(powerUps[i]);
			}
		}

		void DrawBarrier()
		{
			if (activeBarrier)
			{
				SetForeColor(GREEN);
				slRectangleFill(barrier.x, barrier.y, barrier.width, barrier.height);
			}
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
			InitPowerUps();

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

			float totalWidth = abs(mapLimits.x - mapLimits.width);

			player.pallette.rect.x = mapLimits.x + totalWidth / 2;
			player.pallette.rect.y = mapLimits.y + OffSetSpawnPlayer;

			player.pallette.rect.width = palleteWidth;
			player.pallette.speed = palleteSpeed;

			InitBricks();

			activeBarrier = false;

			timeAccum = 0;
		}

		void RestartGame()
		{
			Init();
			firstScreen = true;
		}



		void AddBalls(int cant, float posX, float posY)
		{
			int count = cant;

			for (int i = 0; i < MaxBalls; i++)
			{
				if (!balls[i].isActive && count > 0)
				{
					balls[i].isActive = true;
					balls[i].cir.x = posX;
					balls[i].cir.y = posY;

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

		void AddPower(float posX, float posY)
		{
			bool done = true;

			int chances = 20;

			while (done && chances > 0)
			{
				int indexToActive = GetRandomValue(0, maxPowerUps - 1);

				if (!powerUps[indexToActive].isActive)
				{
					powerUps[indexToActive].isActive = true;
					powerUps[indexToActive].rect.x = posX;
					powerUps[indexToActive].rect.y = posY;
					done = false;
				}

				chances--;
			}
		}
	}
}