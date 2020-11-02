#pragma once

#include "Flame/Core/Base.h"

#include "Flame/Core/Window.h"
#include "Flame/Core/LayerStack.h"

#include "Flame/Events/Event.h"
#include "Flame/Events/ApplicationEvent.h"

#include "Flame/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace flame
{
	class Application
	{
	public:
		Application(const std::string& name = "Flame App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow();

		void Close();
		
		ImGuiLayer* GetImGuiLayer();

		static Application& Get();
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running{ true };
		bool m_Minimized{ false };
		
		LayerStack m_LayerStack;
		float m_LastFrameTime{ 0.0f };
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	//To be defined in client.
	Application* CreateApplication();

}
