#include "SceneCredits.h"
#include "..\ui\Panel.h"
#include "..\GameLoop.h"
#include "..\utilities\Constants.h"

namespace game
{
	namespace credits
	{
		using namespace gameLoop;

		const int maxLines = 6;

		Panel creditsContent[maxLines];
		Vector2 textPos;

		float speedText = 100;

		void Init()
		{
			
			Rectangle rect;
			rect.x = screenWidth / 2;
			rect.y = screenHeight;

			//creditsContent[0] = CreatePanel(rect, "WuPong", 10, 10, 10, 10, 90, DarkBrownWu, OpaYellowWu);
			//rect.y += creditsContent[0].rect.height;
			//
			//creditsContent[1] = CreatePanel(rect, "DEVELOPER", 10, 10, 10, 10, 40, DarkBrownWu, RedWu);
			//rect.y += creditsContent[1].rect.height;
			//creditsContent[2] = CreatePanel(rect, "Emanuel Parajon", 10, 10, 10, 10, 20, DarkBrownWu, GreenWu);
			//rect.y += creditsContent[2].rect.height * 2;
			//
			//creditsContent[3] = CreatePanel(rect, "SPECIAL MENTIONS", 10, 10, 10, 10, 40, DarkBrownWu, RedWu);
			//rect.y += creditsContent[3].rect.height;
			//creditsContent[4] = CreatePanel(rect, "Sergio Baretto", 10, 10, 10, 10, 20, DarkBrownWu, GreenWu);
			//rect.y += creditsContent[4].rect.height;
			//creditsContent[5] = CreatePanel(rect, "Stefano Cvitanich", 10, 10, 10, 10, 20, DarkBrownWu, GreenWu);
		}

		void Input()
		{
			if (slGetKey(SL_KEY_ESCAPE))
			{
				Init();
				currentScene = SCENE::MENU;
			}
		}

		void Update()
		{
			for (int i = 0; i < maxLines; i++)
			{
				creditsContent[i].rect.y -= speedText * slGetDeltaTime();
				creditsContent[i].textPosition.y -= speedText * slGetDeltaTime();
			}

			if(creditsContent[maxLines - 1].rect.y + creditsContent[maxLines - 1].rect.height < 0)
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

			//DrawText("Press ESC to return", 50, screenHeight - 50, 10, GrayTransparent);
		}
	}
}


