#ifndef MODEL
#define MODEL

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
    Model(){};
    virtual ~Model(){};


    bool addData(OBJ_CMDS_TYPE data_type, std::vector<double>& data){
        if( data_type == OBJ_CMDS_TYPE::Vertex)
            return addVertex(data);
        if( data_type == OBJ_CMDS_TYPE::VertexNormal)
            return addNormal(data);
        if( data_type == OBJ_CMDS_TYPE::Face)
            return addFace(data);
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
    bool addFace( std::vector<double>& data ){
        if(data.size() != 3*3)
            return false;
        for(auto it = data.begin(); it < data.end(); it += 9){
            m_faces.emplace_back( *it, *(it+3), *(it + 6));
        }
        return true;
    }
    bool addNormal( std::vector<double>& data ){
        if(data.size() != 3)
            return false;
        m_normals.emplace_back( data[0], data[1], data[2]);
        return true;
    }
    bool addVertex( std::vector<double>& data ){
        if(data.size() != 3)
            return false;
        m_vertices.emplace_back( data[0], data[1], data[2] );
        return true;
    }   

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::ivec3> m_faces;        
    
};

#endif 