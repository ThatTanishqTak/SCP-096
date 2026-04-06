#include "Engine/Window/Window.h"
#include "Engine/Utilities/Log.h"

#include <SDL3/SDL.h>

namespace Engine
{
	Window::~Window()
	{
		Shutdown();
	}

	bool Window::Initialize(const std::string& title, int width, int height)
	{
		m_Window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE /* | SDL_WINDOW_MAXIMIZED */);

		if (!m_Window)
		{
			CORE_ERROR("Failed to create window: {}", SDL_GetError());

			return false;
		}

		return true;
	}

	void Window::Shutdown()
	{
		if (m_Window)
		{
			SDL_DestroyWindow(m_Window);
			m_Window = nullptr;
		}
	}
}