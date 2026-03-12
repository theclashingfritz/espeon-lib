#include "espeon/UI/Image.hpp"

#include <iostream>

namespace espeon {
    Image::Image(Vector2 pos, Vector2 size, std::string imagePath) : UIBase(pos, size) {
        this->backendRenderer = BackendRenderer::get();

        this->texture = this->backendRenderer->loadImage(imagePath);
        if (!this->texture) {
            std::cout << "Failed to load texture: " << SDL_GetError() << std::endl;
        }
    }

    void Image::draw() {
        auto center = this->backendRenderer->getCenter(this->texture);
        SDL_RenderTextureRotated(this->backendRenderer->getRenderer(), this->texture, NULL, &this->rect.rect, 0.0, &center, SDL_FLIP_NONE);
    }
}