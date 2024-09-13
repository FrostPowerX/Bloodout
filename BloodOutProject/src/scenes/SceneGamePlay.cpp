#include "SceneGamePlay.h"

#include "..\PongGame.h"

#include "..\utilities\Constants.h"
#include "..\utilities\Utils.h"

#include "..\entities\Pallette.h"
#include "..\entities\Ball.h"
#include "..\entities\PowerUp.h"
#include "..\entities\Player.h"

#include "..\ui\Button.h"
#include "..\ui\Panel.h"
#include "..\ui\Text.h"

namespace pong
{
	namespace gameplay
	{
		enum class MENU_PAUSE
		{
			CONTINUE,
			MAIN_MENU,
			EXIT
		};

		Camera camera;

		Player players[MaxPlayers];
		Ball balls[MaxBalls];
		PowerUp powerUps[maxPowerUps];

		Button buttons[ButtonsInGamePlay];
		Text infoText[TextsInGamePlay];

		Player playerVictory;

		string scoreText;

		Panel scorePanel;
		Panel resultPanel;
		Panel playerOnePanel;
		Panel PlayerTwoPanel;

		Button buttonEndGame;

		Rectangle mapLimits;

		int scoreVictory;

		float timeAccum;
		float timeUpDiff;

		bool endGameMenu;
		bool pauseGame;
		bool pauseBalls;
		bool pvpMode;

		bool firstScreen;

		void Init()
		{
			scoreText = "  |  ";
			pauseGame = false;
			pauseBalls = true;
			endGameMenu = false;

			timeUpDiff = 10.f;
			scoreVictory = 3;

			camera.position = { 0,500,550 };
			camera.target = { 0,0,0 };
			camera.up = { 0,1,0 };
			camera.fovy = 65;
			camera.projection = CAMERA_PERSPECTIVE;

			timeAccum = 0;

			firstScreen = true;

			InitMap();

			InitUI();

			InitPlayers();

			InitBalls();

			InitPowerUps();
		}

		void Input()
		{

			if (IsKeyPressed(KEY_ESCAPE))
				pauseGame = !pauseGame;

			if (pauseGame || endGameMenu)
				return;

			if (pauseBalls)
				for (int key = 39; key < 336; key++)
				{
					if (IsKeyPressed(key))
					{
						pauseBalls = !pauseBalls;
						if (firstScreen)
							firstScreen = false;
					}
				}

			PlayersInputs();
		}

