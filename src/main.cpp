// #include <stdlib.h>
// #include <memory>
#include <iostream>


// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
#include "SceneRunner.hpp"
#include "ModelLoader.hpp"


// GLFWwindow* window;



int main( void )
{
	// SceneRunner	m_runner("My Cannon Balls");
	// std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new Scene());
	// return m_runner.run( *scene );

	// fs::path 
	std::string path_to_model = ("/home/denis/blender_study/untitled.obj");
	Model model;

	ModelLoader ml_helper;// = ModelLoader();	
	ml_helper.load(path_to_model, model);

	std::vector<size_t> statistics;
	model.getStatistics(statistics);
	for( auto &i : statistics){
		std::cout << i;
	}


	return 0;
}
