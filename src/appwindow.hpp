#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>

class AppWindow {
   private:
    int windowWidth;
    int windowHeight;
    float aspectRatio;
    SDL_Window* window;
    SDL_GLContext context;
    const Uint8* keyboardState;

    void initSDL(const std::string& title);

    AppWindow(const AppWindow&) = delete;
    AppWindow& operator=(const AppWindow&) = delete;

   public:
    AppWindow(const std::string title, int width, int height);
    void run();
    ~AppWindow();

    bool isKeyPressed(int key);
    int getKeyCode(const std::string name);

    virtual void onLoad() {}
    virtual void onUnload() {}
    virtual bool onUpdate(float deltaTime) { return true; }
    virtual void onDraw() {}

    virtual void onMouseMove(int32_t dx, int32_t dy) {}
    virtual void onMouseButtonPressed(uint8_t button) {}
    virtual void onMouseButtonReleased(uint8_t button) {}
    virtual void onMouseScroll(int32_t amount) {}

    virtual void onKeyPressed(int key) {}
    virtual void onKeyReleased(int key) {}
};
