#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Layer/LayerStack.h"

#include <memory>
#include <string>

namespace Engine
{
	class Window;
	class Renderer;
	class Layer;

	class Application
	{
	public:
		Application();
		~Application();

		bool Initialize(const std::string& title, int width, int height);
		void Shutdown();
		void PollEvents();
		void OnUpdate(float deltaTime);
		void OnRender();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window* GetWindow() const { return m_Window.get(); }
		Renderer* GetRenderer() const { return m_Renderer.get(); }

		bool IsSDLInitialized() const { return m_SDLInitialized; }
		bool IsRunning() const { return m_Running; }

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		LayerStack m_LayerStack;

		bool m_SDLInitialized = false;
		bool m_Running = true;
	};
}