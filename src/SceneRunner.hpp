#ifndef SCENERUNNER_H
#define SCENERUNNER_H

#include "config.hpp"
#include "Scene.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// #include <glad/glad.h>
#ifdef DEBUG_IO
#include <iostream>
#include <thread>
#include <chrono>
#endif


class SceneRunner
{
private:
    GLFWwindow * window;
    int fbw, fbh;
public:
    SceneRunner(const std::string& winTitle, 
    int width = WIN_WIDTH, int height = WIN_HEIGHT, 
    int samples = 0, 
    GLclampf rst_red = 0.0,  GLclampf rst_green = 0.0, GLclampf rst_blue = 0.5, GLclampf rst_alpha = 1.0 ){
        //do all init stuff
        if( glfwInit() == GLFW_FALSE ){
#ifdef DEBUG_IO
            std::cout << "GLFW init failed" << std::endl;
            exit( EXIT_FAILURE );
#endif            
        }

        // Select OpenGL 4.3
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );

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
        
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        glClearColor(rst_red, rst_green, rst_blue, rst_alpha);


    }
    ~SceneRunner(){
        //clean up
    }

    int run( Scene& scene ){
        //scene render
        scene.init();
        while( ! glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) ) {
            scene.update();
            scene.render();
            glfwSwapBuffers(window);
            // // std::this_thread::sleep_for(std::chrono::milliseconds(10));            
            // glClear( GL_COLOR_BUFFER_BIT );
            // // Draw nothing, see you in tutorial 2 !
            // // Swap buffers
            // glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwTerminate();
        return EXIT_SUCCESS;

    }


};

#endif