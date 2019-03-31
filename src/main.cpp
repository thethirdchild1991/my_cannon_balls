// #include <stdlib.h>
// #include <memory>
// #include <iostream>


// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

// #include <glm/glm.hpp>
#include "SceneRunner.hpp"
#include "Renderer.hpp"
#include "ModelLoader.hpp"
#include <map>
#include <memory>
// #include "Singleton.hpp"
// #include "stb_image_include.h"


// GLFWwindow* window;

const std::string string_path_to_model = "/home/denis/blender_study/untitled2.obj";
const std::string string_path_to_vert_shader = "/home/denis/cpp/my_cannon_balls/src/shader/basic.vert";
const std::string string_path_to_frag_shader = "/home/denis/cpp/my_cannon_balls/src/shader/basic.frag";


void setupModel( std::vector<Model>& models_vector ){
	
	fs::path path_to_model = (string_path_to_model);		

	ModelLoader ml_helper;
	Model model;
	ml_helper.load(path_to_model, model);
	models_vector.emplace_back(model);
}

std::unique_ptr<Renderer> setupRenderHelper(){
	fs::path path_to_vert_shader = (string_path_to_vert_shader);
	fs::path path_to_frag_shader = (string_path_to_frag_shader);
	std::unique_ptr<Renderer> helper(new Renderer(path_to_vert_shader, path_to_frag_shader));
	return helper;
	// std::cout << "after render" << std::endl;
}

int main( void )
{
	// SceneRunner	m_runner("My Cannon Balls");
	// std::unique_ptr<Scene> scene = std::unique_ptr<Scene>(new Scene());
	// return m_runner.run( *scene );
	// int width, height, nrChannels;
	// unsigned char *data = stbi_load("/home/denis/blender_study/cube_texture.jpg", &width, &height, &nrChannels, 0);


	std::vector<Model> models_vector;	
	setupModel(models_vector);
	setupModel(models_vector);
	setupModel(models_vector);
	setupModel(models_vector);


	std::unique_ptr<Renderer> render_helper = setupRenderHelper();
	render_helper->setModels(models_vector);
	render_helper->render();

	// render_helper->activateShader();
	// for( auto &m : models_vector ){
	// 	render_helper->render(m);
	// }

	return 0;
}
