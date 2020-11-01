#pragma once

#include "Flame.h"

class ExampleLayer : public flame::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(flame::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(flame::Event& e) override;
private:
	flame::ShaderLibrary m_ShaderLibrary;
	flame::Ref<flame::Shader> m_Shader;
	flame::Ref<flame::VertexArray> m_VertexArray;

	flame::Ref<flame::Shader> m_FlatColorShader;
	flame::Ref<flame::VertexArray> m_SquareVA;

	flame::Ref<flame::Texture2D> m_Texture, m_ChernoLogoTexture;

	flame::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};