#pragma once

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

	private:
		Window* m_Window = nullptr;
	};
}