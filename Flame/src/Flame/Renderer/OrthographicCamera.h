#pragma once

#include <glm/glm.hpp>

namespace flame 
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);
		
		~OrthographicCamera() = default;

		void SetPosition(const glm::vec3& position);
		void SetRotation(float rotation);

		[[nodiscard]] const glm::vec3& GetPosition() const;
		float GetRotation() const;

		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetViewProjectionMatrix() const;
	private:
		void RecalculateViewMatrix();

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;
		float m_Rotation;
	};
}