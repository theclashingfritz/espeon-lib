#pragma once

#include <string>
#include <SDL3/SDL.h>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/types/Vector2.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Button : public UIBase {
    public:
        Button(Vector2 pos, Vector2 size, SDL_Color fillColor);
        Button(Vector2 pos, Vector2 size, std::string texturePath);

        void draw() override;

        void onClick(std::function<void()> callback) {
            this->c_onClick = callback;
        }

        void onHover(std::function<void()> callback) {
            this->c_onHover = callback;
        }
    private:
        Vector2 pos;
        Vector2 size;
        BackendRenderer* backendRenderer;

        SDL_Color fillColor;
        
        std::string texturePath;
        SDL_Texture* texture;
    };
}