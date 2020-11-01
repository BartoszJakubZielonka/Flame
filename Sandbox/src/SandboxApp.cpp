#include <Flame.h>
#include <Flame/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox final : public flame::Application
{
public:
	Sandbox(): flame::Application("Sandbox")
	{
		//PushLayer(new ExampleLayer);
		PushLayer(new Sandbox2D);
	}
	~Sandbox() = default;
};

flame::Application* flame::CreateApplication()
{
	return new Sandbox();
}