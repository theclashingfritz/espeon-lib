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

        void setLabel(std::string text, TTF_Font* font, SDL_Color color);

        bool loadTexture(std::string texturePath);
        void unloadTexture();

        SDL_Texture* getTexture();
        void setTexture(SDL_Texture* texture);
    private:
        BackendRenderer* backendRenderer;

        SDL_Color fillColor;
        
        std::string texturePath;
        SDL_Texture* texture;
        std::string label;
    };
}