#pragma once

#include <string>

namespace Engine
{
	struct Event;

	class Layer
	{
	public:
		Layer(const std::string& layerName) : m_DebugName(layerName)
		{

		}
		virtual ~Layer() = default;

		virtual void OnAttach()
		{

		}

		virtual void OnDetach()
		{

		}

		virtual void OnUpdate(float deltaTime)
		{
			static_cast<void>(deltaTime);
		}

		virtual void OnRender()
		{

		}

		virtual void OnEvent(Event& event)
		{
			static_cast<void>(event);
		}

		const std::string& GetDebugName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}