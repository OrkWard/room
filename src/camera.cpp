#include "camera.h"

Camera::Camera() {
    center = glm::vec3(0.0f);
    up = glm::vec3(.0f, .0f, 1.f);
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, center, up);
}

glm::vec3 Camera::getUp() const {
    return glm::normalize(up);
}

glm::vec3 Camera::getRight() const {
    glm::vec3 front = center - position;
    return glm::normalize(glm::cross(up, front));
}

glm::vec3 Camera::getFront() const {
    return glm::normalize(center - position);
}

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect) {
    this->fovy = fovy;
    this->aspect = aspect;
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
	return glm::perspective(glm::radians(fovy), aspect, 0.1f, 10000.f);
}

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float znear, float zfar) {
    project = glm::ortho(left, right, bottom, top, znear, zfar);
}

glm::mat4 OrthographicCamera::getProjectionMatrix() const {
	return project;
}