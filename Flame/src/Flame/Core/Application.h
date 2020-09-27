#pragma once

#include "Core.h"

#include "Window.h"

#include "Flame/Core/LayerStack.h"

#include "Flame/Events/Event.h"
#include "Flame/Events/ApplicationEvent.h"

#include "Flame/ImGui/ImGuiLayer.h"

namespace flame
{

	class FLAME_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow();
		
		inline static Application& Get();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running{true};
		bool m_Minimized{ false };
		
		LayerStack m_LayerStack;
		float m_LastFrameTime{0.0f};
		
		static Application* s_Instance;
	};

	//To be defined in client.
	Application* CreateApplication();

}
