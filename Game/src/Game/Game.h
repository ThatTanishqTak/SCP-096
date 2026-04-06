#pragma once

#include <memory>

namespace Engine
{
	class Application;
}

namespace Game
{
	class Game
	{
	public:
		Game();
		~Game();

		void Run();

	private:
		void PollEvents();
		void Update(float deltaTime);
		void Render();

	private:
		std::unique_ptr<Engine::Application> m_Application;

		bool m_IsRunning = true;
	};
}