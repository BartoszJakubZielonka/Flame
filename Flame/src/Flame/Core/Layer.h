#pragma once

#include "Flame/Core/Base.h"
#include "Flame/Core/Timestep.h"
#include "Flame/Events/Event.h"

namespace flame
{

	class Layer
	{
	public:
		Layer(std::string_view name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate(Timestep ts);
		virtual void OnImGuiRender();
		virtual void OnEvent(Event& event);

		[[nodiscard]] std::string_view GetName() const;
	protected:
		std::string m_debugName;
	};

}