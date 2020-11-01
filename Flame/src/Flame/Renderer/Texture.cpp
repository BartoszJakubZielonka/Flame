#include "flpch.h"
#include "Flame/Renderer/Texture.h"

#include "Flame/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace flame
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    FL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
		}

		FL_CORE_ASSERT(false, "Unknowon RendererAPI!");
		return nullptr;
	}
	
	Ref<Texture2D> Texture2D::Create(std::string_view path)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:    FL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
		}

		FL_CORE_ASSERT(false, "Unknowon RendererAPI!");
		return nullptr;
	}
}