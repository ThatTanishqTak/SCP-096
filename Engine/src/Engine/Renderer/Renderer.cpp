#include "Engine/Renderer/Renderer.h"
#include "Engine/Window/Window.h"
#include "Engine/Utilities/Log.h"

#include <SDL3/SDL.h>
#include <glad/glad.h>

namespace Engine
{
	Renderer::~Renderer()
	{
		Shutdown();
	}

	bool Renderer::Initialize(Window* window)
	{
		if (!window || !window->GetWindow() || !window->GetContext())
		{
			CORE_ERROR("Renderer initialization failed: invalid window or OpenGL context");
			return false;
		}

		m_Window = window;

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)))
		{
			CORE_ERROR("Renderer initialization failed: failed to load GLAD");
			return false;
		}

		int l_Width = 0;
		int l_Height = 0;
		SDL_GetWindowSizeInPixels(m_Window->GetWindow(), &l_Width, &l_Height);
		glViewport(0, 0, l_Width, l_Height);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		const GLubyte* l_Vendor = glGetString(GL_VENDOR);
		const GLubyte* l_Renderer = glGetString(GL_RENDERER);
		const GLubyte* l_Version = glGetString(GL_VERSION);

		CORE_TRACE("Initialized OpenGL Renderer");

		if (l_Vendor && l_Renderer && l_Version)
		{
			CORE_TRACE("OpenGL Vendor: {}", reinterpret_cast<const char*>(l_Vendor));
			CORE_TRACE("OpenGL Renderer: {}", reinterpret_cast<const char*>(l_Renderer));
			CORE_TRACE("OpenGL Version: {}", reinterpret_cast<const char*>(l_Version));
		}

		return true;
	}

	void Renderer::Shutdown()
	{
		if (m_Window)
		{
			m_Window = nullptr;
			CORE_INFO("Renderer Shutdown Complete");
		}
	}

	void Renderer::BeginFrame()
	{
		if (!m_Window || !m_Window->GetWindow())
		{
			return;
		}

		int l_Width = 0;
		int l_Height = 0;
		SDL_GetWindowSizeInPixels(m_Window->GetWindow(), &l_Width, &l_Height);
		glViewport(0, 0, l_Width, l_Height);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::EndFrame()
	{
		if (!m_Window)
		{
			return;
		}

		m_Window->SwapBuffers();
	}
}