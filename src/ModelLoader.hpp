#ifndef MODELLOADER_HPP
#define MODELLOADER_HPP

#include <string>
#include "common.hpp"
#include <map>
#include "Model.hpp"



class ModelLoader{

public:    
    ModelLoader(){
        m_cmds.emplace(OBJ_CMDS_TYPE::Vertex, "v");
        m_cmds.emplace(OBJ_CMDS_TYPE::VertexTexture, "vt");
        m_cmds.emplace(OBJ_CMDS_TYPE::VertexNormal, "vn");
        m_cmds.emplace(OBJ_CMDS_TYPE::Face, "f");
    };
    ~ModelLoader(){};


    bool load( const fs::path& filepath, Model& model ){
        std::ifstream in_file(filepath);
        // in_file.open(filepath);
        if(!in_file.is_open()){
            
            return false;
        }
        std::string line_to_parse;
        OBJ_CMDS_TYPE result_type;
        std::vector<float> result_data;

        while( std::getline(in_file, line_to_parse) ) {
            parse_line(line_to_parse, result_type, result_data);
            model.addData(result_type, result_data);
            
        } 

        return true;
    };

private:    

    void parse_line(std::string& line_to_parse, OBJ_CMDS_TYPE& result_type, std::vector<float>& result_data){
        std::stringstream iss(line_to_parse);
        std::string word;
        iss >> word;

        std::vector<std::string> vos;

        result_type = OBJ_CMDS_TYPE::NONE;
        result_data.clear();
        for( auto &cmd : m_cmds ){
            if(word == cmd.second){
                result_type = cmd.first;
                while(iss >> word){
                    vos.emplace_back(word);
                }
            }
        }

        if(result_type == OBJ_CMDS_TYPE::NONE)
            return;

        if( result_type == OBJ_CMDS_TYPE::Face){
            for( auto &s : vos){
                std::size_t string_size = s.size();
                std::stringstream ss_helper;
                float float_helper;


                //first digit
                ss_helper << s.front();
                ss_helper >> float_helper;
                result_data.emplace_back(float_helper);
                //second didgit
                if(string_size == FACE_LINE_STD_LENGTH){
                    ss_helper << s.at(2);
                    ss_helper >> float_helper;                        
                    result_data.emplace_back(float_helper);
                }else{
                    result_data.emplace_back(-1);
                }
                //third digit
                ss_helper << s.back();
                ss_helper >> float_helper;
                result_data.emplace_back(float_helper);
            }
        }else{
            for(auto &s : vos){
                result_data.emplace_back(std::stod(s));
            }
        }
    }

    std::map<OBJ_CMDS_TYPE,std::string> m_cmds; 
};

#endif 