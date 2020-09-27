#pragma once
#include "Flame/Renderer/OrthographicCamera.h"
#include "Flame/Core/Timestep.h"

#include "Flame/Events/ApplicationEvent.h"
#include "Flame/Events/MouseEvent.h"

namespace flame
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		OrthographicCamera& GetCamera();
		const OrthographicCamera& GetCamera() const;
		
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		float GetZoomLevel() const;
		void SetZoomLevel(float level);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel{1.0f};

		bool m_Rotation;

		glm::vec3 m_CameraPosition{0.0f, 0.0f, 0.0f};
		float m_CameraRotation{0.0f};
		float m_CameraTranslationSpeed{1.0f};
		float m_CameraRotationSpeed{1.0f};
		
		OrthographicCamera m_Camera;
	};
}
