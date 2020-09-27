#pragma once
#include "Flame/Renderer/VertexArray.h"

namespace flame
{

	class OpenGLVertexArray: public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const Ref<VertexBuffer>&) override;
		void SetIndexBuffer(const Ref<IndexBuffer>&) override;

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override;
		const Ref<IndexBuffer>& GetIndexBuffer() const override;
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}