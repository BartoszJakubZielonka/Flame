#pragma once
#include "Flame/Core/Window.h"
#include "Flame/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace flame
{

	class WindowsWindow : public flame::Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() override;

		void OnUpdate() override;

		[[nodiscard]] uint32_t GetWidth() const override;
		[[nodiscard]] uint32_t GetHeight() const override;

		//Window attributes.
		void SetEventCallback(const EventCallbackFn& callback) override;
		void SetVSync(bool enabled) override;
		[[nodiscard]] bool IsVSync() const override;

		void* GetNativeWindow() const override { return m_Window; }
		
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title{""};
			uint32_t Width{ 0 }, Height{ 0 };
			bool VSync{ true };

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}