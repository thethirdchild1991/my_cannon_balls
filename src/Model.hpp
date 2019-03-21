#ifndef MODEL
#define MODEL

#include <vector>
#include <glm/glm.hpp>



class Model{
    Model(){};
    virtual ~Model(){};

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::ivec3> m_faces;        
    
};

#endif 