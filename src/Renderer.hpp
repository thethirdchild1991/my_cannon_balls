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
#include "Camera.hpp"


void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// camera
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}


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
            float deltaTime = 0.0f;                
            float lastFrame = 0.0f; // Time of last frame                



            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(m_window, mouse_callback);
            glfwSetScrollCallback(m_window, scroll_callback);
            

            Singleton<Camera>::instance().setCamera(   {0.0, 0.0, 3.0},
                                            {0.0, 0.0, -1.0},
                                            {0.0, 1.0, 0.0} );

            while( ! glfwWindowShouldClose(m_window)  ) {

                processInput(m_window);                
                
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                auto shader_id = activateShader();
                int i = -1;
                
                
                glm::mat4 projection_mat = glm::mat4(1.0f);
                glm::vec3 cameraPos = Singleton<Camera>::instance().pos();
                glm::vec3 cameraUp = Singleton<Camera>::instance().worldUp();

                float currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                float cameraSpeed = 2.5f * deltaTime;                
                if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
                    cameraPos += cameraSpeed * cameraFront;
                if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
                    cameraPos -= cameraSpeed * cameraFront;
                if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
                    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
                if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
                    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;                


                Singleton<Camera>::instance().updatePosAndFront(cameraPos, cameraFront);

                projection_mat = glm::perspective(glm::radians(fov), float(WIN_WIDTH) / float(WIN_HEIGHT), 0.1f, 100.0f);
                

                for(auto &model : m_models){
                    i++;
                    model.activate();  
                    glm::mat4 model_mat = glm::mat4(1.0f);

                    model_mat = glm::translate(model_mat, glm::vec3(i*1.0f, i*1.0f, i*1.0f ));
                    model_mat = glm::rotate(model_mat, static_cast<float>(glfwGetTime())*i, glm::vec3(1.0f, 1.0f, 1.0f));
                    model_mat = glm::scale(model_mat, glm::vec3( 0.5 ) );

                    unsigned int modelformLoc = glGetUniformLocation( shader_id , "model_mat");
                    glUniformMatrix4fv(modelformLoc, 1, GL_FALSE, glm::value_ptr(model_mat));

                    unsigned int viewformLoc = glGetUniformLocation( shader_id , "view_mat");
                    glUniformMatrix4fv(viewformLoc, 1, GL_FALSE, glm::value_ptr(Singleton<Camera>::instance().viewMat()) );

                    unsigned int projecitonformLoc = glGetUniformLocation( shader_id , "projection_mat");
                    glUniformMatrix4fv(projecitonformLoc, 1, GL_FALSE, glm::value_ptr(projection_mat));
                   
                    
                    glEnable(GL_DEPTH_TEST);
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    glDrawElements(GL_TRIANGLES, model.indicesCount(), GL_UNSIGNED_INT, 0);
                }
                
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

        void processInput(GLFWwindow *window) {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
        }

        std::vector<Model> m_models;
        // Camera m_camera;
        // std::map<SHADERS, Shader> m_shaders;        
        std::vector<Shader> m_shaders;
        unsigned int m_activeShaderIndex;

        GLFWwindow * m_window;
        int fbw, fbh;




};

#endif