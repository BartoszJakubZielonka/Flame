#include "flpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace flame
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
