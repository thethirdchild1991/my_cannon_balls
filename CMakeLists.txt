cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
set (target_name my_cannon_balls)
project(${target_name} VERSION 0.1.0)

# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

add_executable(${target_name} 
        src/main.cpp
        src/Scene.cpp        
        src/Scene.hpp
        src/SceneRunner.cpp
        src/SceneRunner.hpp
        )


find_package(GLEW REQUIRED)
if (GLEW_FOUND)    
    message("GLEW found")
    include_directories(GLEW)
    target_link_libraries(${target_name} GLEW)
endif()

find_package( glm CONFIG REQUIRED )
if(glm_FOUND)
    message("GLM found")
    include_directories(glm)
    link_libraries(glm)
endif()

find_package( glfw3 CONFIG REQUIRED )
if(glfw3_FOUND)
    message("GLFW3 found")
    include_directories(glfw3)    
    target_link_libraries(${target_name} glfw)        
endif()    

find_package( OpenGL REQUIRED )
if(OpenGL_FOUND)
    message("OPENGL FOUND")
    include_directories(OpenGL)
    target_link_libraries(${target_name} OpenGL)
endif()
