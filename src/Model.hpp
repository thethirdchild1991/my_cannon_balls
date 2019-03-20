#ifndef MODEL
#define MODEL

#include <vector>
#include <glm/glm.hpp>

class Model{
    Model(){};
    virtual ~Model(){};

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> faces;        
};

#endif 