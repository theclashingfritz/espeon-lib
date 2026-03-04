#pragma once

#include <string>

#include <SDL3_ttf/SDL_ttf.h>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/types/Vector2.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Label : public UIBase {
    public:
        Label(Vector2 pos, Vector2 size, std::string text, TTF_Font* font, SDL_Color color);

        void draw() override;
        static TTF_Font* loadFont(std::string path, int fontSize);

    private:
        Vector2 pos;
        Vector2 size;
        BackendRenderer* backendRenderer;

        std::string text;
        SDL_Texture* textTexture;
        TTF_Font* font;
    };
}