#include "espeon/UI/Button.hpp"

#include <iostream>

#include <SDL3_image/SDL_image.h>

namespace espeon {
    Button::Button(Vector2 pos, Vector2 size, SDL_Color fillColor) {
       this->pos = pos;
       this->size = size;
       this->fillColor = fillColor;
       this->backendRenderer = BackendRenderer::get();

       SDL_FRect rect;
       rect.x = pos.x;
       rect.y = pos.y;
       rect.w = size.x;
       rect.h = size.y;
       this->rect = rect;

       this->drawType = EDrawType::ESPEON_DRAW_FILLED;
    }

    Button::Button(Vector2 pos, Vector2 size, std::string texturePath) {
        this->pos = pos;
        this->size = size;
        this->texturePath = texturePath;
        this->backendRenderer = BackendRenderer::get();

        this->texture = IMG_LoadTexture(this->backendRenderer->getRenderer(), texturePath.c_str());
        if (!this->texture) {
            std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
        }

        SDL_FRect rect;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;
        this->rect = rect;

        this->drawType = EDrawType::ESPEON_DRAW_TEXTURE;
    }

    void Button::draw() {
        switch (this->drawType) {
            case ESPEON_DRAW_FILLED: {
                auto renderer = this->backendRenderer->getRenderer();
                SDL_SetRenderDrawColor(renderer, this->fillColor.r, this->fillColor.g, this->fillColor.b, this->fillColor.a);
                SDL_RenderFillRect(renderer, &this->rect);
                break;
            }
            case ESPEON_DRAW_TEXTURE: {
                auto renderer = this->backendRenderer->getRenderer();
                SDL_RenderTexture(renderer, this->texture, NULL, &this->rect);
                break;
            }
        }
    }
}