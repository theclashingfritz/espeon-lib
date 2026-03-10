#pragma once

#include <functional>
#include <string>
#include <SDL3/SDL.h>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/UI/Label.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Slider : public UIBase {
    public:
        struct SliderTextures {
            std::string trackTexturePath;
            std::string buttonTexturePath;
        };

        Slider(Vector2 pos, Vector2 size, float minValue, float maxValue, SliderTextures texturesPath, float defaultValue = 0.f);

        void onValueChanged(std::function<void()> callback) {
            this->c_onValueChanged = callback;
        };

        void draw() override;

        void setLabel(std::string text, TTF_Font* font, SDL_Color color);
        void updateLabel(std::string text);
        
        float getValue();
    private:
        BackendRenderer* backendRenderer;

        SDL_FRect trackRect;
        HoverRect buttonRect;
        espeon::Label* label;
        SliderTextures texturesPath;
        float minValue;
        float maxValue;
        float value;
        SDL_Texture* trackTexture;
        SDL_Texture* buttonTexture;



        std::function<void()> c_onValueChanged = std::function<void()>();
    };
}