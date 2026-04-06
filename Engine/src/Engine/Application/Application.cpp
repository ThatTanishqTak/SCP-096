#include "Engine/Application/Application.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Utilities/Log.h"
#include "Engine/Window/Window.h"

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
		if (!m_Running && !m_Renderer && !m_Window && !m_SDLInitialized)
		{
			return;
		}


		m_LayerStack.Clear();

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
		SDL_Event l_SDLEvent;
		while (SDL_PollEvent(&l_SDLEvent))
		{
			Event l_Event;
			switch (l_SDLEvent.type)
			{
				case SDL_EVENT_QUIT:
				{
					l_Event.Type = EventType::Quit;
					OnEvent(l_Event);

					break;
				}

				default:
				{
					break;
				}
			}
		}
	}

	void Application::OnUpdate(float deltaTime)
	{
		for (Layer* it_Layer : m_LayerStack)
		{
			it_Layer->OnUpdate(deltaTime);
		}
	}

	void Application::OnRender()
	{
		if (!m_Renderer)
		{
			return;
		}

		m_Renderer->BeginFrame();
		for (Layer* it_Layer : m_LayerStack)
		{
			it_Layer->OnRender();
		}
		m_Renderer->EndFrame();
	}

	void Application::OnEvent(Event& event)
	{
		if (event.Type == EventType::Quit)
		{
			m_Running = false;
		}

		for (auto it_Layer = m_LayerStack.rbegin(); it_Layer != m_LayerStack.rend(); ++it_Layer)
		{
			(*it_Layer)->OnEvent(event);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
}