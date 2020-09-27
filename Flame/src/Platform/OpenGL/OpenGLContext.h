#pragma once
#include "Flame/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace flame
{

	class FLAME_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}