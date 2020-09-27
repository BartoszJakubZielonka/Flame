#include "flpch.h"
#include "RendererAPI.h"

namespace flame
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	RendererAPI::API RendererAPI::GetAPI()
	{
		return s_API;
	}

}
