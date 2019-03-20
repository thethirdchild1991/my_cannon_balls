#ifndef MODELLOADER
#define MODELLOADER

#include <string>
#include "Model.hpp"

class ModelLoader{
    ModelLoader(){};
    ~ModelLoader(){};

    bool load( const std::string& filepath, Model& out ){
        return false;
    };
};

#endif