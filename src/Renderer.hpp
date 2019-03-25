#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Model.hpp"
#include "Shader.hpp"
#include <map>



class Renderer{
    public:
        Renderer(){};
        Renderer(   fs::path& vert_shader_path,
                    fs::path& frag_shader_path ){
            m_shaders.emplace_back( Shader(vert_shader_path, frag_shader_path) );
            
        }
        Renderer(   Model& model_in, 
                    fs::path& vert_shader_path,
                    fs::path& frag_shader_path ) : m_model(model_in)
        {
            m_shaders.emplace_back( Shader(vert_shader_path, frag_shader_path) );
        }
        ~Renderer(){};

        void render(){
            render(m_model);
        };
        void render(Model& model){};


        bool model(Model& in) { m_model = in; }
        const Model& model() const { return m_model; }
        Model& model() { return m_model; }

        // void setShader( SHADERS shader_type, fs::path& shader_src_path){
            
        // }

    private:
        Model m_model;
        // std::map<SHADERS, Shader> m_shaders;        
        std::vector<Shader> m_shaders;
};

#endif