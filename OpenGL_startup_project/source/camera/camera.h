#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Seden {
	class Camera {
	public:
		void setPosition(glm::vec3 position);
		glm::vec3 getPosition();
		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();
	protected:
		void virtual recalculateViewMatrix() = 0;
		glm::vec3 m_position;
		glm::mat4 m_projection;
		glm::mat4 m_view;
		float m_aspectRatio;
	};

	class PerspectiveCamera : public Camera{
	public:
		PerspectiveCamera(float aspectRatio, glm::vec3 position = glm::vec3(0,0,1), float pitch = 0, float yaw = -glm::pi<float>() / 2.f);

		void setRotation(float pitch, float yaw);

		glm::vec2 getRotation();

		void rotate(float pitchVelocity, float yawVelocity);
		void moveFront(float velocity);
		void moveRight(float velocity);
		void moveUp(float velocity);
	private:
		void virtual recalculateViewMatrix();
		void updateFront();
		float m_pitch;
		float m_yaw;
		glm::vec3 front;
		glm::vec3 up;

		
	};

	class LookAtCamera : public Camera{
	public:
		LookAtCamera(float aspectRatio, glm::vec3 center = glm::vec3(0), float level = 2, float pitch = 0, float yaw = -glm::pi<float>() / 2.f);
		void setRotation(float pitch, float yaw);
		void setZoom(float level);

		glm::vec2 getRotation();
		float getZoom();

		void rotate(float pitchVelocity, float yawVelocity);
	private:
		void virtual recalculateViewMatrix();
		glm::vec3 m_center;
		float m_zoom = 1.0f;
		float m_pitch;
		float m_yaw;
		glm::vec3 up;
	};

	class OrthographicCamera : public Camera {
	public:
		OrthographicCamera(float aspectRatio, glm::vec2 position = glm::vec2(0, 0), float rotation = 0);

		void setRotation(float angle);
		void setZoom(float level);
		
		glm::mat4 getViewProjection();
		float getRotation();
		float getZoom();

		void rotate(float velocity);
		void moveRight(float velocity);
		void moveUp(float velocity);

	private:
		void virtual recalculateViewMatrix();
		void recalculateProjectionMatrix();
		
		float m_rotation;
		float m_zoom = 1.0f;
		glm::mat4 m_viewProjection;
	};
	
}