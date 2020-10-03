#pragma once
#include <glm/glm.hpp>

#include "Flame/Renderer/Shader.h"

//TODO: REMOVE!
typedef unsigned int GLenum;

namespace flame
{

	class OpenGLShader: public Shader
	{
	public:
		OpenGLShader(std::string_view filepath);
		OpenGLShader(std::string_view name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int value) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;

		[[nodiscard]] int OpenGLShader::GetUniformLocation(std::string_view name);

		[[nodiscard]] const std::string& GetName() const override;

		void UploadUniformInt(std::string_view name, int value);

		void UploadUniformFloat(std::string_view name, float value);
		void UploadUniformFloat2(std::string_view name, const glm::vec2& value);
		void UploadUniformFloat3(std::string_view name, const glm::vec3& value);
		void UploadUniformFloat4(std::string_view name, const glm::vec4& value);

		void UploadUniformMat3(std::string_view name, const glm::mat3& matrix);
		void UploadUniformMat4(std::string_view name, const glm::mat4& matrix);
	private:
		std::string ReadFile(std::string_view filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSource);

		std::unordered_map<std::string, int> m_UniformLocations;
		uint32_t m_RendererID;
		std::string m_Name;
	};

}