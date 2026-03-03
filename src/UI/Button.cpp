#include "espeon/UI/Button.hpp"

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
    }

    void Button::draw() {
        auto renderer = this->backendRenderer->getRenderer();
        SDL_SetRenderDrawColor(renderer, this->fillColor.r, this->fillColor.g, this->fillColor.b, this->fillColor.a);
        SDL_RenderFillRect(renderer, &this->rect);
    }
}