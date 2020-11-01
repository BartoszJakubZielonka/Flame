#include "flpch.h"
#include "Flame/Renderer/RenderCommand.h"

namespace flame
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
