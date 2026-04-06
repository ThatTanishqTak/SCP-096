#pragma once

#include <SDL3/SDL.h>

#include <string>

namespace Engine
{
	class Window
	{
	public:
		Window() = default;
		~Window();

		bool Initialize(const std::string& title, int width, int height);
		void Shutdown();

		SDL_Window* GetWindow() const { return m_Window; }

	private:
		SDL_Window* m_Window = nullptr;
	};
}