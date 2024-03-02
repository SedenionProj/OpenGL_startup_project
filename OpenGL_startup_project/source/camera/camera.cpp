#include "camera.h"

namespace Seden {

	// camera

	void Camera::setPosition(glm::vec3 position)
	{
		m_position = position;
		recalculateViewMatrix();
	}
	glm::mat4 Camera::getProjectionMatrix()
	{
		return m_projection;
	}
	glm::mat4 Camera::getViewMatrix()
	{
		return m_view;
	}
	glm::vec3 Camera::getPosition()
	{
		return m_position;
	}

	// perspective

	PerspectiveCamera::PerspectiveCamera(float m_aspectRatio, glm::vec3 position, float pitch, float yaw)
		: up(glm::vec3(0, 1, 0)), m_pitch(pitch), m_yaw(yaw)
	{
		m_position = position;
		m_projection = glm::perspective(glm::radians(90.f), m_aspectRatio, 0.1f, 100.f);
		updateFront();
		recalculateViewMatrix();
	}

	void PerspectiveCamera::setRotation(float pitch, float yaw)
	{
		pitch = pitch;
		yaw = yaw;
	}
	
	void PerspectiveCamera::rotate(float pitchVelocity, float yawVelocity)
	{
		m_pitch += pitchVelocity;
		m_yaw += yawVelocity;
		updateFront();
		recalculateViewMatrix();
	}
	void PerspectiveCamera::moveFront(float velocity)
	{
		m_position += front * velocity;
		recalculateViewMatrix();
	}
	void PerspectiveCamera::moveRight(float velocity)
	{
		m_position += glm::normalize(glm::cross(front, up)) * velocity;
		recalculateViewMatrix();
	}
	void PerspectiveCamera::moveUp(float velocity)
	{
		m_position += glm::vec3(0, velocity, 0);
		recalculateViewMatrix();
	}

	glm::vec2 PerspectiveCamera::getRotation()
	{
		return glm::vec2(m_pitch, m_yaw);
	}

	void PerspectiveCamera::updateFront()
	{
		front.x = glm::cos(m_yaw) * glm::cos(m_pitch);
		front.y = glm::sin(m_pitch);
		front.z = glm::sin(m_yaw) * glm::cos(m_pitch);
	}
	void PerspectiveCamera::recalculateViewMatrix()
	{
		m_view = glm::lookAt(m_position, m_position + front, up);
	}

	// orthographic

	OrthographicCamera::OrthographicCamera(float aspectRatio, glm::vec2 position, float rotation)
		: m_rotation(rotation)
	{
		m_position = glm::vec3(position,0);
		m_aspectRatio = aspectRatio;
		m_position = glm::vec4(0);
		m_view = glm::mat4(1);
		m_viewProjection = glm::mat4(1);
		recalculateProjectionMatrix();
		recalculateViewMatrix();
	}
	
	void OrthographicCamera::setRotation(float angle)
	{
		m_rotation = angle;
		recalculateViewMatrix();
	}
	void OrthographicCamera::setZoom(float level)
	{
		m_zoom = level;
		recalculateProjectionMatrix();
		recalculateViewMatrix();
	}

	glm::mat4 OrthographicCamera::getViewProjection()
	{
		return m_viewProjection;
	}
	float OrthographicCamera::getRotation()
	{
		return m_rotation;
	}
	float OrthographicCamera::getZoom()
	{
		return m_zoom;
	}

	void OrthographicCamera::rotate(float velocity)
	{
		m_rotation += velocity;
		recalculateViewMatrix();
	}

	void OrthographicCamera::moveRight(float velocity)
	{
		m_position += glm::vec3(cos(m_rotation), sin(m_rotation), 0) * velocity;
		recalculateViewMatrix();
	}

	void OrthographicCamera::moveUp(float velocity)
	{
		m_position += glm::vec3(-sin(m_rotation), cos(m_rotation), 0) * velocity;
		recalculateViewMatrix();
	}

	void OrthographicCamera::recalculateViewMatrix()
	{
		glm::mat4 m_view = glm::rotate(glm::mat4(1), -m_rotation, glm::vec3(0, 0, 1));
		m_view = glm::translate(m_view, -m_position);
		m_viewProjection = m_projection * m_view;
	}
	void OrthographicCamera::recalculateProjectionMatrix()
	{
		m_projection = glm::ortho(-m_aspectRatio*m_zoom, m_aspectRatio * m_zoom, -m_zoom, m_zoom, -1.f, 1.f);
	}

}