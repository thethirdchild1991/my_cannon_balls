#ifndef SCENE_H
#define SCENE_H

class Scene
{
private:
    int m_width;
    int m_height;
    bool m_animate;
public:
    Scene() : m_width(640), m_height(480), m_animate(false){}
    ~Scene() {};

    void init();
    void update();
    void render();
    void resize( int width, int height ) { m_width = width, m_height = height; }

    void animate( bool value ) { m_animate = value; }
    bool animate() { return m_animate; }
};

#endif
