#pragma once

#include "Flame/Renderer/Buffer.h"

namespace flame
{

	class FLAME_API OpenGLVertexBuffer final : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		void SetData(const void* data, uint32_t size) override;
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class FLAME_API OpenGLIndexBuffer final : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] uint32_t GetCount() const override;
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
	
}