#pragma once

#include <functional>

#include <SDL3/SDL_rect.h>

#include "espeon/types/EDrawType.hpp"

namespace espeon {
    class UIBase {
    public:
        virtual ~UIBase() = default;
        virtual void draw() = 0;

        SDL_FRect getRect() {
            return this->rect;
        }
        void setRect(SDL_FRect rect) {
            this->rect = rect;
        }

        void setDefaultCallbacks() {
            this->onClick([]() {
            
            });

            this->onHover([]() {

            });

            this->onHoverEnd([]() {

            });
        }

        void onClick(std::function<void()> callback) {
            this->c_onClick = callback;
        }

        void onHover(std::function<void()> callback) {
            this->c_onHover = callback;
        }

        void onHoverEnd(std::function<void()> callback) {
            this->c_onHoverEnd = callback;
        }

        void runOnClick() {
            this->c_onClick();
        }

        void runOnHover() {
            this->c_onHover();
        }

        void runOnHoverEnd() {
            this->c_onHoverEnd();
        }
    
        SDL_FRect rect;
        EDrawType drawType;

    private:
        std::function<void()> c_onClick = std::function<void()>();
        std::function<void()> c_onHover = std::function<void()>();
        std::function<void()> c_onHoverEnd = std::function<void()>();
    };
}