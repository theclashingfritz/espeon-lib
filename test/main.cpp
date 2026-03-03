#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <espeon/Scene.hpp>
#include <espeon/backend/BackendRenderer.hpp>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

class CustomScene : public espeon::Scene<CustomScene> {
    bool init() override {
        espeon::BackendRenderer::get()->drawPrimitive(
            {100, 100}, {250, 100}, {0, 255, 0, SDL_ALPHA_OPAQUE}
        );

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

    CustomScene* scene = CustomScene::create(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{

}