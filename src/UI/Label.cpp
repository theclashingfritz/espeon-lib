#include "espeon/UI/Label.hpp"

namespace espeon {
    Label::Label(Vector2 pos, Vector2 size, std::string text, TTF_Font* font, SDL_Color color) : UIBase(pos, size) {
        this->setDefaultCallbacks();

        this->pos = pos;
        this->size = size;
        this->backendRenderer = BackendRenderer::get();

        SDL_FRect rect;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;
        this->rect = HoverRect(rect);

        this->textEngine = this->backendRenderer->getTextEngine();
        this->font = font;
        this->text = TTF_CreateText(this->textEngine, this->font, text.c_str(), 0);
    }

    void Label::draw() {
        TTF_DrawRendererText(this->text, this->pos.x, this->pos.y);

        UIBase::draw();
    }

    TTF_Font* Label::loadFont(std::string path, int fontSize) {
        TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
        if (font == NULL) {
            return nullptr;
        }

        return font;
    }
}