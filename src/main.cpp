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
    mvp = camera.getProjection() * camera.getView();
    Shader::mainShader.updateMVP(mvp);

    keyFlight = getKeyCode("F");
    keyForw = getKeyCode("W");
    keyBack = getKeyCode("S");
    keyLeft = getKeyCode("A");
    keyRight = getKeyCode("D");
    keyUp = getKeyCode("Space");
    keyDown = getKeyCode("Left Shift");
    keyEsc = getKeyCode("Escape");
    keyReset = getKeyCode("R");
}

ProjectApp::~ProjectApp() {
}

void ProjectApp::onDraw() {
    renderer.setShader(Shader::mainShader);
    tex.bind(Texture::DiffuseMap);
    norm.bind(Texture::NormalMap);
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
            Shader::mainShader.updateMVP(camera.getProjection() * camera.getView());
        }
    }
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
        Shader::mainShader.updateMVP(camera.getProjection() * camera.getView());
    }
}

void ProjectApp::onMouseMove(int32_t dx, int32_t dy) {
    if (flyMode) {
        camera.rotate((float)dx * MOUSE_SENCE, -(float)dy * MOUSE_SENCE);
        Shader::mainShader.updateMVP(camera.getProjection() * camera.getView());
    }
}

int main() {
    ProjectApp app;
    app.run();

    return 0;
}