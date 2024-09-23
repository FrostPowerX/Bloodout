#include <iostream>

#include "sl.h"
#include "GameLoop.h"

#include "Ball.h"
#include "Pallette.h"

#include "SceneMenu.h"
#include "SceneGamePlay.h"
#include "SceneControls.h"
#include "SceneCredits.h"

#include "Constants.h"
#include "Color.h"
#include "Utils.h"
#include "Input.h"

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

		void Deinitialize();

		void Play()
		{
			Initialize();

			while (!slShouldClose() && programLoop)
			{
				Input();
				Update();
				Draw();
			}

			Deinitialize();
		}

		void Initialize()
		{
			slWindow(screenWidth, screenHeight, "Cacho", false);
			slLoadFont((fontDir + "ChainsawCarnage.ttf").c_str());
			slSetFont(0, 15);

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

		void Deinitialize()
		{
			slClose();
		}
	}
}