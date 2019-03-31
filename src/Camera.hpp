#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    public:
        // Camera () : m_inited(false) 
        // {};
        Camera( const glm::vec3& cameraPos = {0.0, 0.0, -3.0},
                const glm::vec3& cameraTarget = {0.0, 0.0, 0.0},
                const glm::vec3& up = {0.0, 1.0, 0.0}
        ) : m_cameraPos(cameraPos), 
            m_cameraTarget(cameraTarget), 
            m_up(up),
            m_viewMat(glm::lookAt(cameraPos, cameraTarget, up)),
            m_inited(true) {};
        ~Camera(){};

        void inited(bool value) { m_inited = value; }
        const bool  inited() const { return m_inited; }

        const glm::mat4& viewMat() const { return m_viewMat; }

        void pos(const glm::vec3& val ) { m_cameraPos = glm::vec3(val); }
        void target(const glm::vec3& val ) { m_cameraTarget = glm::vec3(val); }
        void worldUp(const glm::vec3& up ) { m_up = glm::vec3(up); }

        void calcViewMat() { m_viewMat = glm::lookAt(m_cameraPos, m_cameraTarget, m_up); }

        const glm::mat4& setCamera( glm::vec3& pos_val, glm::vec3& target_val, glm::vec3& up ){
            pos(pos_val);
            target(target_val);
            worldUp(up);
            calcViewMat();
            inited(true);
            return m_viewMat;
        }

        void updatePos(const glm::vec3& val){
            pos(val);
            calcViewMat();
        }

        void updateTarget(const glm::vec3& val){
            target(val);
            calcViewMat();
        }

    private:

        glm::vec3 m_cameraPos;
        glm::vec3 m_cameraTarget;
        glm::vec3 m_up;
        glm::mat4 m_viewMat;

        bool m_inited;
};
#endif