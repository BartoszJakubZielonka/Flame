#pragma once

#include "Flame/Core/Base.h"
#include "Layer.h"

namespace flame
{

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverLay(Layer* overlay);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::const_iterator begin() const;

		std::vector<Layer*>::iterator end();
		std::vector<Layer*>::const_iterator end() const;
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex{ 0 };
	};

}