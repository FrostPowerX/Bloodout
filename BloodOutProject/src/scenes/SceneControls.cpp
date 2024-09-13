#include "SceneControls.h"

#include "..\utilities\Constants.h"
#include "..\ui\Panel.h"
#include "..\PongGame.h"


namespace pong
{
	namespace controls
	{
		const int maxLines = 3;

		Panel creditsContent[maxLines];
		Vector2 textPos;

		float speedText = 100;

		void Init()
		{
			Rectangle rect;
			rect.x = screenWidth / 2;
			rect.y = 100;

			creditsContent[0] = CreatePanel(rect, "CONTROLS", 10, 10, 10, 10, 90, DarkBrownWu, DarkRedWu);

			rect.y += creditsContent[0].rect.height;
			creditsContent[1] = CreatePanel(rect, "Player 1", 10, 10, 10, 10, 40, DarkBrownWu, GreenWu);

			rect.y += creditsContent[1].rect.height * 3;
			creditsContent[2] = CreatePanel(rect, "Player 2", 10, 10, 10, 10, 40, DarkBrownWu, GreenWu);
		}

		void Input()
		{
			if (IsKeyPressed(KEY_ESCAPE))
			{
				Init();
				currentScene = SCENE::MENU;
			}
		}

		void Update()
		{

		}

		void Draw()
		{
			Vector2 rectP1;
			rectP1.x = screenWidth / 2 - (keysP1.width * 0.1f / 2);
			rectP1.y = creditsContent[1].rect.y + (keysP1.height * 0.05f / 2);

			Vector2 rectP2;
			rectP2.x = screenWidth / 2 - (keysP2.width * 0.1f / 2);
			rectP2.y = creditsContent[2].rect.y + (keysP2.height * 0.05f / 2);

			DrawTextureEx(keysP1, rectP1, 0, 0.1f, WHITE);
			DrawTextureEx(keysP2, rectP2, 0, 0.1f, WHITE);

			for (int i = 0; i < maxLines; i++)
			{
				DrawPanel(creditsContent[i]);
			}

			DrawText("Press ESC to return", 50, screenHeight - 50, 10, GrayTransparent);
		}
	}
}
