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

		const int infoTextsCount = 12;

		Button buttons[ButtonsInGamePlay];
		Text infoText[TextsInGamePlay];
		std::string texts[infoTextsCount];

		Button buttonEndGame;

		Rectangle mapLimits;
		Rectangle barrier;

		Ball balls[MaxBalls];
		Brick bricks[MaxBricks];
		PowerUp powerUps[maxPowerUps];

		Text infoTexts[infoTextsCount];
		Text endGameTxt;
		Text scoreEndGameTxt;

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

		int sizeP;
		int powerUpsUsed;
		int activeBalls;
		int round;

		bool activeBarrier;

		bool endGameMenu;
		bool pauseGame;

		bool firstScreen;

		void InitMap();
		void InitBarrier();
		void InitUI();
		void InitTexts();
		void InitPlayers();
		void InitBalls();
		void InitBricks();
		void InitPowerUps();

		void PlayersInputs();

		void UpdateUI();
		void MoveObjects();
		void CheckAllCollisions();
		void UpdateInfoTexts();
		void LoseCondition();
		void RoundPassCondition();

		void DrawUI();
		void DrawTexts();
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

			ballRadius = 8.f;
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

			sizeP = player.pallette.rect.width;
			powerUpsUsed = 0;
			activeBalls = 1;
			round = 1;
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
			UpdateUI();

			if (pauseGame || endGameMenu)
				return;

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

			UpdateInfoTexts();

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

			DrawTexts();
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

				buttons[i] = CreateButton(buttonPos, buttonWidth, buttonHeight, namesButtons[i], 25, RED, GRAY, BLUE, CYAN);
			}

			buttonEndGame = CreateButton(buttonPos, buttonWidth, buttonHeight, "Menu", 25, RED, GRAY, BLUE, CYAN);

			// infoTexts

			InitTexts();
		}

		void InitTexts()
		{
			int offSetTxt = 10;
			int fontSize = 16;

			Vector2 position;
			position.x = offSetTxt;
			position.y = screenHeight;

			texts[0] = "Lives: ";
			texts[1] = "Score: ";
			texts[2] = "Level: ";
			texts[3] = "Used PowerUps: ";
			texts[4] = "Active balls: ";
			texts[5] = "Movement: Left \"A\", Right \"D\"";
			texts[6] = "Shoot: \"W\"";
			texts[7] = "Menu / Pause: \"ESC\"";
			texts[8] = "PowerUp Speed: \"COLOR\"";
			texts[9] = "PowerUp Barrier: \"COLOR\"";
			texts[10] = "PowerUp Size: \"COLOR\"";
			texts[11] = "PowerUp Balls: \"COLOR\"";

			for (int i = 0; i < infoTextsCount; i++)
			{
				position.y -= slGetTextHeight(texts[i].c_str()) + offSetTxt;
				if (i == infoTextsCount - 4)
					position.y -= offSetTxt * 2;

				if (i == 3)
					position.y -= offSetTxt * 2;

				infoTexts[i] = CreateText(texts[i], position.x, position.y, fontSize, GRAY);
			}

			infoTexts[0].color = RED;
			infoTexts[1].color = GREEN;
			infoTexts[2].color = GREEN;


			infoTexts[8].color = CYAN;
			infoTexts[9].color = GREEN;
			infoTexts[10].color = GRAY;
			infoTexts[11].color = YELLOW;

			fontSize = 20;
			position.x = screenWidth / 2;

			slSetFontSize(fontSize * 6);
			std::string txtEndgame = "You Lose";
			position.x -= slGetTextWidth(txtEndgame.c_str()) / 2;
			position.y = screenHeight - slGetTextHeight(txtEndgame.c_str()) - fontSize;
			endGameTxt = CreateText(txtEndgame, position.x, position.y, fontSize * 6, BOARD);

			slSetFontSize(fontSize);
			std::string scoreEndGame = "Max Score: ";
			position.x = (screenWidth / 2) - slGetTextWidth(scoreEndGame.c_str()) * 2;
			position.y -= slGetTextHeight(scoreEndGame.c_str()) + fontSize;
			scoreEndGameTxt = CreateText(scoreEndGame, position.x, position.y, fontSize, GREEN);
		}

		void InitPlayers()
		{
			float totalWidth = abs(mapLimits.x - mapLimits.width);

			float halfMapW = mapLimits.x + totalWidth / 2;
			float halfMapH = mapLimits.y + OffSetSpawnPlayer;

			Pallette pallette = CreatePallette(Vector2{ halfMapW, halfMapH }, RED, palleteWidth, palleteHeight, palleteSpeed);

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

			float health = maxBrickHealth;

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
			int powersPerType = 10;

			for (int i = 0; i < maxPowerUps; i++)
			{
				if (count < powersPerType)
					powerUps[i] = CreatePowerUp(rect, GRAY, 10, 0, 0, 0);
				else if (count < powersPerType * 2)
					powerUps[i] = CreatePowerUp(rect, CYAN, 0, 25, 0, 0);
				else if (count < powersPerType * 3)
					powerUps[i] = CreatePowerUp(rect, YELLOW, 0, 0, 0, 2);
				else if (count < powersPerType * 4)
					powerUps[i] = CreatePowerUp(rect, GREEN, 0, 0, 10.f, 0);

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

#ifndef NDEBUG

			if (GetKeyDown('R'))
				activeBarrier = !activeBarrier;

			if (GetKeyDown('E'))
				Heal(player.health, 3.f);

			if (GetKeyPress('Q'))
				AddBalls(5, balls[0].cir.x, balls[0].cir.y);

			if (GetKeyPress('T'))
				RestartRound();

#endif
		}

		void UpdateUI()
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

			// Collisions PowerUp
			for (int i = 0; i < maxPowerUps; i++)
			{
				if (!powerUps[i].isActive)
					continue;

				// With player
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

					player.pallette.rect.width += (player.pallette.rect.width + powerUps[i].addWidth < palleteWidth * 3) ? powerUps[i].addWidth : 0;
					player.pallette.speed += (player.pallette.speed + powerUps[i].addSpeed < PalletSpeed * 3) ? powerUps[i].addSpeed : 0;

					if (powerUps[i].secondsInvulerable > 0)
					{
						timeActiveBarrier = powerUps[i].secondsInvulerable;
						timeAccum = 0;
						activeBarrier = true;
					}

					powerUpsUsed++;

					powerUps[i].isActive = false;
				}

				// With map
				if (CheckBorderCollision(powerUps[i].rect, mapLimits.width, mapLimits.x, mapLimits.height, mapLimits.y))
					powerUps[i].isActive = false;
			}
		}

		void UpdateInfoTexts()
		{
			infoTexts[0].text = texts[0] + to_string((int)player.health.currentHealth);
			infoTexts[1].text = texts[1] + to_string(player.score);
			infoTexts[2].text = texts[2] + to_string(round);
			infoTexts[3].text = texts[3] + to_string(powerUpsUsed);
			infoTexts[4].text = texts[4] + to_string(activeBalls);
		}

		void LoseCondition()
		{
			int ballsActive = 0;

			for (int i = 0; i < MaxBalls; i++)
			{
				if (balls[i].isActive)
					ballsActive++;
			}

			activeBalls = ballsActive;

			if (ballsActive <= 0)
			{
				TakeDamage(player.health, 1.f);
				InitBalls();
			}

			if (!IsAlive(player.health) && !endGameMenu)
			{
				scoreEndGameTxt.text += to_string(player.score);
				endGameMenu = true;
			}
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
					SetForeColor(BLACK_TRANSPARENT);
					slRectangleFill(screenWidth / 2, screenHeight / 2, screenWidth, screenHeight);

					DrawText(endGameTxt);

					slSetFont(1, 15);
					DrawText(scoreEndGameTxt);
					slSetFont(0, 15);

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

		void DrawTexts()
		{
			slSetFont(1, infoTexts[0].fontSize);

			for (int i = 0; i < infoTextsCount; i++)
			{
				DrawText(infoTexts[i]);
			}

			slSetFont(0, infoTexts[0].fontSize);
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

			maxBrickHealth += 1.f;

			if (round % 3 == 0 && round < 42)
			{
				maxBrickLines++;
				maxBrickHealth = 1.f;
			}

			float totalWidth = abs(mapLimits.x - mapLimits.width);

			player.pallette.rect.x = mapLimits.x + totalWidth / 2;
			player.pallette.rect.y = mapLimits.y + OffSetSpawnPlayer;

			player.pallette.rect.width = palleteWidth;
			player.pallette.speed = palleteSpeed;

			InitBricks();

			activeBarrier = false;

			timeAccum = 0;
			round++;
		}

		void RestartGame()
		{
			Init();
			for (int i = 0; i < MaxBricks; i++)
			{
				bricks[i].isActive = false;
			}

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