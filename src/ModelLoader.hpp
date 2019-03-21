#ifndef MODELLOADER
#define MODELLOADER

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "Model.hpp"

enum OBJ_CMDS_KEYS{
    Vertex,
    VertexTexture,
    VertexNormal,
    Face
};

class ModelLoader{
    ModelLoader(){
        m_cmds.emplace(OBJ_CMDS_KEYS::Vertex, "v");
        m_cmds.emplace(OBJ_CMDS_KEYS::VertexTexture, "vt");
        m_cmds.emplace(OBJ_CMDS_KEYS::VertexNormal, "vn");
        m_cmds.emplace(OBJ_CMDS_KEYS::Face, "f");
    };
    ~ModelLoader(){};


    bool load( const std::string& filepath, Model& model ){
        std::ifstream in_file(filepath);
        if(!in_file.is_open())
            return false;
        std::string line_to_parse;
        while( std::getline(in_file, line_to_parse) ) {
            parse_line(line_to_parse);
        } 

        return false;
    };

private:    

    void parse_line(std::string& line_to_parse){
        std::stringstream iss(line_to_parse);
        std::string word;
        iss >> word;
        for( auto &cmd : m_cmds ){
            if(word == cmd){
                
            }
        }
    }

    std::map<int,std::string> m_cmds; 
};

#endif 