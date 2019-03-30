#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "config.hpp"
#include <stdlib.h>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Model.hpp"
#include "Shader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <map>




class Renderer{
    public:
        Renderer(){
            initContext();
        };
        Renderer(   const fs::path& vert_shader_path,
                    const fs::path& frag_shader_path )
        {            
            initContext();
            m_shaders.emplace_back( vert_shader_path, frag_shader_path );
            
        }
        Renderer(   const Shader& shader_in )
        {
            initContext();
            m_shaders.push_back(shader_in);
        }

        

        ~Renderer(){
            glfwTerminate();
#ifdef DEBUG_IO
            std::cout << "Trminated" << std::endl;
#endif
        };


        void render(){
            while( ! glfwWindowShouldClose(m_window) && !glfwGetKey(m_window, GLFW_KEY_ESCAPE) ) {

                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                auto shader_id = activateShader();
                int i = -1;

                glm::mat4 view_mat = glm::mat4(1.0f);
                glm::mat4 projection_mat = glm::mat4(1.0f);

                float radius = 10.0f;
                float camX = sin(i*glfwGetTime()) * radius;
                float camY = sin(i*glfwGetTime()) * radius * 0;
                float camZ  = cos(i*glfwGetTime()) * radius;

                glm::vec3 cameraPos = glm::vec3(camX, camY, camZ);
                glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
                // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

                glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
                // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
                // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
                
                view_mat = glm::lookAt(cameraPos, cameraTarget, up);
                projection_mat = glm::perspective(glm::radians(45.0f), float(WIN_WIDTH) / float(WIN_HEIGHT), 0.1f, 100.0f);
                // projection_mat = glm::ortho(0.0f, float(WIN_WIDTH), 0.0f, float(WIN_HEIGHT), -100.1f, 100.0f);



                for(auto &model : m_models){
                    i++;
                    model.activate();  
                    glm::mat4 model_mat = glm::mat4(1.0f);

                    model_mat = glm::translate(model_mat, glm::vec3(i*1.0f, i*1.0f, i*1.0f ));
                    model_mat = glm::rotate(model_mat, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
                    model_mat = glm::scale(model_mat, glm::vec3( 0.5 ) );

                    // view_mat = glm::translate(view_mat, glm::vec3(0.0f, 0.0f, -3.0f));

                    // glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                    
                    

                    unsigned int modelformLoc = glGetUniformLocation( shader_id , "model_mat");
                    glUniformMatrix4fv(modelformLoc, 1, GL_FALSE, glm::value_ptr(model_mat));

                    unsigned int viewformLoc = glGetUniformLocation( shader_id , "view_mat");
                    glUniformMatrix4fv(viewformLoc, 1, GL_FALSE, glm::value_ptr(view_mat));

                    unsigned int projecitonformLoc = glGetUniformLocation( shader_id , "projection_mat");
                    glUniformMatrix4fv(projecitonformLoc, 1, GL_FALSE, glm::value_ptr(projection_mat));
                    

                    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
                    // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
                    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

                    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
                    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
                    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);


                    // glm::mat4 view;
                    // view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                    // glm::vec3(0.0f, 0.0f, 0.0f),
                    // glm::vec3(0.0f, 1.0f, 0.0f));

                    
                    
                    // model.activate(); 
                    // glDrawArrays(GL_TRIANGLES, 0, 3);
                    // glBindVertexArray(0); 
                    glEnable(GL_DEPTH_TEST);
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    glDrawElements(GL_TRIANGLES, model.indicesCount(), GL_UNSIGNED_INT, 0);
                }
                

                // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
                // -------------------------------------------------------------------------------
                glfwSwapBuffers(m_window);
                glfwPollEvents();
            }
            glfwTerminate();            
        };


        void setModels(std::vector<Model>& models){
            m_models.assign(models.begin(), models.end());
        }

        void addShader( const Shader& in ){
            m_shaders.push_back(in);
        }
        const shader_program activateShader( const int activeIndex = 0){
            m_activeShaderIndex = activeIndex;
            m_shaders[m_activeShaderIndex].activate();
            return m_shaders[m_activeShaderIndex].getShaderId();
        }

    private:

        void initContext(
                            const std::string& winTitle = "MyWindow", 
                            int width = WIN_WIDTH, int height = WIN_HEIGHT, 
                            int samples = 0, 
                            GLclampf rst_red = 0.0,  
                            GLclampf rst_green = 0.0, 
                            GLclampf rst_blue = 0.5, 
                            GLclampf rst_alpha = 1.0 )

        {

            if( glfwInit() == GLFW_FALSE ){
#ifdef DEBUG_IO
                std::cout << "GLFW init failed" << std::endl;                
#endif
                exit(EXIT_FAILURE);
            }
            
            glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
            glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );

            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

            m_window = glfwCreateWindow( WIN_WIDTH, WIN_HEIGHT, winTitle.c_str(), NULL, NULL);

            if( !m_window ){
#ifdef DEBUG_IO
                std::cout << "Failed to open GLFW window" << std::endl;
#endif
                glfwTerminate();
                exit( EXIT_FAILURE );
            }

            glfwMakeContextCurrent(m_window);
            glfwGetFramebufferSize(m_window, &fbw, &fbh);

            if (glewInit() != GLEW_OK) {
#ifdef DEBUG_IO
                std::cout << "Failed to initialize GLEW" << std::endl;            
#endif                
                glfwTerminate();
                exit(EXIT_FAILURE);
            }

            glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

            glClearColor(rst_red, rst_green, rst_blue, rst_alpha);

        };

        std::vector<Model> m_models;
        // std::map<SHADERS, Shader> m_shaders;        
        std::vector<Shader> m_shaders;
        unsigned int m_activeShaderIndex;

        GLFWwindow * m_window;
        int fbw, fbh;
};

#endif