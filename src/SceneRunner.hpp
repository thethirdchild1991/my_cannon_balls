#ifndef SCENERUNNER_H
#define SCENERUNNER_H

#include <config.hpp>

#ifdef DEBUG_IO
#include<iostream>
#endif


#include <GLFW/glfw3.h>


class SceneRunner
{
private:
    /* data */
public:
    SceneRunner(/* args */){
        //do all init stuff
        if( !glfwInit() ){
#ifdef DEBUG_IO
            std::cout << "GLFW init failed" << std::endl;
            exit(-1);
#endif            
        }
    }
    ~SceneRunner(){
        //clean up
    }

    void render(){
        //scene render
    }


};

#endif