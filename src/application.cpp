//#include "Image.h"
#include "window.h"
// Always include window first (because it includes glfw, which includes GL which needs to be included AFTER glew).
// Can't wait for modules to fix this stuff...
#include "disable_all_warnings.h"
#include "gl/shader.h"
#include "gl/texture.h"
#include "prospective_camera.h"
#include "util3D/geometry.h"
#include "util3D/scene.h"
#include "util3D/mesh.h"
#include "util3D/group.h"
#include "util3D/directional_light.h"
#include "materials/solid_color_material.h"
#include "materials/blinn_phong_material.h"
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
    std::shared_ptr<ProspectiveCamera> camera;
    std::shared_ptr<Transformable> group;
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

        std::shared_ptr<Geometry> dragon_geometry = std::make_shared<Geometry>("resources/dragon.obj");
        std::shared_ptr<Material> solid_material = std::make_shared<SolidColorMaterial>(glm::vec3(1.0f,0.0f,0.0f));
        std::shared_ptr<Material> blinn_phong_material = std::make_shared<BlinnPhongMaterial>(glm::vec3(0.5, 0.5, 0.5), 10.0f, glm::vec3(0.4, 0.4, 0.4));
        std::shared_ptr<Mesh> dragon =  std::make_shared<Mesh>(
            dragon_geometry,
            blinn_phong_material
        );
        
        std::shared_ptr<Mesh> platform = std::make_shared<Mesh>(
        	std::make_shared<Geometry>("resources/platform.obj"),
            blinn_phong_material
        );

        platform -> translate(glm::vec3(0.0, -1.5, 0.0));
        auto new_dragon = std::make_shared<Mesh>(dragon_geometry, blinn_phong_material);
        scene.add(new_dragon);
        camera = std::make_shared<ProspectiveCamera>();
        group = std::make_shared<Group>();
       // auto light2 = std::make_shared<DirectionalLight>(camera->getProjectionMatrix(), glm::vec3(1, 0, 0), glm::ivec2(1024, 1024));
        auto light = std::make_shared<DirectionalLight>(camera -> getProjectionMatrix(),glm::vec3(1.0, 1.0, 0.0), glm::ivec2(500, 500));
       // light->rotate(glm::vec3(1.5, 0,0));
       // light->translate(glm::vec3(1, 1, 0));
        //auto light2 = std::make_shared<SpotLight>(glm::vec3(.3, .1, 0));
       // camera -> add(light2);
        camera -> add(light);
	    auto subgroup = std::make_shared<Group>();
        subgroup -> add(dragon);
       // subgroup -> add(light);
        camera->add(light);
        //subgroup -> add(light2);
        //light2->rotate(glm::vec3(0, 0, 1.5));
        subgroup -> translate(glm::vec3(2, 0, 0));
        group -> add(subgroup);
	    scene.add(group);
		//camera->add(light);
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
            camera -> render();
   
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
