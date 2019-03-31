#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Singleton.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera : public Singleton<Camera> {
    public:
        // Camera () : m_inited(false) 
        // {};
        // Camera( const glm::vec3& cameraPos = {0.0, 0.0, 3.0},
        //         const glm::vec3& cameraFront = {0.0, 0.0, -1.0},
        //         const glm::vec3& up = {0.0, 1.0, 0.0}
        // ) : m_cameraPos(cameraPos), 
        //     m_cameraFront(cameraFront), 
        //     m_up(up),
        //     m_viewMat(glm::lookAt(cameraPos, cameraPos + cameraFront, up)),
        //     m_inited(true) {};
        // ~Camera(){};

        void inited(bool value) { m_inited = value; }
        const bool  inited() const { return m_inited; }

        const glm::mat4& viewMat() const { return m_viewMat; }

        void pos(const glm::vec3& val ) { m_cameraPos = glm::vec3(val); }
        const glm::vec3&  pos() const { return m_cameraPos; }
        void front(const glm::vec3& val ) { m_cameraFront = glm::vec3(val); }
        void worldUp(const glm::vec3& up ) { m_up = glm::vec3(up); }
        const glm::vec3& worldUp() const { return m_up; }

        void calcViewMat() { m_viewMat = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_up); }

        const glm::mat4& setCamera( const glm::vec3& pos_val, 
                                    const glm::vec3& front_val, 
                                    const glm::vec3& up ){
            pos(pos_val);
            front(front_val);
            worldUp(up);
            calcViewMat();
            inited(true);
            return m_viewMat;
        }

        void updatePos(const glm::vec3& val){
            pos(val);
            calcViewMat();
        }

        void updateFront(const glm::vec3& val){
            front(val);
            calcViewMat();
        }
        void updatePosAndFront( const glm::vec3& valPos, const glm::vec3& valFront ){
            pos(valPos);
            front(valFront);
            calcViewMat();
        }

    private:

        glm::vec3 m_cameraPos;
        glm::vec3 m_cameraFront;
        glm::vec3 m_up;
        glm::mat4 m_viewMat;

        bool m_inited;
};


#endif