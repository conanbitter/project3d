#include "app.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main() {
    App& app = App::getInstance();
    app.init("Project 3D", SCREEN_WIDTH, SCREEN_HEIGHT);
    app.run();

    return 0;
}