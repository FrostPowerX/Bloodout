#include "SceneMenu.h"

#include "..\utilities\Constants.h"
#include "..\utilities\Utils.h"
#include "..\utilities\Input.h"

#include "..\ui\Button.h"
#include "..\ui\Panel.h"

#include "..\GameLoop.h"

namespace game
{
	namespace menu
	{
		using namespace gameLoop;

		enum class OPTIONS_MENU
		{
			PLAY,
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

			buttonPos.x = (screenWidth / 2);
			buttonPos.y = screenHeight - buttonsOffset;

			std::string namesButtons[ButtonsInMenu];

			namesButtons[0] = "Play";
			namesButtons[1] = "Controls";
			namesButtons[2] = "Credits";
			namesButtons[3] = "Exit";

			Rectangle rect;

			rect.x = (screenWidth / 2);
			rect.y = (screenHeight / 4);

			gameNamePanel = CreatePanel(rect, GameName, 10, 10, 10, 10, 90, WHITE, YELLOW);

			for (int i = 0; i < ButtonsInMenu; i++)
			{
				Vector2 tempPos;
				tempPos = buttonPos;

				tempPos.y -= (i * buttonHeight) + (buttonsOffset * (i + 1));

				buttons[i] = CreateButton(tempPos, buttonWidth, buttonHeight, namesButtons[i], 20, GREEN, RED, BLUE, YELLOW);
			}
		}

		void Input()
		{
			if (GetKeyDown(SL_KEY_ESCAPE))
			{
				cout << "Se presiono\n";
				//programLoop = false;
			}
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
						case OPTIONS_MENU::PLAY:
							currentScene = SCENE::GAMEPLAY;
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