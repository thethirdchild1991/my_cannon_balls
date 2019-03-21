#include <stdlib.h>
#include <memory>
#include <iostream>

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
#include "SceneRunner.hpp"
#include "ModelLoader.hpp"


GLFWwindow* window;

int main( void )
{
	SceneRunner	m_runner("My Cannon Balls");
	std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new Scene());
	return m_runner.run( *scene );
}
