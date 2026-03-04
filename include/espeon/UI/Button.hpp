#pragma once

#include <string>
#include <SDL3/SDL.h>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/types/Vector2.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Button : public UIBase {
    public:
        Button(Vector2 pos, Vector2 size, SDL_Color fillColor);
        Button(Vector2 pos, Vector2 size, std::string texturePath);
        
        void draw() override;

        bool loadTexture(std::string texturePath);
        void unloadTexture();
        
        Vector2 getPos();
        void setPos(Vector2 pos);

        Vector2 getSize();
        void setSize(Vector2 size);

        SDL_Texture* getTexture();
        void setTexture(SDL_Texture* texture);

        void onClick(std::function<void()> callback) {
            this->c_onClick = callback;
        }

        void onHover(std::function<void()> callback) {
            this->c_onHover = callback;
        }

        void onHoverEnd(std::function<void()> callback) {
            this->c_onHoverEnd = callback;
        }
    private:
        Vector2 pos;
        Vector2 size;
        BackendRenderer* backendRenderer;

        SDL_Color fillColor;
        
        std::string texturePath;
        SDL_Texture* texture;
    };
}