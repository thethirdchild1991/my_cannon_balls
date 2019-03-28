#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <glm/glm.hpp>

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
        }else{
            std::vector<glm::vec3> vertices(m_vertices.begin(), m_vertices.begin()+3);
            
            //just for debug
            // std::vector<glm::vec3> vertices{
            //     glm::vec3( 1.000000, -1.000000, -1.000000 ),
            //     glm::vec3( -1.000000, 1.000000, 1.000000 ),
            //     glm::vec3( -1.000000, -1.000000, 1.000000)
            // };

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices.front()), vertices.data(), GL_STATIC_COPY_ARB );
            

            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            // std::cout << vertices.size() << std::endl;
            
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(vertices.front()), (void*)0);
            glEnableVertexAttribArray(0);
            // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(vertices.front()), (void*)(3*sizeof(vertices.front())));
            // glEnableVertexAttribArray(1);
            inited = true;
        }

    }
    void deactivate(){
        inited = false;
    }

    
    void getStatistics ( std::vector<size_t>& result ) { 
        result.emplace_back(verticesCount());
        result.emplace_back(normalsCount());
        result.emplace_back(facesCount());
    }

    const size_t verticesCount() const { return m_vertices.size(); }
    const size_t normalsCount() const { return m_normals.size(); }
    const size_t facesCount() const { return m_faces.size(); }

private:
    bool addFace( std::vector<float>& data ){
        if(data.size() != 3*3)
            return false;
        for(auto it = data.begin(); it < data.end(); it += 9){
            m_faces.emplace_back( *it, *(it+3), *(it + 6));
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
        m_vertices.emplace_back(glm::vec3( data[0]/2, data[1]/2, 0.0f ) );              
        // m_vertices.push_back(glm::fvec3( float(0.0), float(1.0-0.5), float(-1.0+0.5) ) );
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
    std::vector<glm::vec2> m_verticesTexture;
    unsigned int VBO, VAO, EBO;
    bool inited;
    
};

#endif 