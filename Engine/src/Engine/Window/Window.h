#pragma once

#include <string>

//struct SDL_Window;
//struct SDL_GLContext;

#include <SDL3/SDL.h>

namespace Engine
{
	class Window
	{
	public:
		Window() = default;
		~Window();

		bool Initialize(const std::string& title, int width, int height);
		void Shutdown();

		void SwapBuffers();

		SDL_Window* GetWindow() const { return m_Window; }
		SDL_GLContext GetContext() const { return m_Context; }

	private:
		SDL_Window* m_Window = nullptr;
		SDL_GLContext m_Context;
	};
}