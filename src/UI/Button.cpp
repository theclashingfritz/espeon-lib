#include "espeon/UI/Button.hpp"

#include <iostream>

#include <SDL3_image/SDL_image.h>

#include "espeon/UI/Label.hpp"

namespace espeon {
    Button::Button(Vector2 pos, Vector2 size, SDL_Color fillColor) {
        this->setDefaultCallbacks();
        
        this->pos = pos;
        this->size = size;
        this->fillColor = fillColor;
        this->backendRenderer = BackendRenderer::get();

        SDL_FRect rect;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;
        this->rect = HoverRect(rect);

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
                SDL_RenderFillRect(renderer, &this->rect.rect);
                break;
            }
            case ESPEON_DRAW_TEXTURE: {
                auto renderer = this->backendRenderer->getRenderer();
                SDL_FPoint center = {this->texture->w / 2.f, this->texture->h / 2.f};
                SDL_RenderTextureRotated(renderer, this->texture, NULL, &this->rect.rect, 0.0, &center, SDL_FLIP_NONE);
                break;
            }
        }

        UIBase::draw();
    }

    void Button::setLabel(std::string text, TTF_Font* font, SDL_Color color) {
        auto label = new espeon::Label(
            {this->pos.x + (this->size.x / 2), this->pos.y + (this->size.y / 2)}, 
            {static_cast<int>(this->rect.rect.w), static_cast<int>(this->rect.rect.h)}, 
            text, font, color
        );
        this->addElement(label);
    }

    bool Button::loadTexture(std::string texturePath) {
        this->unloadTexture();

        this->texture = IMG_LoadTexture(this->backendRenderer->getRenderer(), texturePath.c_str());
        if (!this->texture) {
            return false;
        }

        return true;
    }

    void Button::unloadTexture() {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    SDL_Texture* Button::getTexture() {
        return this->texture;
    }

    void Button::setTexture(SDL_Texture* texture) {
        this->texture = texture;
    }
}