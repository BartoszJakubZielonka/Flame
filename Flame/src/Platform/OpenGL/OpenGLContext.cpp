#include "flpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace flame
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle): m_WindowHandle(windowHandle)
	{
		FL_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		FL_PROFILE_FUNCTION();
		
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		FL_CORE_ASSERT(status, "Failed to initialize Glad!");

		FL_CORE_INFO("OpenGL Info:");
		FL_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		FL_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		FL_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		FL_PROFILE_FUNCTION();
		
		glfwSwapBuffers(m_WindowHandle);
	}

	
}
