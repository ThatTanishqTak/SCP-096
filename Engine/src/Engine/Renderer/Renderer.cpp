#include "Engine/Renderer/Renderer.h"
#include "Engine/Window/Window.h"
#include "Engine/Utilities/Log.h"

#include <SDL3/SDL.h>

namespace Engine
{
	Renderer::~Renderer()
	{
		Shutdown();
	}

	bool Renderer::Initialize(Window* window)
	{
		if (!window || !window->GetWindow())
		{
			CORE_ERROR("Renderer initialization failed: invalid window");
			return false;
		}

		m_Renderer = SDL_CreateRenderer(window->GetWindow(), nullptr);

		if (!m_Renderer)
		{
			CORE_ERROR("Failed to create renderer: {}", SDL_GetError());
			return false;
		}

		CORE_INFO("Initialized Renderer");

		return true;
	}

	void Renderer::Shutdown()
	{
		if (m_Renderer)
		{
			SDL_DestroyRenderer(m_Renderer);
			m_Renderer = nullptr;

			CORE_INFO("Renderer Shutdown Complete");
		}
	}

	void Renderer::BeginFrame()
	{
		SDL_SetRenderDrawColorFloat(m_Renderer, 0.05f, 0.05f, 0.05f, 1.0f);
		SDL_RenderClear(m_Renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_Renderer);
	}
}