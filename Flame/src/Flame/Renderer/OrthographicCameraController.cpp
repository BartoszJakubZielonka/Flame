#include "flpch.h"
#include "OrthographicCameraController.h"

#include "Flame/Core/Input.h"
#include "Flame/Core/KeyCodes.h"

namespace flame
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation): m_AspectRatio(aspectRatio), m_Rotation(rotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
		FL_PROFILE_FUNCTION();
	}

	OrthographicCamera& OrthographicCameraController::GetCamera()
	{
		return m_Camera;
	}

	const OrthographicCamera& OrthographicCameraController::GetCamera() const
	{
		return m_Camera;
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		FL_PROFILE_FUNCTION();
		
		if (Input::IsKeyPressed(FL_KEY_D))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(FL_KEY_A))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(FL_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(FL_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(FL_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(FL_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		FL_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(FL_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(FL_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}

	float OrthographicCameraController::GetZoomLevel() const
	{
		return m_ZoomLevel;
	}

	void OrthographicCameraController::SetZoomLevel(float level)
	{
		m_ZoomLevel = level;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		FL_PROFILE_FUNCTION();
		
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = glm::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		FL_PROFILE_FUNCTION();
		
		m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
