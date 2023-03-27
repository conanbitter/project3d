#pragma once

#include <SDL.h>
#include <string>
#include "renderer.hpp"

class AppWindow {
   private:
    int windowWidth;
    int windowHeight;
    float aspectRatio;
    SDL_Window* window;
    SDL_GLContext context;
    const Uint8* keyboardState;
    bool working;

    void initSDL(const std::string& title);

    AppWindow(const AppWindow&) = delete;
    AppWindow& operator=(const AppWindow&) = delete;

   public:
    Renderer renderer;

    AppWindow(const std::string title, int width, int height);
    void run();
    ~AppWindow();

    bool isKeyPressed(int key);
    int getKeyCode(const std::string name);
    void requestExit() { working = false; }
    void setStickyMouse(bool enabled);
    void setTitle(std::string title);

    virtual void onLoad() {}
    virtual void onUnload() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onDraw() {}

    virtual void onMouseMove(int32_t dx, int32_t dy) {}
    virtual void onMouseButtonPressed(uint8_t button) {}
    virtual void onMouseButtonReleased(uint8_t button) {}
    virtual void onMouseScroll(int32_t amount) {}

    virtual void onKeyPressed(int key) {}
    virtual void onKeyReleased(int key) {}
};
