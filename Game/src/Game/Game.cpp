#include "Game/Game.h"

#include "Engine/Application/Application.h"
#include "Engine/Renderer/Renderer.h"
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

			Update(Engine::Utilities::Time::GetDeltaTime());
			Render();
		}
	}

	void Game::Update(float deltaTime)
	{
		//CLIENT_TRACE("{}", deltaTime);
		(void)deltaTime;
	}

	void Game::Render()
	{
		if (!m_Application || !m_Application->GetRenderer())
		{
			return;
		}

		m_Application->GetRenderer()->BeginFrame();
		m_Application->GetRenderer()->EndFrame();
	}
}

int main()
{
	Game::Game l_Game;

	l_Game.Run();

	return 0;
}