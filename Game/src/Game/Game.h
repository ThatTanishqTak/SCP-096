#pragma once

#include <memory>

namespace Engine
{
	class Application;
}

namespace Game
{
	class GameLayer;

	class Game
	{
	public:
		Game();
		~Game();

		void Run();

	private:
		std::unique_ptr<Engine::Application> m_Application;
		GameLayer* m_GameLayer = nullptr;
	};
}