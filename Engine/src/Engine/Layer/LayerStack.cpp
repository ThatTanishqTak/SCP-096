#include "Engine/Layer/LayerStack.h"

#include <algorithm>

namespace Engine
{
	LayerStack::~LayerStack()
	{
		for (Layer* it_Layer : m_Layers)
		{
			it_Layer->OnDetach();
			delete it_Layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsertIndex), layer);
		++m_LayerInsertIndex;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto a_Iterator = std::find(m_Layers.begin(), m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsertIndex), layer);
		if (a_Iterator != m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsertIndex))
		{
			layer->OnDetach();
			m_Layers.erase(a_Iterator);
			--m_LayerInsertIndex;

			delete layer;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto a_Iterator = std::find(m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsertIndex), m_Layers.end(), overlay);
		if (a_Iterator != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(a_Iterator);

			delete overlay;
		}
	}
}