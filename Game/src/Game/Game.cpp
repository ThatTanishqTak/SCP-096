#include "Game/Game.h"
#include "Game/GameLayer.h"

#include "Engine/Application/Application.h"
#include "Engine/Utilities/Log.h"
#include "Engine/Utilities/Time.h"

#include <SDL3/SDL.h>

#include <memory>

namespace Game
{
	Game::Game()
	{
		Engine::Utilities::Log::Initialize();
		Engine::Utilities::Time::Initialize();

		CLIENT_INFO("Initializing Game");

		m_Application = std::make_unique<Engine::Application>();
		if (!m_Application->Initialize("SCP-096", 1920, 1080))
		{
			CLIENT_ERROR("Failed to initialize game application");
			m_Application->Shutdown();
		}
		else
		{
			m_GameLayer = new GameLayer();
			m_Application->PushLayer(m_GameLayer);
		}

		CLIENT_INFO("Game Initialized");
	}

	Game::~Game()
	{
		CORE_INFO("Shutting down game");

		m_Application->Shutdown();
		m_Application.reset();
	}

	void Game::Run()
	{
		while (m_Application->IsRunning())
		{
			Engine::Utilities::Time::Update();

			m_Application->PollEvents();
			m_Application->OnUpdate(Engine::Utilities::Time::GetDeltaTime());
			m_Application->OnRender();
		}
	}
}

int main()
{
	Game::Game l_Game;

	l_Game.Run();

	return 0;
}