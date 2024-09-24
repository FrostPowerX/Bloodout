#include "SceneCredits.h"

#include "sl.h"

#include "Panel.h"
#include "GameLoop.h"
#include "Constants.h"
#include "Input.h"

namespace game
{
	namespace credits
	{
		using namespace gameLoop;

		const int maxLines = 6;

		Panel creditsContent[maxLines];
		Vector2 textPos;
		Text text;

		float speedText = 100;

		void Init()
		{
			
			Rectangle rect;
			rect.x = screenWidth / 2;
			rect.y = 0;

			creditsContent[0] = CreatePanel(rect, GameName, 10, 10, 10, 10, 90, BLACK, RED);
			rect.y -= creditsContent[0].rect.height;
			
			creditsContent[1] = CreatePanel(rect, "DEVELOPER", 10, 10, 10, 10, 60, BLACK, RED);
			rect.y -= creditsContent[1].rect.height;
			creditsContent[2] = CreatePanel(rect, "Emanuel Parajon", 10, 10, 10, 10, 40, BLACK, BOARD);
			rect.y -= creditsContent[2].rect.height * 2;
			
			creditsContent[3] = CreatePanel(rect, "SPECIAL MENTIONS", 10, 10, 10, 10, 60, BLACK, RED);
			rect.y -= creditsContent[3].rect.height;
			creditsContent[4] = CreatePanel(rect, "Sergio Baretto", 10, 10, 10, 10, 40, BLACK, BOARD);
			rect.y -= creditsContent[4].rect.height;
			creditsContent[5] = CreatePanel(rect, "Stefano Cvitanich", 10, 10, 10, 10, 40, BLACK, BOARD);

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
				currentScene = SCENE::MENU;
			}
		}

		void Update()
		{
			for (int i = 0; i < maxLines; i++)
			{
				creditsContent[i].rect.y += speedText * slGetDeltaTime();
				creditsContent[i].text.position.y += speedText * slGetDeltaTime();
			}

			if(creditsContent[maxLines - 1].rect.y + creditsContent[maxLines - 1].rect.height > screenHeight)
			{
				Init();
				currentScene = SCENE::MENU;
			}
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


