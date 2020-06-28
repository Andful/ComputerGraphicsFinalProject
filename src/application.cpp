//#include "Image.h"
#include "window.h"
// Always include window first (because it includes glfw, which includes GL which needs to be included AFTER glew).
// Can't wait for modules to fix this stuff...
#include "disable_all_warnings.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "drawable.h"
#include "scene.h"
#include "drawable_mesh.h"
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
        oldCPos(0), scene(1024, 1024)
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
        scene.addPostShader(std::make_shared<Shader>("shaders/postfxquad.vert.glsl", "shaders/postfxinverse.frag.glsl"));
        scene.addPostShader(std::make_shared<Shader>("shaders/postfxquad.vert.glsl", "shaders/postfxtest.frag.glsl"));

        std::shared_ptr<DrawableMesh> dragon =  std::make_shared<DrawableMesh>(
            Mesh("resources/dragon.obj"),
            Shader("shaders/shader.vert.glsl", "shaders/blinn_phong.frag.glsl"),
            Shader("shaders/shader.vert.glsl"),
            Texture("resources/checkerboard.png"),
            Shader("shaders/shader.vert.glsl", "shaders/xtoon.frag.glsl"),
            Texture("resources/toon_map.png"),
            Shader("shaders/shader.vert.glsl", "shaders/xraycull.frag.glsl")
        );
	    std::shared_ptr<DrawableMesh> dragon2 =  std::make_shared<DrawableMesh>(
			    Mesh("resources/dragon.obj"),
			    Shader("shaders/shader.vert.glsl", "shaders/blinn_phong.frag.glsl"),
			    Shader("shaders/shader.vert.glsl"),
			    Texture("resources/checkerboard.png"),
			    Shader("shaders/shader.vert.glsl", "shaders/xtoon.frag.glsl"),
			    Texture("resources/toon_map.png"),
			    Shader("shaders/shader.vert.glsl", "shaders/xraycull.frag.glsl")
	    );
        
        std::shared_ptr<DrawableMesh> platform = std::make_shared<DrawableMesh>(
        		Mesh("resources/platform.obj"),
        		Shader("shaders/shader.vert.glsl", "shaders/blinn_phong.frag.glsl"),
        		Shader("shaders/shader.vert.glsl"),
        		Texture("resources/checkerboard.png"),
		        Shader("shaders/shader.vert.glsl", "shaders/xtoon.frag.glsl"),
		        Texture("resources/toon_map.png"),
		        Shader("shaders/shader.vert.glsl", "shaders/xraycull.frag.glsl")
        		);
	    std::shared_ptr<DrawableMesh> platformSideways = std::make_shared<DrawableMesh>(
			    Mesh("resources/platform.obj"),
			    Shader("shaders/shader.vert.glsl", "shaders/blinn_phong.frag.glsl"),
			    Shader("shaders/shader.vert.glsl"),
			    Texture("resources/checkerboard.png"),
			    Shader("shaders/shader.vert.glsl", "shaders/xtoon.frag.glsl"),
			    Texture("resources/toon_map.png"),
			    Shader("shaders/shader.vert.glsl", "shaders/xraycull.frag.glsl")
	    );
        platform -> translate(glm::vec3(0.0, -1.5, 0.0));
        platformSideways->translate(glm::vec3(0, 0, 0));
        platformSideways->rotate(glm::vec3(1.5, 0, 0));
        platformSideways->scaling(glm::vec3(0.7, .7, .7));
        scene.add(dragon2);
        camera = std::make_shared<Camera>(1024,1024);
        group = std::make_shared<Group>();
        auto light = std::make_shared<DrawableLight>(glm::vec3(0, .2, .3), glm::vec3(0, 0, 0));
        auto light2 = std::make_shared<DrawableLight>(glm::vec3(.3, .1, 0), glm::vec3(0, 0, 0));
	    auto subgroup = std::make_shared<Group>();
        subgroup -> add(dragon);
        subgroup -> add(light2);
        light2->rotate(glm::vec3(0, 0, 1.5));
        subgroup -> translate(glm::vec3(2, 0, 0));
        group -> add(subgroup);
        scene.addLight(light);
	   scene.addLight(light2);
	    scene.add(group);
		camera->add(light);
		scene.add(platformSideways);
        scene.add(camera);
        scene.add(platform);

        scene.update();
    }

    void update()
    {
        // This is your game loop
        // Put your real-time logic and rendering in here
        while (!m_window.shouldClose()) {
            m_window.updateInput();
            group -> rotate(glm::vec3(0,0,0.01));
            scene.update();
            scene.render(*camera);
   
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
    		case GLFW_KEY_X:
    			scene.toggleXRay();
    			break;
    		case GLFW_KEY_M:
    			scene.samples++;
    			break;
    		case GLFW_KEY_N:
    			if(scene.samples >0) scene.samples--;
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
