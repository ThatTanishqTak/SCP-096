#pragma once

struct SDL_Renderer;

namespace Engine
{
	class Window;

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer();

		bool Initialize(Window* window);
		void Shutdown();

		void BeginFrame();
		void EndFrame();

		SDL_Renderer* GetRenderer() const { return m_Renderer; }

	private:
		SDL_Renderer* m_Renderer = nullptr;
	};
}