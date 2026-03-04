#include "espeon/UI/Label.hpp"

namespace espeon {
    Label::Label(Vector2 pos, Vector2 size, std::string text, TTF_Font* font, SDL_Color color) {
        this->setDefaultCallbacks();

        this->pos = pos;
        this->size = size;
        this->backendRenderer = BackendRenderer::get();

        SDL_FRect rect;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;
        this->rect = rect;

        this->text = text;
        this->font = font;

        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.length(), color);
        this->textTexture = SDL_CreateTextureFromSurface(this->backendRenderer->getRenderer(), surface);
        SDL_DestroySurface(surface);
    }

    void Label::draw() {
        auto renderer = this->backendRenderer->getRenderer();
        SDL_RenderTexture(renderer, this->textTexture, NULL, &this->rect);
    }

    TTF_Font* Label::loadFont(std::string path, int fontSize) {
        TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
        if (font == NULL) {
            return nullptr;
        }

        return font;
    }
}