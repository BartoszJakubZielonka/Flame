#include "flpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace flame
{
	Ref<Texture2D> Texture2D::Create(std::string_view path)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    FL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		FL_CORE_ASSERT(false, "Unknowon RendererAPI!");
		return nullptr;
	}
}