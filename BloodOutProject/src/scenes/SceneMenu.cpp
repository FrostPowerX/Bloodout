#include "SceneMenu.h"

#include "..\utilities\Constants.h"
#include "..\utilities\Utils.h"

#include "..\ui\Button.h"
#include "..\ui\Panel.h"

#include "..\PongGame.h"

namespace pong
{
	namespace menu
	{
		enum class OPTIONS_MENU
		{
			SINGLEPLAYER,
			MULTIPLAYER,
			CONTROLS,
			CREDITS,
			EXIT
		};

		Button buttons[ButtonsInMenu];

		Panel gameNamePanel;

		void Init()
		{
			float buttonWidth = 200;
			float buttonHeight = 50;

			float buttonsOffset = 25;

			Vector2 buttonPos;

			buttonPos.x = (screenWidth / 2) - (buttonWidth / 2);
			buttonPos.y = screenHeight / (ButtonsInMenu - 2);

			std::string namesButtons[ButtonsInMenu];

			namesButtons[0] = "Singleplayer";
			namesButtons[1] = "Multiplayer";
			namesButtons[2] = "Controls";
			namesButtons[3] = "Credits";
			namesButtons[4] = "Exit";

			Rectangle rect;

			rect.x = (screenWidth / 2);
			rect.y = (screenHeight / 4);

			gameNamePanel = CreatePanel(rect, GameName, 10, 10, 10, 10, 90, DarkBrownWu, OpaYellowWu);

			for (int i = 0; i < ButtonsInMenu; i++)
			{
				Vector2 tempPos;
				tempPos = buttonPos;

				tempPos.y += (i * buttonHeight) + (buttonsOffset * (i + 1));

				buttons[i] = CreateButton(tempPos, buttonWidth, buttonHeight, namesButtons[i], 20, GreenWu, RedWu, DarkRedWu, OpaYellowWu);
			}
		}

		void Input()
		{
			if (IsKeyPressed(KEY_ESCAPE))
				programLoop = false;
		}

		void Update()
		{

			for (int i = 0; i < ButtonsInMenu; i++)
			{
				if (MouseOnTopButton(buttons[i]))
					if (IsButtonPressed(buttons[i]))
					{
						switch (OPTIONS_MENU(i))
						{
						case OPTIONS_MENU::SINGLEPLAYER:
							currentScene = SCENE::GAMEPLAY;
							mutliplayer = false;
							break;

						case OPTIONS_MENU::MULTIPLAYER:
							currentScene = SCENE::GAMEPLAY;
							mutliplayer = true;
							break;

						case OPTIONS_MENU::CONTROLS:
							currentScene = SCENE::CONTROLS;
							break;

						case OPTIONS_MENU::CREDITS:
							currentScene = SCENE::CREDITS;
							break;

						case OPTIONS_MENU::EXIT:
							programLoop = false;
							break;


						default:
							break;
						}
					}
			}

		}

		void Draw()
		{
			for (int i = 0; i < ButtonsInMenu; i++)
			{
				DrawButton(buttons[i]);
			}

			DrawPanel(gameNamePanel);
		}
	}
}