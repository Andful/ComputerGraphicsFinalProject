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
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

DISABLE_WARNINGS_POP()

class Camera
{
public:
	enum CAM_DIR {CAM_F, CAM_B, CAM_R, CAM_L};

	Camera(glm::vec3, glm::vec3, double, double);

	~Camera();

	void updateViewMatrix();

	void setEye(glm::vec3);

	void setCenter(glm::vec3);

	void setUp(glm::vec3);

	void mouseRotate(double, double);

	void move(CAM_DIR);

	static glm::vec3 calculateDir(double pitch, double yaw)
	{
		return normalize(glm::vec3(
				cos(yaw) * cos(pitch),
				 sin(pitch),
				sin(yaw) * cos(pitch)
		));
	}

	glm::mat4 m_viewMatrix;
	double sensitivity = 0.05;
	float movementMul = 0.1f;

private:
	glm::vec3 eye, up, center;
	double pitch, yaw;
};


#endif //COMPUTERGRAPHICS_CAMERA_H
