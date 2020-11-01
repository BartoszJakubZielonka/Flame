#pragma once
#include "Flame/Renderer/Framebuffer.h"

namespace flame
{

	class OpenGLFramebuffer: public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		// Inherited via Framebuffer
		void Bind() override;

		void Unbind() override;

		void Resize(uint32_t width, uint32_t height) override;

		uint32_t GetColorAttachmentRendererID() const override;

		const FramebufferSpecification& GetSpecification() const override;
	private:
		uint32_t m_RendererID{ 0 };
		uint32_t m_ColorAttachment{ 0 }, m_DepthAttachment{ 0 };
		FramebufferSpecification m_Specification;
	};

}