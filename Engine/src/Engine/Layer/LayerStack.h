#pragma once

#include "Engine/Layer/Layer.h"

#include <cstddef>
#include <vector>

namespace Engine
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		LayerStack(const LayerStack&) = delete;
		LayerStack& operator=(const LayerStack&) = delete;
		LayerStack(LayerStack&&) = delete;
		LayerStack& operator=(LayerStack&&) = delete;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		auto begin() { return m_Layers.begin(); }
		auto end() { return m_Layers.end(); }
		auto begin() const { return m_Layers.begin(); }
		auto end() const { return m_Layers.end(); }

		auto rbegin() { return m_Layers.rbegin(); }
		auto rend() { return m_Layers.rend(); }
		auto rbegin() const { return m_Layers.rbegin(); }
		auto rend() const { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;
		size_t m_LayerInsertIndex = 0;
	};
}