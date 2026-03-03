#pragma once

#include <functional>

#include <SDL3/SDL.h>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/types/Vector2.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Button : public UIBase {
    public:
        Button(Vector2 pos, Vector2 size, SDL_Color fillColor);

        void draw() override;

        void onClick(std::function<void()> callback) {
            this->c_onClick = callback;
        }
    private:
        Vector2 pos;
        Vector2 size;
        SDL_Color fillColor;

        BackendRenderer* backendRenderer;
    };
}