		void Update()
		{
			string newText = to_string(players[0].score) + scoreText + to_string(players[1].score);
			SetText(scorePanel, newText);

			if (pauseGame || endGameMenu)
			{
				if (endGameMenu)
				{
					if (MouseOnTopButton(buttonEndGame))
						if (IsButtonPressed(buttonEndGame))
						{
							currentScene = SCENE::MENU;
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
									pong::currentScene = SCENE::MENU;
									RestartGame();
									break;

								case MENU_PAUSE::EXIT:
									pong::programLoop = false;
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
				if (!pauseBalls)
					AddDifficulty();
			}
			else
				timeAccum += GetFrameTime();

			MoveObjects();

			CheckAllCollisions();

			CheckVictoryCondition();
		}

		void Draw()
		{
			BeginMode3D(camera);

			DrawCube({ 0,0,0 }, mapLimits.width, 0.1f, mapLimits.height, DarkBrownWu);
			DrawCubeWires({ 0,0,0 }, mapLimits.width, 0.1f, mapLimits.height, PURPLE);

			DrawPlayers();
			DrawBalls();
			DrawPowerUps();

			EndMode3D();

			DrawUI();
		}



		void InitMap()
		{
			mapLimits.x = 0;
			mapLimits.y = 0;
			mapLimits.width = screenWidth - mapLimits.x;
			mapLimits.height = screenHeight - mapLimits.y;
		}

		void InitUI()
		{
			string newTextSCore = to_string(players[0].score) + scoreText + to_string(players[1].score);

			scorePanel = CreatePanel(Rectangle{ screenWidth / 2,50,0,0 }, newTextSCore, 10, 10, 10, 10, 50, GrayTransparent, WHITE);

			string newTextP1 = "Player 1";
			playerOnePanel = CreatePanel(Rectangle{ 120,50,0,0 }, newTextP1, 10, 10, 10, 10, 50, GrayTransparent, DarkRedWu);

			string newTextP2 = "Player 2";
			PlayerTwoPanel = CreatePanel(Rectangle{ screenWidth - 120,50,0,0 }, newTextP2, 10, 10, 10, 10, 50, GrayTransparent, OpaYellowWu);

			string newTextResult = "Player 2 Victory!";
			resultPanel = CreatePanel(Rectangle{ screenWidth / 2,screenHeight / 2,0,0 }, newTextResult, 10, 10, 10, 10, 90, GrayTransparent, GreenWu);

			float buttonWidth = 150;
			float buttonHeight = 50;

			Vector2 buttonPos;

			buttonPos.x = (screenWidth / 2) - (buttonWidth / 2);
			buttonPos.y = screenHeight / ButtonsInMenu;

			std::string namesButtons[ButtonsInMenu];

			namesButtons[0] = "Continue";
			namesButtons[1] = "Menu";
			namesButtons[2] = "Exit";

			for (int i = 0; i < ButtonsInGamePlay; i++)
			{
				buttonPos.y += (i * buttonHeight) + 25;

				buttons[i] = CreateButton(buttonPos, buttonWidth, buttonHeight, namesButtons[i], 25, GreenWu, RedWu, DarkRedWu, OpaYellowWu);
			}

			buttonEndGame = CreateButton(buttonPos, buttonWidth, buttonHeight, "Menu", 25, GreenWu, RedWu, DarkRedWu, OpaYellowWu);

			// infoTexts

			infoText[0].color = DarkRedWu;
			infoText[0].font = 25;
			infoText[0].text = "You must score 3 goals to win";

			infoText[1].color = DarkRedWu;
			infoText[1].font = 25;
			infoText[1].text = "You have three types of upgrades";


			infoText[2].color = GRAY;
			infoText[2].font = 25;
			infoText[2].text = "Gray - Increases size";

			infoText[3].color = YELLOW;
			infoText[3].font = 25;
			infoText[3].text = "Yellow - Increases speed";

			infoText[4].color = GREEN;
			infoText[4].font = 25;
			infoText[4].text = "Green - Add a ball";

			infoText[5].color = DarkRedWu;
			infoText[5].font = 25;
			infoText[5].text = "Press any key to start";

			Vector2 pos;
			pos.x = screenWidth / 2;
			pos.y = screenHeight / TextsInGamePlay;

			for (int i = 0; i < TextsInGamePlay; i++)
			{
				infoText[i].position.x = pos.x - (MeasureText(infoText[i].text.c_str(), infoText[i].font) / 2);
				infoText[i].position.y = pos.y;
				pos.y += infoText[i].font * 2;
			}
		}

		void InitPlayers()
		{
			Vector2 pos1;
			pos1.x = mapLimits.x + PalletsOffset;
			pos1.y = mapLimits.y + (mapLimits.height / 2 - (PalletteHeight / 2));

			Vector2 pos2;
			pos2.x = mapLimits.x + (mapLimits.width - PalletteWidth - PalletsOffset);
			pos2.y = mapLimits.y + (mapLimits.height / 2 - (PalletteHeight / 2));

			Pallette p1 = CreatePallette(pos1, DarkRedWu, PalletteWidth, PalletteHeight, PalletSpeed);
			Pallette p2 = CreatePallette(pos2, OpaYellowWu, PalletteWidth, PalletteHeight, PalletSpeed);

			players[0] = CreatePlayer(p1, 0, 1);
			players[1] = CreatePlayer(p2, 0, 2);
		}

		void InitBalls()
		{
			Vector2 pos3;
			pos3.x = mapLimits.x + (mapLimits.width / 2);
			pos3.y = mapLimits.y + (mapLimits.height / 2);

			float ballSpeed = 300;
			float radius = 15;

			for (int i = 0; i < MaxBalls; i++)
			{
				balls[i] = CreateBall(GreenWu, pos3.x, pos3.y, radius, ballSpeed);
			}

			balls[0].isActive = true;
		}

		void InitPowerUps()
		{
			for (int i = 0; i < maxPowerUps; i++)
			{
				Rectangle rect;

				rect.width = 50;
				rect.height = 50;

				rect.x = GetRandomValue(mapLimits.x + (rect.width / 2) + OffSetSpawn, mapLimits.width - (rect.width / 2) - OffSetSpawn);
				rect.y = GetRandomValue(mapLimits.y, mapLimits.height - rect.height);

				if (i < 2)
					powerUps[i] = CreatePowerUp(rect, GREEN, 0, 0, 1);
				else if (i < 4)
					powerUps[i] = CreatePowerUp(rect, YELLOW, 0, 100, 0);
				else
					powerUps[i] = CreatePowerUp(rect, GRAY, 50, 0, 0);
			}
		}



		void PlayersInputs()
		{
			//Player 1 Controlls
			players[0].pallette.direction = (IsKeyDown(KEY_W)) ? -1.f : 0.f;

			players[0].pallette.direction = (IsKeyDown(KEY_S)) ? 1.f : players[0].pallette.direction;

			// Player 2 Controlls
			if (pvpMode)
			{
				players[1].pallette.direction = (IsKeyDown(KEY_UP)) ? -1.f : 0.f;

				players[1].pallette.direction = (IsKeyDown(KEY_DOWN)) ? 1.f : players[1].pallette.direction;
			}

			// Debug
#ifndef NDEBUG

			players[0].pallette.speed += (IsKeyDown(KEY_R)) ? 1.f : 0.f;
			players[0].pallette.speed -= (IsKeyDown(KEY_T)) ? 1.f : 0.f;

			if (IsKeyPressed(KEY_C))
				AddBalls(1);

			if (IsKeyPressed(KEY_V))
				RemoveBalls(1);

#endif // #ifndef NDEBUG
		}



		void MoveObjects()
		{
			if (pauseBalls)
				return;

			if (!pvpMode)
			{
				int idBall = 0;
				for (int i = 0; i < MaxBalls; i++)
				{
					if (balls[i].isActive)
					{
						float distanceX = abs(balls[i].cir.x - players[1].pallette.rect.x);
						float distanceX2 = abs(balls[idBall].cir.x - players[1].pallette.rect.x);

						if (distanceX < distanceX2)
							idBall = i;
					}
				}

				if (players[1].pallette.rect.y + (players[1].pallette.rect.height / 2) > balls[idBall].cir.y)
					players[1].pallette.direction = -1.f;
				else
					players[1].pallette.direction = 1.f;
			}

			for (int i = 0; i < MaxPlayers; i++)
			{
				MovePallette(players[i].pallette, players[i].pallette.direction);
			}

			for (int i = 0; i < MaxBalls; i++)
			{
				if (balls[i].isActive)
					MoveBall(balls[i]);
			}

		}

		void CheckAllCollisions()
		{
			string newText = scorePanel.text;

			// Balls Collisions
			for (int i = 0; i < MaxBalls; i++)
			{
				if (balls[i].isActive)
				{
					if (CheckBorderCollision(balls[i].cir, mapLimits.width + mapLimits.x, mapLimits.x, mapLimits.height + mapLimits.y, mapLimits.y))
						switch (SolveCollisionMap(balls[i], mapLimits.width + mapLimits.x, mapLimits.x, mapLimits.height + mapLimits.y, mapLimits.y))
						{
						case HORIZONTAL:

							if (balls[i].cir.x > (screenWidth / 2))
								AddScore(players[0], 1);
							else
								AddScore(players[1], 1);

							RestartRound();

							break;

						case VERTICAL:
							break;

						default:
							break;
						}

					for (int j = 0; j < MaxPlayers; j++)
						if (CheckCollision(balls[i].cir, players[j].pallette.rect))
							switch (SolveCollision(players[j].pallette.rect, balls[i].cir))
							{
							case HORIZONTAL:

								balls[i].dirX *= -1;
								BouncingAngle(balls[i], players[j].pallette.rect);
								balls[i].playerId = j;

								break;

							case VERTICAL:
								balls[i].dirY *= -1;
								break;

							default:
								break;
							}

					for (int j = 0; j < MaxBalls; j++)
					{
						if (j != i && balls[j].isActive)
							if (CheckCollision(balls[i].cir, balls[j].cir))
							{
								SolveCollision(balls[i].cir, balls[j].cir);
								BouncingBalls(balls[i], balls[j]);
							}

					}
				}
			}

			// Player Collisions
			for (int i = 0; i < MaxPlayers; i++)
			{
				if (CheckBorderCollision(players[i].pallette.rect, mapLimits.width + mapLimits.x, mapLimits.x, mapLimits.height + mapLimits.y, mapLimits.y))
					SolveCollisionMap(players[i].pallette.rect, mapLimits.width + mapLimits.x, mapLimits.x, mapLimits.height + mapLimits.y, mapLimits.y);
			}

			// PowerUps Collisions
			for (int i = 0; i < maxPowerUps; i++)
			{
				if (powerUps[i].isActive)
					for (int j = 0; j < MaxBalls; j++)
					{
						if (balls[j].isActive)
							if (CheckCollision(powerUps[i].rect, balls[j].cir))
							{
								if (balls[j].playerId != -1)
								{
									players[balls[j].playerId].pallette.speed += powerUps[i].addSpeed;
									players[balls[j].playerId].pallette.rect.height += powerUps[i].addHeight;
								}

								AddBalls(powerUps[i].addBalls);

								powerUps[i].isActive = false;

								powerUps[i].rect.x = GetRandomValue(mapLimits.x + OffSetSpawn, mapLimits.width - powerUps[i].rect.width - OffSetSpawn);
								powerUps[i].rect.y = GetRandomValue(mapLimits.y, mapLimits.height - powerUps[i].rect.height);
							}
					}
			}
		}

		void CheckVictoryCondition()
		{
			for (int i = 0; i < MaxPlayers; i++)
			{
				if (players[i].score >= scoreVictory)
				{
					playerVictory = players[i];
					endGameMenu = true;

					string newText;

					if (pvpMode)
						newText = "Player " + to_string(i) + " Victory!";
					else if (playerVictory.id == 1)
					{
						newText = "Victory!!";
						SetColorText(resultPanel, GreenWu);
					}
					else
					{
						newText = "Defeat!!";
						SetColorText(resultPanel, RedWu);
					}

					Vector2 pos;
					pos.x = screenWidth / 2;
					pos.y = screenHeight / 2;

					SetText(resultPanel, newText);
					SetPanelPosition(resultPanel, pos);
				}
			}
		}

		void AddDifficulty()
		{
			/*for (int i = 0; i < MaxBalls; i++)
			{
				if (balls[i].isActive)
					balls[i].speed += speedAddDiff;
			}*/

			AddPower();
		}



		void DrawUI()
		{
			DrawPanel(scorePanel);
			DrawPanel(playerOnePanel);
			DrawPanel(PlayerTwoPanel);

			if (pauseBalls && firstScreen)
			{
				DrawRectangle(0, 0, screenWidth, screenHeight, { 0,0,0,200 });

				for (int i = 0; i < TextsInGamePlay; i++)
				{
					DrawText(infoText[i]);
				}
			}

			if (pauseGame || endGameMenu)
			{
				DrawRectangle(0, 0, screenWidth, screenHeight, Color{ 0,0,0,200 });

				if (endGameMenu)
				{
					DrawPanel(resultPanel);
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
			for (int i = 0; i < MaxPlayers; i++)
			{
				DrawPallette(players[i].pallette);
			}
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
			for (int i = 0; i < maxPowerUps; i++)
			{
				if (powerUps[i].isActive)
					DrawPowerUp(powerUps[i]);
			}
		}



		void RestartRound()
		{
			InitBalls();

			players[0].pallette.rect.y = mapLimits.y + (mapLimits.height / 2 - (PalletteHeight / 2));
			players[0].pallette.rect.height = PalletteHeight;
			players[0].pallette.speed = PalletSpeed;

			players[1].pallette.rect.y = mapLimits.y + (mapLimits.height / 2 - (PalletteHeight / 2));
			players[1].pallette.rect.height = PalletteHeight;
			players[1].pallette.speed = PalletSpeed;

			pauseBalls = true;
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

				if (!powerUps[indexToActive].isActive)
				{
					powerUps[indexToActive].isActive = true;
					done = false;
				}

				chances--;
			}
		}

		void SetGameModeMultiplayer(bool active)
		{
			pvpMode = active;
		}
	}
}