//#include "Image.h"
#include "window.h"
// Always include window first (because it includes glfw, which includes GL which needs to be included AFTER glew).
// Can't wait for modules to fix this stuff...
#include "disable_all_warnings.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
<<<<<<< HEAD
#include "camera.h"
#include "drawable.h"
#include "scene.h"
#include "drawable_mesh.h"
=======
#include "drawable.h"
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78
DISABLE_WARNINGS_PUSH()
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/string_cast.hpp>
DISABLE_WARNINGS_POP()
#include <functional>
#include <iostream>
#include <vector>

class Application {
private:
    Window m_window;
    // Shader for default rendering and for depth rendering
	enum mouse_status {MOUSE_DISABLED, MOUSE_REENABLED, MOUSE_ACTIVE};
	mouse_status mouse_movement = MOUSE_DISABLED;
    glm::dvec2 oldCPos;
    Scene scene;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Drawable> group;
public:
    Application()
        : m_window(glm::ivec2(1024, 1024), "Final Project", false),
        oldCPos(0)
    {
        m_window.registerKeyCallback([this](int key, int scancode, int action, int mods) {
            if (action == GLFW_PRESS || action == GLFW_REPEAT)
                onKeyPressed(key, mods, action);
            else if (action == GLFW_RELEASE)
                onKeyReleased(key, mods);
        });
        m_window.registerMouseMoveCallback(std::bind(&Application::onMouseMove, this, std::placeholders::_1));
        m_window.registerMouseButtonCallback([this](int button, int action, int mods) {
            if (action == GLFW_PRESS)
                onMouseClicked(button, mods);
            else if (action == GLFW_RELEASE)
                onMouseReleased(button, mods);
        });
        try {
<<<<<<< HEAD
            //m_defaultShader = Shader("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
            //m_shadowShader = Shader("shaders/shadow.vert.glsl");
=======
            m_defaultShader = Shader("shaders/shader.vert.glsl", "shaders/shader.frag.glsl");
            m_shadowShader = Shader("shaders/shadow.vert.glsl");
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78

            // Any new shaders can be added below in similar fashion.
            // ==> Don't forget to reconfigure CMake when you do!
            //     Visual Studio: PROJECT => Generate Cache for ComputerGraphics
            //     VS Code: ctrl + shift + p => CMake: Configure => enter
            // ....
        } catch (ShaderLoadingException& e) {
            std::cerr << e.what() << std::endl;
        }
        std::shared_ptr<DrawableMesh> dragon =  scene.create<DrawableMesh>(
            Mesh("resources/dragon.obj"),
            Shader("shaders/shader.vert.glsl", "shaders/shader.frag.glsl"),
            Texture("resources/checkerboard.png")
        ); 

        camera = scene.create<Camera>();
        group = scene.create<Group>();
        std::shared_ptr<Group> subgroup = scene.create<Group>();
        subgroup -> add(dragon);
        subgroup -> translate(glm::vec3(1, 0, 0));
        group -> add(subgroup);
        scene.add(group);
        scene.add(dragon);
        scene.add(camera);
    }

    void update()
    {
        // This is your game loop
        // Put your real-time logic and rendering in here
        while (!m_window.shouldClose()) {
            m_window.updateInput();
<<<<<<< HEAD
            group -> rotate(glm::vec3(0,0,0.01));
            camera -> render();
=======

            // Clear the screen
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // ...
            glEnable(GL_DEPTH_TEST);

            const glm::mat4 mvpMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
            // Normals should be transformed differently than positions (ignoring translations + dealing with scaling):
            // https://paroj.github.io/gltut/Illumination/Tut09%20Normal%20Transformation.html
            const glm::mat3 normalModelMatrix = glm::inverseTranspose(glm::mat3(m_modelMatrix));

            m_defaultShader.bind();
            glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(mvpMatrix));
            glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
            glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(normalModelMatrix));
            if (m_mesh.hasTextureCoords()) {
                m_texture.bind(0);
                glUniform1i(3, 0);
                glUniform1i(4, GL_TRUE);
            } else {
                glUniform1i(4, GL_FALSE);
            }

            m_mesh.draw();
>>>>>>> fa1109b6f083e67db6402c2f6b6f46510036cf78

            // Processes input and swaps the window buffer
            m_window.swapBuffers();
        }
    }

    // In here you can handle key presses
    // key - Integer that corresponds to numbers in https://www.glfw.org/docs/latest/group__keys.html
    // mods - Any modifier keys pressed, like shift or control
    void onKeyPressed(int key, int mods, int action)
    {
    	switch (key) {
    		case GLFW_KEY_ESCAPE:
    			if(action == GLFW_PRESS)
			    {
				    mouse_movement = mouse_movement == MOUSE_DISABLED ? MOUSE_REENABLED : MOUSE_DISABLED;
				    m_window.setMouseCapture();
			    }
    			break;
    		case GLFW_KEY_W:
    			camera -> translate(glm::orientate3(camera -> getRotation())*glm::vec3(0,0,-1));
    			break;
    		case GLFW_KEY_D:
    			camera -> translate(glm::orientate3(camera -> getRotation())*glm::vec3(1,0,0));
    			break;
    		case GLFW_KEY_A:
    			camera -> translate(glm::orientate3(camera -> getRotation())*glm::vec3(-1,0,0));
    			break;
    		case GLFW_KEY_S:
    			camera -> translate(glm::orientate3(camera -> getRotation())*glm::vec3(0,0,1));
    			break;
            case GLFW_KEY_Q:
    			camera -> translate(glm::vec3(0,1,0));
    			break;
            case GLFW_KEY_Z:
    			camera -> translate(glm::vec3(0,-1,0));
    			break;
    	}
        //std::cout << "Key pressed: " << key << std::endl;
    }

    // In here you can handle key releases
    // key - Integer that corresponds to numbers in https://www.glfw.org/docs/latest/group__keys.html
    // mods - Any modifier keys pressed, like shift or control
    void onKeyReleased(int key, int mods)
    {
        //std::cout << "Key released: " << key << std::endl;
    }

    // If the mouse is moved this function will be called with the x, y screen-coordinates of the mouse
    void onMouseMove(const glm::dvec2& cursorPos)
    {
		if(mouse_movement == MOUSE_DISABLED) return;
		else if(mouse_movement == MOUSE_REENABLED)
		{
			mouse_movement = MOUSE_ACTIVE;
			oldCPos = cursorPos;
			return;
		}
		else
		{
			glm::dvec2 delta = cursorPos - oldCPos;
			oldCPos = cursorPos;
			camera -> mouseRotate(delta.x, delta.y);
		}
    }

    // If one of the mouse buttons is pressed this function will be called
    // button - Integer that corresponds to numbers in https://www.glfw.org/docs/latest/group__buttons.html
    // mods - Any modifier buttons pressed
    void onMouseClicked(int button, int mods)
    {
       // std::cout << "Pressed mouse button: " << button << std::endl;
    }

    // If one of the mouse buttons is released this function will be called
    // button - Integer that corresponds to numbers in https://www.glfw.org/docs/latest/group__buttons.html
    // mods - Any modifier buttons pressed
    void onMouseReleased(int button, int mods)
    {
       // std::cout << "Released mouse button: " << button << std::endl;
    }
};


int main()
{
    Application app;
    app.update();

    return 0;
}
