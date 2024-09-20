#include <iostream>

#include "sl.h"
#include "GameLoop.h"

#include "entities/Ball.h"
#include "entities/Pallette.h"

#include "scenes/SceneMenu.h"
#include "scenes/SceneGamePlay.h"
#include "scenes/SceneControls.h"
#include "scenes/SceneCredits.h"

#include "utilities/Constants.h"
#include "utilities/Color.h"
#include "utilities/Utils.h"
#include "utilities/Input.h"

namespace game
{
	namespace gameLoop
	{
		SCENE currentScene = SCENE::MENU;

		bool programLoop = true;

		void Initialize();

		void Input();
		void Update();
		void Draw();

		void Play()
		{
			slWindow(screenWidth, screenHeight, "Cacho", false);
			slLoadFont((fontDir + "aerial.ttf").c_str());
			slSetFont(0, 15);

			Initialize();

			while (!slShouldClose() && programLoop)
			{
				Input();
				Update();
				Draw();
			}

			slClose();
		}

		void Initialize()
		{
			menu::Init();
			controls::Init();
			gameplay::Init();
			credits::Init();
		}

		void Input()
		{
			switch (currentScene)
			{
			case game::gameLoop::SCENE::MENU:
				menu::Input();
				break;

			case game::gameLoop::SCENE::CONTROLS:
				controls::Input();
				break;

			case game::gameLoop::SCENE::GAMEPLAY:
				gameplay::Input();
				break;

			case game::gameLoop::SCENE::CREDITS:
				credits::Input();
				break;

			default:
				break;
			}
		}

		void Update()
		{
			switch (currentScene)
			{
			case game::gameLoop::SCENE::MENU:
				menu::Update();
				break;

			case game::gameLoop::SCENE::CONTROLS:
				controls::Update();
				break;

			case game::gameLoop::SCENE::GAMEPLAY:
				gameplay::Update();
				break;

			case game::gameLoop::SCENE::CREDITS:
				credits::Update();
				break;

			default:
				break;
			}
		}

		void Draw()
		{
			switch (currentScene)
			{
			case game::gameLoop::SCENE::MENU:
				menu::Draw();
				break;

			case game::gameLoop::SCENE::CONTROLS:
				controls::Draw();
				break;

			case game::gameLoop::SCENE::GAMEPLAY:
				gameplay::Draw();
				break;

			case game::gameLoop::SCENE::CREDITS:
				credits::Draw();
				break;

			default:
				break;
			}

			slRender();
		}
	}
}