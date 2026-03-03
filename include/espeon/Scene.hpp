#pragma once

#include <SDL3/SDL.h>

#include "espeon/backend/BackendRenderer.hpp"

namespace espeon {
    template <class CustomScene>
    class Scene {
    public:
        static CustomScene* create(SDL_Renderer* renderer) {
            CustomScene::create();
        }

        bool setup(SDL_Renderer* renderer) {
            this->renderer = renderer;
            BackendRenderer::get()->setup(renderer);

            return this->init();
        }
    private:
        virtual bool init() {
            return false;
        }
        
        SDL_Renderer* renderer;
    };
}