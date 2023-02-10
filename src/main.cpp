#include "appwindow.hpp"
#include "mesh.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class ProjectApp : public AppWindow {
   private:
    Mesh box;

   public:
    ProjectApp();
    ~ProjectApp();
    void onDraw();
};

ProjectApp::ProjectApp() : AppWindow("Project 3D", SCREEN_WIDTH, SCREEN_HEIGHT) {
    box = Mesh("..\\..\\assets\\box.mesh");
}

ProjectApp::~ProjectApp() {
}

void ProjectApp::onDraw() {
    renderer.draw(box);
}

int main() {
    ProjectApp app;
    app.run();

    return 0;
}