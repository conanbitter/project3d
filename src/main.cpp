#include "appwindow.hpp"
#include "mesh.hpp"
#include "shaders.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class ProjectApp : public AppWindow {
   private:
    Mesh box;
    glm::mat4x4 mvp;

   public:
    ProjectApp();
    ~ProjectApp();
    void onDraw();
};

ProjectApp::ProjectApp() : AppWindow("Project 3D", SCREEN_WIDTH, SCREEN_HEIGHT) {
    box = Mesh("..\\..\\assets\\box.mesh");
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 100.f);
    glm::mat4 View = glm::lookAt(glm::vec3(7.3, 4.9, -6.9), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    mvp = Projection * View;
    int mvp_pos = Shader::mainShader.getUniformId("mvp");
    Shader::mainShader.updateUniformMat(mvp_pos, mvp);
}

ProjectApp::~ProjectApp() {
}

void ProjectApp::onDraw() {
    renderer.setShader(Shader::mainShader);
    renderer.draw(box);
}

int main() {
    ProjectApp app;
    app.run();

    return 0;
}