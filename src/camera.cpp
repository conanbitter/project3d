#include "camera.hpp"
#include <glm/ext.hpp>

const float FlyCamera::pi = glm::pi<float>();

FlyCamera::FlyCamera() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    right = glm::vec3(1.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    pitch = 0;
    yaw = 0;
    ar = 1.0;
    fov = 45;

    updateProj();
    updateView();
}

void FlyCamera::updateProj() {
    projection = glm::perspective(glm::radians(fov), ar, 0.1f, 100.0f);
}
void FlyCamera::updateView() {
    view = glm::lookAt(position, position + forward, up);
}

void FlyCamera::updateVectors() {
    if (pitch >= (pi / 2 - 0.1)) {
        pitch = pi / 2 - 0.1;
    }

    if (pitch <= (-pi / 2 + 0.1)) {
        pitch = -pi / 2 + 0.1;
    }
    forward = glm::normalize(glm::vec3(
        cos(yaw) * cos(pitch),
        sin(pitch),
        sin(yaw) * cos(pitch)));
    right = glm::normalize(glm::cross(forward, up));
}

void FlyCamera::setPosition(const glm::vec3 &newPosition) {
    position = newPosition;
    updateView();
}

void FlyCamera::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
    updateView();
}

void FlyCamera::move(float dForw, float dRight, float dUp) {
    position += forward * dForw + right * dRight + up * dUp;
    updateView();
}

void FlyCamera::setRotation(float hor, float vert) {
    yaw = hor;
    pitch = vert;
    updateVectors();
    updateView();
}

void FlyCamera::rotate(float dHor, float dVert) {
    yaw += dHor;
    pitch += dVert;
    updateVectors();
    updateView();
}

void FlyCamera::setAspectRatio(float newAspectRatio) {
    ar = newAspectRatio;
    updateProj();
}

void FlyCamera::setFOV(float newFov) {
    fov = newFov;
    updateProj();
}