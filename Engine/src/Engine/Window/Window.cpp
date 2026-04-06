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
		if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) || !SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3))
		{
			CORE_ERROR("Failed to set OpenGL major/minor version: {}", SDL_GetError());
			return false;
		}

		if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
		{
			CORE_ERROR("Failed to set OpenGL profile: {}", SDL_GetError());
			return false;
		}

		if (!SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1))
		{
			CORE_ERROR("Failed to enable double buffering: {}", SDL_GetError());
			return false;
		}

		if (!SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24))
		{
			CORE_ERROR("Failed to set depth buffer size: {}", SDL_GetError());
			return false;
		}

		if (!SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8))
		{
			CORE_ERROR("Failed to set stencil buffer size: {}", SDL_GetError());
			return false;
		}

		m_Window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		if (!m_Window)
		{
			CORE_ERROR("Failed to create window: {}", SDL_GetError());
			return false;
		}

		m_Context = SDL_GL_CreateContext(m_Window);
		if (!m_Context)
		{
			CORE_ERROR("Failed to create OpenGL context: {}", SDL_GetError());
			SDL_DestroyWindow(m_Window);
			m_Window = nullptr;

			return false;
		}

		if (!SDL_GL_MakeCurrent(m_Window, m_Context))
		{
			CORE_ERROR("Failed to make OpenGL context current: {}", SDL_GetError());
			SDL_GL_DestroyContext(m_Context);
			SDL_DestroyWindow(m_Window);
			
			m_Context = nullptr;
			m_Window = nullptr;

			return false;
		}

		if (!SDL_GL_SetSwapInterval(1))
		{
			CORE_WARN("Failed to enable VSync: {}", SDL_GetError());
		}

		return true;
	}

	void Window::Shutdown()
	{
		if (m_Context)
		{
			SDL_GL_DestroyContext(m_Context);
			m_Context = nullptr;
		}

		if (m_Window)
		{
			SDL_DestroyWindow(m_Window);
			m_Window = nullptr;
		}
	}

	void Window::SwapBuffers()
	{
		if (m_Window)
		{
			SDL_GL_SwapWindow(m_Window);
		}
	}
}