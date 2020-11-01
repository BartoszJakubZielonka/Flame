#pragma once

#include "Flame/Core/Layer.h"

#include "Flame/Events/ApplicationEvent.h"
#include "Flame/Events/KeyEvent.h"
#include "Flame/Events/MouseEvent.h"

namespace flame
{

	class ImGuiLayer: public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& e) override;

		void Begin();
		void End();
	private:		
		float m_Time{ 0.0f };
	};

}