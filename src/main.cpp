#include "appwindow.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class ProjectApp : public AppWindow {
   private:
   public:
    ProjectApp();
    ~ProjectApp();
};

ProjectApp::ProjectApp() : AppWindow("Project 3D", SCREEN_WIDTH, SCREEN_HEIGHT) {
}

ProjectApp::~ProjectApp() {
}

int main() {
    ProjectApp app;
    app.run();

    return 0;
}