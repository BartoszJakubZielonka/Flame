#include "flpch.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>
#include <filesystem>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace flame
{
	static GLenum ShaderTypeFromString(std::string_view type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		FL_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(std::string_view filepath)
	{
		FL_PROFILE_FUNCTION();
		
		const auto source = ReadFile(filepath);
		const auto shaderSource = PreProcess(source);
		Compile(shaderSource);

		const std::filesystem::path path = filepath;
		m_Name = path.stem().string();
	}

	OpenGLShader::OpenGLShader(std::string_view name, const std::string& vertexSrc, const std::string& fragmentSrc): m_Name(std::string(name))
	{
		FL_PROFILE_FUNCTION();
		
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		FL_PROFILE_FUNCTION();
		
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(std::string_view filepath)
	{
		FL_PROFILE_FUNCTION();
		
		std::string result;
		std::ifstream in(std::string(filepath), std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			FL_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		FL_PROFILE_FUNCTION();
		
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		auto typeTokenLength = strlen(typeToken);
		auto pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			auto eol = source.find_first_of("\r\n", pos);
			FL_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			auto begin = pos + typeTokenLength + 1;
			auto type = source.substr(begin, eol - begin);
			FL_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			auto nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		FL_PROFILE_FUNCTION();
		
		const auto program = glCreateProgram();

		FL_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now!")
		
		std::vector<GLint> glShaderIDs;
		glShaderIDs.reserve(shaderSources.size());

		//auto glShaderIdIndex{ 0 };
		for (auto&& [type, source] : shaderSources)
		{
			const auto shader = glCreateShader(type);

			const auto* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, nullptr);

			glCompileShader(shader);

			auto isCompiled{ 0 };
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				auto maxLength{ 0 };
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				FL_CORE_ERROR("{0}", infoLog.data());
				FL_CORE_ASSERT(false, "Shader compilation failure!")
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs.push_back(shader);
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		auto isLinked{ 0 };
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			auto maxLength{ 0 };
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			FL_CORE_ERROR("{0}", infoLog.data());
			FL_CORE_ASSERT(false, "Shader link failure!")
			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::Bind() const
	{
		FL_PROFILE_FUNCTION();
		
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		FL_PROFILE_FUNCTION();
		
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		FL_PROFILE_FUNCTION();
		
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		FL_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		FL_PROFILE_FUNCTION();
		
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		FL_PROFILE_FUNCTION();
		
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		FL_PROFILE_FUNCTION();
		
		UploadUniformMat4(name, value);
	}

	const std::string& OpenGLShader::GetName() const
	{
		return m_Name;
	}

	int OpenGLShader::GetUniformLocation(std::string_view name)
	{
		FL_PROFILE_FUNCTION();
		
		auto location{ 0 };
		if (m_UniformLocations.find(std::string(name)) == m_UniformLocations.end())
		{
			location = glGetUniformLocation(m_RendererID, name.data());
			m_UniformLocations[std::string(name)] = location;
		}
		else
		{
			location = m_UniformLocations[std::string(name)];
		}

		return location;
	}

	void OpenGLShader::UploadUniformInt(std::string_view name, int value)
	{
		FL_PROFILE_FUNCTION();
		
		const auto location = GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		const auto location = GetUniformLocation(name);
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(std::string_view name, float value)
	{
		FL_PROFILE_FUNCTION();
		
		const auto location = GetUniformLocation(name);
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(std::string_view name, const glm::vec2& value)
	{
		FL_PROFILE_FUNCTION();
		
		const auto location = GetUniformLocation(name);
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(std::string_view name, const glm::vec3& value)
	{
		FL_PROFILE_FUNCTION();
		
		const auto location = GetUniformLocation(name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(std::string_view name, const glm::vec4& value)
	{
		FL_PROFILE_FUNCTION();
		
		const auto location = GetUniformLocation(name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(std::string_view name, const glm::mat3& matrix)
	{
		FL_PROFILE_FUNCTION();
		
		const auto location = GetUniformLocation(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(std::string_view name, const glm::mat4& matrix)
	{
		FL_PROFILE_FUNCTION();
		
		const auto location = GetUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}
