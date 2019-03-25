#ifndef SHADER_HPP
#define SHADER_HPP

#include "common.hpp"

enum SHADERS{
    Vert,
    Frag        
};
using compiled_shader = unsigned int;
using shader_program = unsigned int;

class Shader{
    public:    
        // Shader(){};
        Shader(){
            m_ok = false;
        };
        Shader( fs::path& vertex_shader_src_path,
                fs::path& fragment_shader_src_path ){   
            
            m_ok = false;        
            
            m_shaders_src_path.emplace(SHADERS::Vert, vertex_shader_src_path);
            m_shaders_src_path.emplace(SHADERS::Frag, fragment_shader_src_path);

            std::string vertexCode, fragmentCode;
            loadShaderSrc(vertex_shader_src_path, vertexCode );
            loadShaderSrc(fragment_shader_src_path, fragmentCode);

            compiled_shader vertexShader, fragmentShader;
            compileShader(vertexCode, vertexShader);
            compileShader(fragmentCode, fragmentShader);

            m_compiled_shaders.emplace_back(vertexShader);
            m_compiled_shaders.emplace_back(fragmentShader);

            makeShaderProgram( m_ID, m_compiled_shaders);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            m_compiled_shaders.clear();

            m_ok = true;
            
        };
        ~Shader(){
            m_shaders_src_path.clear();            
        };

        const bool isOK() const { return (m_ok == true) ? true : false; }
        
    
    private:        
        void loadShaderSrc( const fs::path& shader_src_path, std::string& shaderCode){
            std::fstream shaderFile;
            shaderFile.open(shader_src_path);

            std::stringstream shaderStream;            
            shaderStream << shaderFile.rdbuf();            
            shaderFile.close();
                        
            shaderCode = shaderStream.str();
        };
        void compileShader( const std::string& shaderCode, compiled_shader& shader) {
            shader = glCreateShader(GL_VERTEX_SHADER);
            const char* cShaderCode = shaderCode.c_str();
            glShaderSource(shader, 1, &cShaderCode, NULL);
            glCompileShader(shader);
        };
        void makeShaderProgram( shader_program& ID,   std::vector<compiled_shader>& compiled_shaders ){
            ID = glCreateProgram();
            for( auto &sh : compiled_shaders ){
                glAttachShader(ID, sh);
            }
            glLinkProgram(ID);
        };
    
        shader_program m_ID;
        std::map<SHADERS, fs::path> m_shaders_src_path;
        std::vector<compiled_shader> m_compiled_shaders;
        bool m_ok;

};


#endif 