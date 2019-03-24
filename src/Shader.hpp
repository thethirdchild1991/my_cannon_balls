#ifndef SHADER_HPP
#define SHADER_HPP

#include "common.hpp"

class Shader{
    public:    
        Shader(){};
        Shader( fs::path& shader_src_path ){           
        };
        ~Shader(){};

        void loadShaderSrc( const fs::path& shader_src_path, std::string& vertexCode){
            std::fstream shaderFile;
            shaderFile.open(shader_src_path);

            std::stringstream shaderStream;            
            shaderStream << shaderFile.rdbuf();            
            shaderFile.close();
                        
            vertexCode = shaderStream.str();
        };
        void compileShader( const std::string& shaderCode, unsigned int& vertex) {
            vertex = glCreateShader(GL_VERTEX_SHADER);
            const char* cShaderCode = shaderCode.c_str();
            glShaderSource(vertex, 1, &cShaderCode, NULL);
            glCompileShader(vertex);
        };
        void makeShaderProgram( unsigned int& ID, const unsigned int& shader ){
            ID = glCreateProgram();
            glAttachShader(ID, shader);
            glLinkProgram(ID);
        };
        void cleanup( unsigned int& shader){
            glDeleteShader(shader);
        };
    private:
        int m_ID;
        fs::path m_shader_src_path;

};


#endif 