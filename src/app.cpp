#include "app.hpp"
#include <iostream>

App& App::getInstance() {
    static App theInstance;
    return theInstance;
}

void App::initSDL(const std::string& title) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowWidth,
                              windowHeight,
                              SDL_WINDOW_OPENGL);

    context = SDL_GL_CreateContext(window);

    keyboardState = SDL_GetKeyboardState(nullptr);
}

void App::init(const std::string title, int width, int height) {
    if (isInitComplete) return;

    windowWidth = width;
    windowHeight = height;
    aspectRatio = (float)windowWidth / (float)windowHeight;

    initSDL(title);

    isInitComplete = true;
}

App::~App() {
    if (context) {
        SDL_GL_DeleteContext(context);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

void App::run() {
    SDL_Event event;
    bool working = true;
    while (working) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    working = false;
                    break;
                case SDL_MOUSEMOTION:
                    onMouseMove(event.motion.xrel, event.motion.yrel);
                    break;
                case SDL_KEYDOWN:
                    if (!event.key.repeat) {
                        onKeyPressed(event.key.keysym.scancode);
                    }
                    break;
                case SDL_KEYUP:
                    if (!event.key.repeat) {
                        onKeyReleased(event.key.keysym.scancode);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    onMouseButtonPressed(event.button.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    onMouseButtonReleased(event.button.button);
                    break;
                case SDL_MOUSEWHEEL:
                    onMouseScroll(event.wheel.y);
                    break;
            }
        }

        if (!onUpdate(1.0f)) {
            working = false;
        }

        SDL_GL_SwapWindow(window);
        SDL_Delay(5);
    }
}

bool App::isKeyPressed(int key) {
    return keyboardState[key];
}

int getKeyCode(const std::string name) {
    return SDL_GetKeyFromName(name.c_str());
}