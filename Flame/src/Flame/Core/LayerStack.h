#pragma once

#include "Flame/Core/Core.h"
#include "Layer.h"

namespace flame
{

	class FLAME_API LayerStack
	{
	public:
		LayerStack();
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
		unsigned int m_LayerInsertIndex;
	};

}