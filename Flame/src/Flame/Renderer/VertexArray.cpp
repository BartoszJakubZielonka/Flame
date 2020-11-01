#include "flpch.h"
#include "Flame/Renderer/VertexArray.h"

#include "Flame/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace flame
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    FL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
		}

		FL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
