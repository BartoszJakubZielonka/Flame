#include "flpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace flame
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FL_CORE_ASSERT(false, "RendererAPI is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		FL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			FL_CORE_ASSERT(false, "RendererAPI is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		FL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
	inline uint32_t BufferLayout::GetStride() const
	{
		return m_Stride;
	}

	inline const std::vector<BufferElement>& BufferLayout::GetElements() const
	{
		return m_Elements;
	}

	std::vector<BufferElement>::iterator BufferLayout::begin()
	{
		return m_Elements.begin();
	}

	std::vector<BufferElement>::iterator BufferLayout::end()
	{
		return m_Elements.end();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::begin() const
	{
		return m_Elements.begin();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::end() const
	{
		return m_Elements.end();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		m_Stride = 0;
		for(auto& element: m_Elements)
		{
			element.Offset = m_Stride;
			m_Stride += element.Size;
		}
	}

	
}
