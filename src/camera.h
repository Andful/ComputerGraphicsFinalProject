//
// Created by erik on 5/25/20.
//

#ifndef COMPUTERGRAPHICS_CAMERA_H
#define COMPUTERGRAPHICS_CAMERA_H
#include "disable_all_warnings.h"
DISABLE_WARNINGS_PUSH()
#include <GL/glew.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
DISABLE_WARNINGS_POP()

class Camera
{
public:
	Camera();
	~Camera();


	void updateViewMatrix();
	void setEye(glm::vec3);
	void setCenter(glm::vec3);
	void setUp(glm::vec3);

	void startRotate();
	void endRotate();
	void mouseRotate(float, float);
	//void rotateCamera(glm::vec3 &axis, float rotation_deg);


	glm::mat4 m_viewMatrix = glm::lookAt(eye, center, up);
private:
	glm::vec3 moveEye;
	bool canRotate = false;
	glm::vec3 eye = glm::vec3(-1, 1, -1);
	glm::vec3 center = glm::vec3(0);
	glm::vec3 up = glm::vec3(0, 1, 0);
};


#endif //COMPUTERGRAPHICS_CAMERA_H
