#include "flpch.h"
#include "Layer.h"

namespace flame
{
	Layer::Layer(std::string_view name) : m_debugName(name)
	{
	}

	void Layer::OnAttach()
	{
	}

	void Layer::OnDetach()
	{
	}

	void Layer::OnUpdate(Timestep ts)
	{
	}

	void Layer::OnImGuiRender()
	{
	}

	void Layer::OnEvent(Event& event)
	{
	}

	std::string_view Layer::GetName() const
	{
		return m_debugName;
	}
}