#include "SceneControls.h"

#include "sl.h"
#include "Constants.h"
#include "Input.h"

#include "Panel.h"

#include "GameLoop.h"

namespace game
{
	namespace controls
	{
		const int maxLines = 4;

		Panel creditsContent[maxLines];
		Vector2 textPos;

		Text text;

		float speedText = 100;

		void Init()
		{
			Rectangle rect;
			rect.x = screenWidth / 2;
			rect.y = screenHeight - 90;

			creditsContent[0] = CreatePanel(rect, "CONTROLS", 10, 10, 10, 10, 90, BLACK, RED);

			rect.y -= creditsContent[0].rect.height;
			creditsContent[1] = CreatePanel(rect, "Shoot \"W\"", 10, 10, 10, 10, 40, BLACK, BOARD);

			rect.y -= creditsContent[1].rect.height * 2;
			creditsContent[2] = CreatePanel(rect, "Movement: Left \"A\", Right \"D\"", 10, 10, 10, 10, 40, BLACK, BOARD);

			rect.y -= creditsContent[1].rect.height * 3;
			creditsContent[3] = CreatePanel(rect, "Pause / Menu in game: \"ESC\"", 10, 10, 10, 10, 40, BLACK, BOARD);

			text.color = GRAY_TRANSPARENT;
			text.text = "Press ESC to return";
			text.position.x = 50;
			text.position.y = 50;
			text.fontSize = 20;
		}

		void Input()
		{
			if (GetKeyDown(SL_KEY_ESCAPE))
			{
				Init();
				gameLoop::currentScene = gameLoop::SCENE::MENU;
			}
		}

		void Update()
		{

		}

		void Draw()
		{
			for (int i = 0; i < maxLines; i++)
			{
				DrawPanel(creditsContent[i]);
			}

			DrawText(text);
		}
	}
}
