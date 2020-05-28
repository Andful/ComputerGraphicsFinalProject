#ifndef _SHADING_H
/* Here we define all structures that encode constants used in fragment shading models */
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


// Structure for point lights

struct Light {
    glm::vec3 position;
    glm::vec3 color;
};

// structure for material shading details
struct ShadingData {
    // Diffuse (lambert)
    glm::vec3 kd{ 0.5f };
    // RED glm::vec3 kd = glm::vec3(1.0f,0.0f, 0.0f);
   // glm::vec3 kd{ 1.0f, 0.0f, 0.0f };
    // Specular (Phong/Blinn Phong)
    glm::vec3 ks{ 0.5f };
    float shininess = 3.0f;
    // Toon
    int toonDiscretize = 6;
    float toonSpecularThreshold = 0.49f;
};

#define _SHADING_H 

#endif 

/*_SHADING_H compiles the cpp's and then link the object files together into a main program. To include headers in cpp's use (#include "header.h")