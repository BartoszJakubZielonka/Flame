#include "flpch.h"
#include "WindowsWindow.h"

#include "Flame/Events/ApplicationEvent.h"
#include "Flame/Events/KeyEvent.h"
#include "Flame/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace flame
{
	static bool s_GLFWInitialized{ false };

	static void GLFWErrorCallback(const int error, const char* description)
	{
		FL_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props):m_Window(nullptr), m_Context(nullptr)
	{
		FL_PROFILE_FUNCTION();
		
		WindowsWindow::Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		FL_PROFILE_FUNCTION();
		
		WindowsWindow::Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		FL_PROFILE_FUNCTION();
		
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		FL_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if(!s_GLFWInitialized)
		{
			//TODO: glfwTerminate on system shutdown
			const auto success = glfwInit();
			FL_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(), nullptr, nullptr);
		
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, const int width, const int height)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			data.Width = static_cast<uint32_t>(width);
			data.Height = static_cast<uint32_t>(height);

			WindowResizeEvent event(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
			
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			WindowCloseEvent event;

			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, const int key, int scancode, const int action, int mods)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			default:
				break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, const unsigned int keycode)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, const int button, const int action, int mods)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
			case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			default: 
				break;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, const double xOffset, const double yOffset)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, const double xPos, const double yPos)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		FL_PROFILE_FUNCTION();
		
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		FL_PROFILE_FUNCTION();
		
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(const bool enabled)
	{
		FL_PROFILE_FUNCTION();
		
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	uint32_t WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	uint32_t WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		m_Data.EventCallback = callback;
	}
}
