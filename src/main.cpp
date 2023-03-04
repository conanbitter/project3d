#include "appwindow.hpp"
#include "mesh.hpp"
#include "shaders.hpp"
#include "textures.hpp"
#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/epsilon.hpp>
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const float MOVE_SPEED = 0.1f;
const float MOUSE_SENCE = 0.004f;

class ProjectApp : public AppWindow {
   private:
    Mesh box;
    Texture tex;
    Texture norm;
    FlyCamera camera;
    glm::mat4x4 mvp;
    glm::mat4x4 model;
    glm::mat3x3 normalMat;
    float lightAngle = 0.0f;
    float lightRadius = 3.93f;

    bool flyMode = false;
    int keyFlight;
    int keyForw;
    int keyBack;
    int keyLeft;
    int keyRight;
    int keyUp;
    int keyDown;
    int keyEsc;
    int keyReset;

   public:
    ProjectApp();
    ~ProjectApp();
    void onDraw();
    void onUpdate(float deltaTime);
    void onKeyPressed(int key);
    void onMouseMove(int32_t dx, int32_t dy);
};

ProjectApp::ProjectApp() : AppWindow("Project 3D", SCREEN_WIDTH, SCREEN_HEIGHT) {
    box = Mesh("..\\..\\assets\\monkey.mesh");
    tex.load("..\\..\\assets\\monkey_diff.jpg");
    norm.load("..\\..\\assets\\monkey_normal.png");

    camera.setFOV(45.0f);
    camera.setAspectRatio(16.0f / 9.0f);
    camera.setPosition(3.5, 2.3, 3.3);
    camera.setRotation(3.9, -0.45);

    keyFlight = getKeyCode("F");
    keyForw = getKeyCode("W");
    keyBack = getKeyCode("S");
    keyLeft = getKeyCode("A");
    keyRight = getKeyCode("D");
    keyUp = getKeyCode("Space");
    keyDown = getKeyCode("Left Shift");
    keyEsc = getKeyCode("Escape");
    keyReset = getKeyCode("R");

    Shader::mainShader.updateVec3("materialColor", glm::vec3(0.62f, 0.66f, 0.85f));
    Shader::mainShader.updateVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    Shader::mainShader.updateVec3("lightPosition", glm::vec3(sin(lightAngle) * lightRadius, 2.7, cos(lightAngle) * lightRadius));
    Shader::mainShader.updateFloat("ambientStregth", 0.15f);
    Shader::mainShader.updateFloat("specularStrength", 0.5f);

    renderer.setClearColor(0, 0, 0);
    model = glm::mat4(1.0f);
    // model = glm::rotate(model, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));  // glm::scale(model, glm::vec3(1.0, 2.0, 0.5));
}

ProjectApp::~ProjectApp() {
}

void ProjectApp::onDraw() {
    renderer.setShader(Shader::mainShader);
    tex.bind(Texture::DiffuseMap);
    norm.bind(Texture::NormalMap);

    normalMat = glm::mat3x3(glm::transpose(glm::inverse(model)));

    Shader::mainShader.updateMVP(camera.getProjection() * camera.getView() * model);
    Shader::mainShader.updateMat4("model", model);
    Shader::mainShader.updateVec3("eyePosition", camera.getPosition());
    Shader::mainShader.updateMat3("normalMat", normalMat);

    renderer.draw(box);
}

void ProjectApp::onUpdate(float deltaTime) {
    bool cameraMoved = false;
    glm::vec2 direction(0.0f, 0.0f);
    float vert = 0.0f;

    if (flyMode) {
        if (isKeyPressed(keyLeft)) {
            direction.x -= 1.0;
            cameraMoved = true;
        }
        if (isKeyPressed(keyRight)) {
            direction.x += 1.0;
            cameraMoved = true;
        }
        if (isKeyPressed(keyForw)) {
            direction.y += 1.0;
            cameraMoved = true;
        }
        if (isKeyPressed(keyBack)) {
            direction.y -= 1.0;
            cameraMoved = true;
        }
        if (isKeyPressed(keyUp)) {
            vert += MOVE_SPEED;
            cameraMoved = true;
        }
        if (isKeyPressed(keyDown)) {
            vert -= MOVE_SPEED;
            cameraMoved = true;
        }

        if (cameraMoved) {
            if (glm::length(direction) >= glm::epsilon<float>()) {
                direction = glm::normalize(direction) * MOVE_SPEED;
            }
            camera.move(direction.y, direction.x, vert);
        }
    }

    lightAngle += 0.01f;
    if (lightAngle > 6.28) {
        lightAngle -= 6.28;
    }
    Shader::mainShader.updateVec3("lightPosition", glm::vec3(sin(lightAngle) * lightRadius, 2.7, cos(lightAngle) * lightRadius));
}

void ProjectApp::onKeyPressed(int key) {
    if (key == keyEsc) {
        requestExit();
        return;
    }
    if (key == keyFlight) {
        flyMode = !flyMode;
        setStickyMouse(flyMode);
        setTitle(flyMode ? "Project 3D [Fly mode]" : "Project 3D");
        return;
    }
    if (key == keyReset) {
        camera.setPosition(3.5, 2.3, 3.3);
        camera.setRotation(3.9, -0.45);
    }
}

void ProjectApp::onMouseMove(int32_t dx, int32_t dy) {
    if (flyMode) {
        camera.rotate((float)dx * MOUSE_SENCE, -(float)dy * MOUSE_SENCE);
    }
}

int main() {
    ProjectApp app;
    app.run();

    return 0;
}