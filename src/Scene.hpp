#ifndef SCENE_H
#define SCENE_H


#include <GL/glew.h>
#include <iostream>

class Scene
{
private:
    int m_width;
    int m_height;
    bool m_animate;

    GLuint vaoHandle;
    
public:
    Scene() : m_width(640), m_height(480), m_animate(false){}
    ~Scene() {};

    void init(){}//shader compile and etc
    void update(){}//some time delta update
    void render(){
        std::cout << "Scene Render" << std::endl;
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vaoHandle);
        glDrawArrays(GL_TRIANGLES, 0, 3 );
        glBindVertexArray(0);

    }//bind data array and draw
    void resize( int width, int height ) { m_width = width, m_height = height; }

    void animate( bool value ) { m_animate = value; }
    bool animate() { return m_animate; }
};

#endif
