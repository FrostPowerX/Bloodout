#pragma once

namespace game
{
	namespace gameLoop
	{
		enum class SCENE
		{
			MENU,
			CONTROLS,
			GAMEPLAY,
			CREDITS
		};

		extern SCENE currentScene;

		extern bool programLoop;

		void Play();
	}
}
