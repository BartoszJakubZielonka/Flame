#pragma once

#include <glad/glad.h>

#include "Flame/Renderer/Texture.h"

namespace flame
{
	class OpenGLTexture2D: public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(std::string_view path);
		~OpenGLTexture2D() override;

		// Inherited via Texture2D
		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;
		uint32_t GetRendererID() const override { return m_RendererID; }

		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot = 0) const override;
		bool operator==(const Texture& other) const override
		{
			return m_RendererID == static_cast<const OpenGLTexture2D&>(other).m_RendererID;
		}
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}