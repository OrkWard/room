#include "camera.h"

Camera::Camera() {
    center = glm::vec3(0.0f);
    up = glm::vec3(.0f, .0f, 1.f);
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, center, up);
}

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float znear, float zfar) {
    project = glm::perspective(fovy, aspect, znear, zfar);
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
	return project;
}

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float znear, float zfar) {
    project = glm::ortho(left, right, bottom, top, znear, zfar);
}

glm::mat4 OrthographicCamera::getProjectionMatrix() const {
	return project;
}