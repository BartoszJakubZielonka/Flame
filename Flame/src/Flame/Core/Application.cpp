#include "flpch.h"
#include "Application.h"

#include "Flame/Core/Log.h"

#include "Flame/Core/Timestep.h"

#include "Flame/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace flame
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FL_PROFILE_FUNCTION();
		FL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(FL_BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		FL_PROFILE_FUNCTION();
		Renderer::Shutdown();
	}

	void Application::Run()
	{
		FL_PROFILE_FUNCTION();
		while (m_Running)
		{
			FL_PROFILE_SCOPE("RunLoop")
			const auto newTime = glfwGetTime();
			const auto frameTime = static_cast<float>(newTime) - m_LastFrameTime;
			m_LastFrameTime = static_cast<float>(newTime);

			if (!m_Minimized)
			{
				{
					FL_PROFILE_SCOPE("Layerstack OnUpdate");
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(frameTime);
				}
			}
			m_ImGuiLayer->Begin();
			{
				FL_PROFILE_SCOPE("LayerStack OnImGuiRender")
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		FL_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(FL_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(FL_BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		FL_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		FL_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	Window& Application::GetWindow()
	{
		return *m_Window;
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		FL_PROFILE_FUNCTION();
		if(e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}