#include "flpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace flame
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case flame::ShaderDataType::Float:    return GL_FLOAT;
		case flame::ShaderDataType::Float2:   return GL_FLOAT;
		case flame::ShaderDataType::Float3:   return GL_FLOAT;
		case flame::ShaderDataType::Float4:   return GL_FLOAT;
		case flame::ShaderDataType::Mat3:     return GL_FLOAT;
		case flame::ShaderDataType::Mat4:     return GL_FLOAT;
		case flame::ShaderDataType::Int:      return GL_INT;
		case flame::ShaderDataType::Int2:     return GL_INT;
		case flame::ShaderDataType::Int3:     return GL_INT;
		case flame::ShaderDataType::Int4:     return GL_INT;
		case flame::ShaderDataType::Bool:     return GL_BOOL;
		}

		FL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		FL_PROFILE_FUNCTION();
		
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		FL_PROFILE_FUNCTION();
		
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		FL_PROFILE_FUNCTION();
		
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		FL_PROFILE_FUNCTION();
		
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		FL_PROFILE_FUNCTION();
		
		FL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index{ 0 };
		const auto& layout = vertexBuffer->GetLayout();
		for(const auto& element: layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				reinterpret_cast<const void*>(element.Offset));
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		FL_PROFILE_FUNCTION();
		
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}


}
