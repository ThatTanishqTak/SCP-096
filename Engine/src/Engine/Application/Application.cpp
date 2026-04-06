#include "Engine/Application/Application.h"
#include "Engine/Window/Window.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Utilities/Log.h"
#include "Engine/Utilities/Time.h"

#include <SDL3/SDL.h>

#include <memory>

namespace Engine
{
	Application::Application() = default;
	Application::~Application()
	{
		Shutdown();
	}

	bool Application::Initialize(const std::string& title, int width, int height)
	{
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			CORE_ERROR("Failed to initialize SDL: {}", SDL_GetError());
			return false;
		}

		m_SDLInitialized = true;

		m_Window = std::make_unique<Window>();
		if (!m_Window->Initialize(title, width, height))
		{
			CORE_ERROR("Failed to initialize window");
			return false;
		}

		m_Renderer = std::make_unique<Renderer>();
		if (!m_Renderer->Initialize(m_Window.get()))
		{
			CORE_ERROR("Failed to initialize renderer");

			m_Window->Shutdown();
			m_Window.reset();

			return false;
		}

		return true;
	}

	void Application::Shutdown()
	{
		if (m_Renderer)
		{
			m_Renderer->Shutdown();
			m_Renderer.reset();
		}

		if (m_Window)
		{
			m_Window->Shutdown();
			m_Window.reset();
		}

		if (m_SDLInitialized)
		{
			SDL_Quit();
			m_SDLInitialized = false;
		}

		m_Running = false;
	}

	void Application::PollEvents()
	{
		SDL_Event l_Event;
		while (SDL_PollEvent(&l_Event))
		{
			switch (l_Event.type)
			{
				case SDL_EVENT_QUIT:
				{
					m_Running = false;
					break;
				}

				default:
				{
					break;
				}
			}
		}
	}
}