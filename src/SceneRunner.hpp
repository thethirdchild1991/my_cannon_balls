#ifndef SCENERUNNER_H
#define SCENERUNNER_H

#include <config.hpp>

#ifdef DEBUG_IO
#include<iostream>
#endif

#include <GLFW/glfw3.h>
#include <GL/glew.h>
// #include <glad/glad.h>



class SceneRunner
{
private:
    GLFWwindow * window;
    int fbw, fbh;
public:
    SceneRunner(const std::string& winTitle, 
    int width = WIN_WIDTH, int height = WIN_HEIGHT, 
    int samples = 0, 
    GLclampf rst_red = 0.0,  GLclampf rst_green = 0.0, GLclampf rst_blue = 0.0, GLclampf rst_alpha = 0.0 ){
        //do all init stuff
        if( !glfwInit() ){
#ifdef DEBUG_IO
            std::cout << "GLFW init failed" << std::endl;
            exit( EXIT_FAILURE );
#endif            
        }

        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        if(samples > 0) {
            glfwWindowHint(GLFW_SAMPLES, samples);
        }

        window = glfwCreateWindow( WIN_WIDTH, WIN_HEIGHT, winTitle.c_str(), NULL, NULL );
        if( ! window ) {
            std::cout << "Failed to open GLFW window" << std::endl;
            glfwTerminate();
            exit( EXIT_FAILURE );
        }
        glfwMakeContextCurrent(window);

        glfwGetFramebufferSize(window, &fbw, &fbh);

        if (glewInit() != GLEW_OK) {
            std::cout << "Failed to initialize GLEW" << std::endl;            
            glfwTerminate();
            exit(EXIT_FAILURE);
        }


        glClearColor(rst_red, rst_green, rst_blue, rst_alpha);


    }
    ~SceneRunner(){
        //clean up
    }

    void render(){
        //scene render
    }


};

#endif