#pragma once

#include <glm/glm.hpp>

class FlyCamera {
   private:
    glm::mat4x4 projection;
    glm::mat4x4 view;

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    float pitch;
    float yaw;
    float ar;
    float fov;

    static const float pi;

    void updateProj();
    void updateView();
    void updateVectors();

   public:
    FlyCamera();

    glm::mat4x4 getProjection() { return projection; }
    glm::mat4x4 getView() { return view; }

    void setPosition(const glm::vec3 &newPosition);
    void setPosition(float x, float y, float z);
    glm::vec3 getPosition() { return position; }
    void move(float dForw, float dRight, float dUp);

    void setRotation(float hor, float vert);
    void rotate(float dHor, float dVert);

    void setAspectRatio(float newAspectRatio);
    void setFOV(float newFov);
};
