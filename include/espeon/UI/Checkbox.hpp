#pragma once

#include <string>
#include <functional>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/UI/Label.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Checkbox : public UIBase {
    public:
        struct CheckboxTextures {
            std::string checkboxTexturePath;
            std::string checkTexturePath;
        };

        enum TextAlign {
            TEXT_ALIGN_LEFT,
            TEXT_ALIGN_RIGHT
        };

        Checkbox(Vector2 pos, Vector2 size, CheckboxTextures textures, bool checked = false);

        void draw() override;

        void setLabel(std::string text, TTF_Font* font, SDL_Color color);
        void updateLabel(std::string text) {
            this->label->updateText(text);
        }
    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        BackendRenderer* backendRenderer;

        SDL_Texture* checkboxTexture;
        SDL_Texture* checkTexture;
        bool checked;
        espeon::Label* label;
    };
}