#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <SDL3/SDL_rect.h>

#include "espeon/types/EDrawType.hpp"

namespace espeon {
    class UIBase {
    public:
        virtual ~UIBase() = default;
        virtual void draw() {
            this->drawAllElements();
        };

        void addElement(UIBase* element) {
            this->elements.push_back(std::unique_ptr<UIBase>(element));
        }
        void drawAllElements() {
            if (!elements.empty()) {
                for (auto& element : elements) {
                    element->draw();
                }
            }
        }

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

        void detectOnClick(SDL_FPoint click) {
            for (auto& element : this->elements) {
                if (SDL_PointInRectFloat(&click, &element->rect)) {
                    element->runOnClick();
                }
            }
        }

        void detectOnHover(SDL_FPoint coords) {
            if (!this->elements.empty()) {
                for (auto& element : this->elements) {
                    bool isHovering = SDL_PointInRectFloat(&coords, &element->rect);
                    if (isHovering && !wasHovering) {
                        element->runOnHover();
                    }

                    if (!isHovering && wasHovering) {
                        element->runOnHoverEnd();
                    }

                    wasHovering = isHovering;
                }
            }
        }
    
        SDL_FRect rect;
        EDrawType drawType;
        bool passthrough = false;
        std::vector<std::unique_ptr<UIBase>> elements = {};

    private:
        bool wasHovering = false;
        std::function<void()> c_onClick = std::function<void()>();
        std::function<void()> c_onHover = std::function<void()>();
        std::function<void()> c_onHoverEnd = std::function<void()>();
    };
}