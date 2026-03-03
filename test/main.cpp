#include <iostream>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <espeon/Scene.hpp>
#include <espeon/SceneManager.hpp>
#include <espeon/UI/Button.hpp>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

class CustomScene : public espeon::Scene {
    bool init() override {
        auto button = new espeon::Button(
            {100, 100}, {250, 100}, {0, 0, 255, SDL_ALPHA_OPAQUE}
        );

        button->onClick([]() {
            std::cout << "hello world!" << std::endl;
        });

        this->addElement(button); 

        return true;
    }

public:
    static CustomScene* create(SDL_Renderer* renderer) {
        auto* ret = new CustomScene();
        if (!ret->setup(renderer)) {
            return nullptr;
        }
        return ret;
    }
};

class CustomScene2 : public espeon::Scene {
    bool init() override {
        auto button = new espeon::Button(
            {100, 200}, {250, 100}, {0, 255, 0, SDL_ALPHA_OPAQUE}
        );

        button->onClick([]() {
            std::cout << "hello world 2!" << std::endl;
        });

        this->addElement(button); 

        return true;
    }

public:
    static CustomScene2* create(SDL_Renderer* renderer) {
        auto* ret = new CustomScene2();
        if (!ret->setup(renderer)) {
            return nullptr;
        }
        return ret;
    }
};

espeon::SceneManager* sceneManager = espeon::SceneManager::get();

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("espeon_lib_test", "1.0", "dev.limegradient.espeon_lib_test");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("espeon_test", 1280, 720, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 1280, 720, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

    SDL_RenderClear(renderer);

    sceneManager->loadScene<CustomScene>(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (event->key.key == SDLK_SPACE) {
            sceneManager->loadScene<CustomScene>(renderer);
        }
        if (event->key.key == SDLK_TAB) {
            sceneManager->loadScene<CustomScene2>(renderer);
        }
    }

    sceneManager->updateSceneEvents(event);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    sceneManager->updateScene();
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}