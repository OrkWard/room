#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 up;
public:
    Camera();
	glm::mat4 getViewMatrix() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;
    glm::vec3 getFront() const;
	virtual glm::mat4 getProjectionMatrix() const = 0;
};


class PerspectiveCamera : public Camera {
public:
    glm::mat4 project;
public:
	PerspectiveCamera(float fovy, float aspect, float znear, float zfar);

	glm::mat4 getProjectionMatrix() const override;
};


class OrthographicCamera : public Camera {
public:
    glm::mat4 project;
public:
	OrthographicCamera(float left, float right, float bottom, float top, float znear, float zfar);
	
	glm::mat4 getProjectionMatrix() const override;
};

#endif