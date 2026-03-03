#pragma once

#include <SDL3/SDL.h>

#include "espeon/types/Vector2.hpp"

namespace espeon {
    class BackendRenderer {
    public:
        static BackendRenderer* get() {
            static BackendRenderer instance;
            return &instance;
        }

        void setup(SDL_Renderer* renderer) {
            this->renderer = renderer;
        }

        SDL_Renderer* getRenderer() {
            return this->renderer;
        }

        SDL_FRect drawPrimitive(Vector2 pos, Vector2 size, SDL_Color outlineColor);
        SDL_FRect drawFilledPrimitive(Vector2 pos, Vector2 size, SDL_Color outlineColor, SDL_Color fillColor);
    
    private:
        SDL_Renderer* renderer;
    };
}