#include "espeon/UI/Slider.hpp"

#include <iostream>

#include <SDL3_image/SDL_image.h>

#include "espeon/backend/EventManager.hpp"

namespace espeon {
    Slider::Slider(Vector2 pos, Vector2 size, float minValue, float maxValue, Slider::SliderTextures texturesPath) : UIBase(pos, size) {
        this->backendRenderer = BackendRenderer::get();

        this->trackRect = this->rect.rect;

        this->minValue = minValue;
        this->maxValue = maxValue;
        this->texturesPath = texturesPath;

        this->trackTexture = IMG_LoadTexture(this->backendRenderer->getRenderer(), texturesPath.trackTexturePath.c_str());
        if (!this->trackTexture) {
            std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
        }

        this->buttonTexture = IMG_LoadTexture(this->backendRenderer->getRenderer(), texturesPath.buttonTexturePath.c_str());
        if (!this->buttonTexture) {
            std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
        }

        this->buttonRect = SDL_FRect {
            static_cast<float>(pos.x),
            static_cast<float>(pos.y),
            static_cast<float>(buttonTexture->w),
            static_cast<float>(size.y)
        };

        this->onClick([=]() mutable {
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            this->buttonRect.rect.x = mouseX;
            
            this->value = SDL_clamp((buttonRect.rect.x - trackRect.x) / trackRect.w, minValue, maxValue);

            this->c_onValueChanged();
        });

        auto eventManager = EventManager::get();
        this->onDrag([=]() {
            if (eventManager->getDragging()) {
                std::cout << "dragging" << std::endl;
            }

            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            this->buttonRect.rect.x = mouseX;
            
            this->value = SDL_clamp((buttonRect.rect.x - trackRect.x) / trackRect.w, minValue, maxValue);

            this->c_onValueChanged();
        });
    }

    void Slider::draw() {
        auto renderer = this->backendRenderer->getRenderer();
        SDL_FPoint center = {this->trackTexture->w / 2.f, this->trackTexture->h / 2.f};

        SDL_RenderTextureRotated(renderer, this->trackTexture, NULL, &this->trackRect, 0.0, &center, SDL_FLIP_NONE);
        SDL_RenderTextureRotated(renderer, this->buttonTexture, NULL, &this->buttonRect.rect, 0.0, &center, SDL_FLIP_NONE);
    };

    void Slider::setLabel(std::string text, TTF_Font* font, SDL_Color color) {

    }

    float Slider::getValue() {
        return this->value;
    }
}