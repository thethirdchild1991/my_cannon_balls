#ifndef SCENE_H
#define SCENE_H


#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Scene
{
private:
    int m_width;
    int m_height;
    bool m_animate;

    int vertexCount;

    GLuint m_vaoHandle;
    GLuint m_vertShader;
    GLuint m_fragShader;

    


public:
    Scene() : m_width(640), m_height(480), m_animate(false){}
    ~Scene() {};


    GLuint compileVertShader( std::string shaderFilePath = "src/shader/basic.vert" ){
        // Load contents of file
        std::ifstream inFile( shaderFilePath );
        if (!inFile) {
            std::cout << stderr << "Error opening file: shader/basic.vert" << std::endl; 
            exit(1);
        }

        std::stringstream code;
        code << inFile.rdbuf();
        inFile.close();
        std::string codeStr(code.str());

        // Create the shader object
        m_vertShader = glCreateShader( GL_VERTEX_SHADER );
        
        if (0 == m_vertShader) {
            std::cout << stderr << "Error creating vertex shader" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Load the source code into the shader object
        const GLchar* codeArray[] = {codeStr.c_str()};
        glShaderSource(m_vertShader, 1, codeArray, NULL);

        // Compile the shader
        glCompileShader( m_vertShader );

        // Check compilation status
        GLint result;
        glGetShaderiv( m_vertShader, GL_COMPILE_STATUS, &result );
        if( GL_FALSE == result ) {
            fprintf( stderr, "Vertex shader compilation failed!\n" );

            GLint logLen;
            glGetShaderiv( m_vertShader, GL_INFO_LOG_LENGTH, &logLen );

            if (logLen > 0) {
                char * log = (char *)malloc(logLen);

                GLsizei written;
                glGetShaderInfoLog(m_vertShader, logLen, &written, log);

                fprintf(stderr, "Shader log: \n%s", log);

                free(log);
            }
        }
        return m_vertShader;

    }
    GLuint compileFragShader( std::string shaderFilePath = "src/shader/basic.frag" ){
        // Load contents of file into shaderCode here
        std::ifstream fragFile( shaderFilePath );
        if (!fragFile) {
            std::cout <<stderr << "Error opening file: shader/basic.frag" << std::endl;
            exit(1);
        }

        std::stringstream code;
        code << fragFile.rdbuf();
        fragFile.close();
        std::string codeStr(code.str());        

        // Create the shader object
        m_fragShader = glCreateShader( GL_FRAGMENT_SHADER );
        
        if (0 == m_fragShader) {
            fprintf(stderr, "Error creating fragment shader.\n");
            exit(1);
        }

        // Load the source code into the shader object
        const GLchar* codeArray[] = {codeStr.c_str()};
        glShaderSource( m_fragShader, 1, codeArray, NULL );

        // Compile the shader
        glCompileShader( m_fragShader );
        
        GLint result;
        // Check compilation status
        glGetShaderiv( m_fragShader, GL_COMPILE_STATUS, &result );
        if (GL_FALSE == result) {
            fprintf( stderr, "Fragment shader compilation failed!\n" );

            GLint logLen;
            glGetShaderiv( m_fragShader, GL_INFO_LOG_LENGTH, &logLen );

            if (logLen > 0) {
                char * log = (char *)malloc(logLen);

                GLsizei written;
                glGetShaderInfoLog(m_fragShader, logLen, &written, log);

                fprintf(stderr, "Shader log: \n%s", log);

                free(log);
            }
        }

        return m_fragShader;
    }

    void linking( GLuint vertShader, GLuint fragShader ){
        // Create the program object
        GLuint programHandle = glCreateProgram();
        if(0 == programHandle) {
            fprintf(stderr, "Error creating program object.\n");
            exit(1);
        }

        // Bind index 0 to the shader input variable "VertexPosition"
        //glBindAttribLocation(programHandle, 0, "VertexPosition");
        // Bind index 1 to the shader input variable "VertexColor"
        //glBindAttribLocation(programHandle, 1, "VertexColor");

        // Attach the shaders to the program object
        glAttachShader( programHandle, vertShader );
        glAttachShader( programHandle, fragShader );

        // Link the program
        glLinkProgram( programHandle );

        // Check for successful linking
        GLint status;
        glGetProgramiv( programHandle, GL_LINK_STATUS, &status );
        if (GL_FALSE == status) {

            fprintf( stderr, "Failed to link shader program!\n" );

            GLint logLen;
            glGetProgramiv( programHandle, GL_INFO_LOG_LENGTH, &logLen );

            if (logLen > 0) {
                char * log = (char *)malloc(logLen);

                GLsizei written;
                glGetProgramInfoLog(programHandle, logLen, &written, log);

                fprintf(stderr, "Program log: \n%s", log);

                free(log);
            }
        } else {
            glUseProgram( programHandle );
        }

    }


    void init(){
        GLuint fragShader = compileVertShader();
        GLuint vertShader = compileFragShader();

        linking(m_vertShader, m_fragShader);

        float positionData[] = {
                // -0.8f, -0.8f, 0.0f,
                // 0.8f, -0.8f, 0.5f,
                // 0.0f,  0.8f, 0.8f 
                -1, 0, 0,
                0, -1, 0,
                0, 0, 0,

                1, 0, 0,
                0, 1, 0,
                0, 0.5, 0

                };
        vertexCount = sizeof(positionData) / 3;                
        float colorData[] = {
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f };

        // Create and populate the buffer objects
        GLuint vboHandles[2];
        glGenBuffers(2, vboHandles);
        GLuint positionBufferHandle = vboHandles[0];
        GLuint colorBufferHandle = vboHandles[1];

        glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

        // Create and set-up the vertex array object
        glGenVertexArrays( 1, &m_vaoHandle );
        glBindVertexArray(m_vaoHandle);

        glEnableVertexAttribArray(0);  // Vertex position
        glEnableVertexAttribArray(1);  // Vertex color

        glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );

        glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte *)NULL );
        glBindVertexArray(0);        


    }
    void update(){}//some time delta update
    void render(){        
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_vaoHandle);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount );
        glBindVertexArray(0);
    }
    void resize( int width, int height ) { m_width = width, m_height = height; }

    void animate( bool value ) { m_animate = value; }
    bool animate() { return m_animate; }
};

#endif
