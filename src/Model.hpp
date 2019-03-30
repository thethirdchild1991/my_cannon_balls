#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image_include.h"

const std::size_t FACE_LINE_STD_LENGTH  = 5;

enum OBJ_CMDS_TYPE{
    NONE,
    Vertex,
    VertexTexture,
    VertexNormal,
    Face
};

class Model{
public:    
    Model(){
        inited = false;
    };
    virtual ~Model(){
        std::cout << "model deleted" << std::endl;
    };


    bool addData(OBJ_CMDS_TYPE data_type, std::vector<float>& data){
        if( data_type == OBJ_CMDS_TYPE::Vertex)
            return addVertex(data);
        if( data_type == OBJ_CMDS_TYPE::VertexNormal)
            return addNormal(data);
        if( data_type == OBJ_CMDS_TYPE::VertexTexture)            
            return addVertexTextureCoordinate(data);
        if( data_type == OBJ_CMDS_TYPE::Face)
            return addFace(data);
    }

    void activate(){
        if(inited){
            glBindVertexArray(VAO);
            glBindTexture(GL_TEXTURE_2D, texture);
        }else{
            std::vector<glm::vec3> vertices(m_vertices.begin(), m_vertices.end());
            // auto vertices = m_vertices;
            std::vector<unsigned int> indices(m_indices.begin(), m_indices.end());
            // for(auto &v:indices){
            //     std::cout   << vertices[v].x << " "
            //                 << vertices[v].y << " "
            //                 << vertices[v].z << " "
            //                 << std::endl;
            // }

            //just for debug
            // std::vector<glm::vec3> vertices{
            //     glm::vec3( 1.000000, -1.000000, -1.000000 ),
            //     glm::vec3( -1.000000, 1.000000, 1.000000 ),
            //     glm::vec3( -1.000000, -1.000000, 1.000000)
            // };

            // std::vector<float> vertices = {
            //     0.5f, 0.5f, 0.0f, // top right
            //     0.5f, -0.5f, 0.0f, // bottom right
            //     -0.5f, -0.5f, 0.0f, // bottom left
            //     -0.5f, 0.5f, 0.0f // top left
            // };
            // unsigned int indices[] = { // note that we start from 0!
            //     0, 1, 3, // first triangle
            //     1, 2, 3
            // // second triangle
            // };

            
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // load and generate the texture
            int width, height, nrChannels;
            unsigned char *data = stbi_load("/home/denis/blender_study/cube_texture.jpg", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
            
            // bind Texture
            glBindTexture(GL_TEXTURE_2D, texture);


            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);            
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.front())*vertices.size(), vertices.data(), GL_STATIC_DRAW);
            

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices.front())*indices.size(), indices.data(), GL_STATIC_DRAW);
            // std::cout << vertices.size() << std::endl;
            
            // glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
            // glEnableVertexAttribArray(0);
            
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(vertices.front()), (void*)0);
            glEnableVertexAttribArray(0);
            // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(vertices.front()), (void*)(3*sizeof(vertices.front())));
            // glEnableVertexAttribArray(1);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
            inited = true;
        }

    }
    void deactivate(){
        inited = false;
    }

    void modify(){

    }
    
    void getStatistics ( std::vector<size_t>& result ) { 
        result.emplace_back(verticesCount());
        result.emplace_back(normalsCount());
        result.emplace_back(facesCount());
    }

    const size_t verticesCount() const { return m_vertices.size(); }
    const size_t normalsCount() const { return m_normals.size(); }
    const size_t facesCount() const { return m_faces.size(); }
    const size_t indicesCount(){ return m_indices.size(); }

private:
    bool addFace( std::vector<float>& data ){
        if(data.size() != 3*3)
            return false;
        for(auto it = data.begin(); it < data.end(); it += 9){
            m_faces.emplace_back( *it, *(it+3), *(it + 6));
            m_indices.emplace_back((*(it))-1);
            m_indices.emplace_back((*(it+3))-1);
            m_indices.emplace_back((*(it+6))-1);
        }
        return true;
    }
    bool addNormal( std::vector<float>& data ){
        if(data.size() != 3)
            return false;
        m_normals.emplace_back( data[0], data[1], data[2]);
        return true;
    }
    bool addVertex( std::vector<float>& data ){
        if(data.size() != 3)
            return false;
        m_vertices.emplace_back(glm::vec3( data[0], data[1], data[2] ) );                      
        return true;
    } 
    bool addVertexTextureCoordinate( std::vector<float>& data){
        if( data.size() != 2)
            return false;
        m_verticesTexture.emplace_back(data[0], data[1]);        
        return true;
    }  
    

private:    
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::ivec3> m_faces;        
    std::vector<unsigned int> m_indices;
    std::vector<glm::vec2> m_verticesTexture;
    unsigned int VBO, VAO, EBO;
    unsigned int texture;
    bool inited;

    glm::mat4 m_modify_mat;
    
};

#endif 