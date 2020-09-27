#include <Flame.h>

#include <Platform\OpenGL\OpenGLShader.h>

#include <imgui/imgui.h>
#include <glm\glm\gtc\type_ptr.hpp>
#include <glm\glm\ext\matrix_transform.hpp>

class ExampleLayer: public flame::Layer
{
public:
	ExampleLayer(): Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray.reset(flame::VertexArray::Create());

		std::array<float, 3 * 7> vertices{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		flame::Ref<flame::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(flame::VertexBuffer::Create(vertices.data(), sizeof(vertices)));
		flame::BufferLayout layout = {
			{ flame::ShaderDataType::Float3, "a_Position" },
			{ flame::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		std::array<uint32_t, 3> indices = { 0, 1, 2 };
		flame::Ref<flame::IndexBuffer> indexBuffer;
		indexBuffer.reset(flame::IndexBuffer::Create(indices.data(), sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVertexArray.reset(flame::VertexArray::Create());

		std::array<float, 5 * 4> squareVertices = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		flame::Ref<flame::VertexBuffer> squareVB;
		squareVB.reset(flame::VertexBuffer::Create(squareVertices.data(), sizeof(squareVertices)));
		squareVB->SetLayout({
			{ flame::ShaderDataType::Float3, "a_Position" },
			{ flame::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVertexArray->AddVertexBuffer(squareVB);

		std::array<uint32_t, 6> squareIndices = { 0, 1, 2, 2, 3, 0 };
		flame::Ref<flame::IndexBuffer> squareIB;
		squareIB.reset(flame::IndexBuffer::Create(squareIndices.data(), sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 460 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 460 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = flame::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = flame::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = flame::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = flame::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<flame::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<flame::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	~ExampleLayer() override = default;

	void OnUpdate(flame::Timestep ts) override
	{
		//Update
		m_CameraController.OnUpdate(ts);

		//Renderer
		flame::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		flame::RenderCommand::Clear();

		flame::Renderer::BeginScene(m_CameraController.GetCamera());

		const glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<flame::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<flame::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (auto y = 0; y < 20; y++)
		{
			for (auto x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				flame::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		const auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		flame::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		flame::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Triangle
		//flame::Renderer::Submit(m_Shader, m_VertexArray);

		flame::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(flame::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	flame::ShaderLibrary m_ShaderLibrary;
	flame::Ref<flame::Shader> m_Shader;
	flame::Ref<flame::VertexArray> m_VertexArray;

	flame::Ref<flame::Shader> m_FlatColorShader;
	flame::Ref<flame::VertexArray> m_SquareVertexArray;
	flame::Ref<flame::Texture2D> m_Texture, m_ChernoLogoTexture;

	flame::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox final : public flame::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}
	~Sandbox() = default;
};

flame::Application* flame::CreateApplication()
{
	return new Sandbox();
}