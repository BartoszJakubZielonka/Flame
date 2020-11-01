#include <Flame.h>
#include <Flame/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace flame
{
	class FlameEditor : public Application
	{
	public:
		FlameEditor() : Application("Flame Editor")
		{
			PushLayer(new EditorLayer());
		}

		~FlameEditor() = default;
	};

	Application* CreateApplication()
	{
		return new FlameEditor();
	}
}