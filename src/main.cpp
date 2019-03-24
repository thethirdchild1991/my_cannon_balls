// #include <stdlib.h>
// #include <memory>
#include <iostream>


// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
#include "SceneRunner.hpp"
#include "ModelLoader.hpp"
#include "Renderer.hpp"

// GLFWwindow* window;

const std::string string_path_to_model = "/home/denis/blender_study/untitled.obj";
const std::string string_path_to_vert_shader = "/home/denis/cpp/my_cannon_balls/src/shader/basic.vert";
const std::string string_path_to_frag_shader = "/home/denis/cpp/my_cannon_balls/src/shader/basic.frag";


void setupModel( std::vector<Model>& models_vector ){
	
	fs::path path_to_model = (string_path_to_model);		

	ModelLoader ml_helper;
	Model model;
	ml_helper.load(path_to_model, model);
	models_vector.push_back(model);
}

void setupRenderHelper(Renderer& render_helper){
	fs::path path_to_vert_shader = (string_path_to_vert_shader);
	fs::path path_to_frag_shader = (string_path_to_frag_shader);
	render_helper = Renderer(path_to_vert_shader, path_to_frag_shader);
}

int main( void )
{
	// SceneRunner	m_runner("My Cannon Balls");
	// std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new Scene());
	// return m_runner.run( *scene );
	std::vector<Model> models_vector;	
	setupModel(models_vector);

	Renderer render_helper;
	setupRenderHelper(render_helper);
	
	for( auto &m : models_vector ){
		render_helper.render(m);
	}

	return 0;
}
