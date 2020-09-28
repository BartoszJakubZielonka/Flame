#pragma once

#include "Flame.h"

class Sandbox2D : public flame::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(flame::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(flame::Event& e) override;
private:
	flame::OrthographicCameraController m_CameraController;
	
	// Temp
	flame::Ref<flame::VertexArray> m_SquareVA;
	flame::Ref<flame::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};