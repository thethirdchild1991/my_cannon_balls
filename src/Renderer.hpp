#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "config.hpp"
#include <stdlib.h>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Model.hpp"
#include "Shader.hpp"
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
        Renderer(   const Model& model_in, 
                    const fs::path& vert_shader_path,
                    const fs::path& frag_shader_path ) : m_model(model_in)                    
        {
            initContext();
            m_shaders.emplace_back( vert_shader_path, frag_shader_path );
        }

        Renderer(   const Shader& shader_in )
        {
            initContext();
            m_shaders.push_back(shader_in);
        }

        Renderer(   const Shader& shader_in, 
                    const Model& model_in ) : m_model(model_in)
        {
            initContext();
            m_shaders.push_back(shader_in);
        };

        ~Renderer(){
            glfwTerminate();
#ifdef DEBUG_IO
            std::cout << "Trminated" << std::endl;
#endif
        };

        void render(){
            render(m_model);
        };
        void render(Model& model){
            while( ! glfwWindowShouldClose(m_window) && !glfwGetKey(m_window, GLFW_KEY_ESCAPE) ) {

                

                // render the triangle
                
                float vertices[] = {
                    // positions         // colors
                    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
                    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
                    0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
                };

                unsigned int VBO, VAO, EBO;
                glGenVertexArrays(1, &VAO);//VERTEX ARRAY OBJECT
                glGenBuffers(1, &VBO);//VERTEX BUFFER OBJECT 
                // glGenBuffers(1, &EBO);//ELEMENT_ARRAY_BUFFER
                
                glBindVertexArray(VAO);

                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

                // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
                // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);                              
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));                              
                glEnableVertexAttribArray(1);
                
                //unbind
                glBindBuffer(GL_ARRAY_BUFFER, 0); 
                glBindVertexArray(0); 

/////////////////////////////////////////////////////////////////////////////////////
                glClear( GL_COLOR_BUFFER_BIT );
                activateShader();
                model.bind(); //glBindVertexArray(VAO); 
                
                glDrawArrays(GL_TRIANGLES, 0, 3);
                // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
                // -------------------------------------------------------------------------------
                glfwSwapBuffers(m_window);
                glfwPollEvents();



            }
            glfwTerminate();
            // return EXIT_SUCCESS;
        };


        void model(Model& in) { m_model = in; }
        const Model& model() const { return m_model; }
        Model& model() { return m_model; }

        void addShader( const Shader& in ){
            m_shaders.push_back(in);
        }
        void activateShader( const int activeIndex = 0){
            m_activeShaderIndex = activeIndex;
            m_shaders[m_activeShaderIndex].activate();
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

        Model m_model;
        // std::map<SHADERS, Shader> m_shaders;        
        std::vector<Shader> m_shaders;
        unsigned int m_activeShaderIndex;

        GLFWwindow * m_window;
        int fbw, fbh;
};

#endif