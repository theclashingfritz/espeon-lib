#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <SDL3/SDL_rect.h>

#include "espeon/types/EDrawType.hpp"
#include "espeon/types/HoverRect.hpp"
#include "espeon/types/Vector2.hpp"

namespace espeon {
    class UIBase {
    public:
        UIBase(Vector2 pos, Vector2 size) {
            this->setDefaultCallbacks();
            this->pos = pos;
            this->size = size;

            SDL_FRect rect;
            rect.x = pos.x;
            rect.y = pos.y;
            rect.w = size.x;
            rect.h = size.y;
            this->rect = HoverRect(rect);
        }

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
            return this->rect.rect;
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
                if (SDL_PointInRectFloat(&click, &element->rect.rect)) {
                    element->runOnClick();
                }
            }
        }

        void detectOnHover(SDL_FPoint coords) {
            if (!this->elements.empty()) {
                for (auto& element : this->elements) {
                    if (element->rect.update(coords)) {
                        if (element->rect.justEntered()) {
                            element->runOnHover();
                        } else {
                            element->runOnHoverEnd();
                        }
                    }
                }
            }
        }

        Vector2 getPos() {
            return this->pos;
        }

        void setPos(Vector2 pos) {
            this->pos = pos;
        }

        Vector2 getSize() {
            return this->size;
        }

        void setSize(Vector2 size) {
            this->size = size;
        }
    
        HoverRect rect;
        EDrawType drawType;
        bool passthrough = false;
        std::vector<std::unique_ptr<UIBase>> elements = {};
        Vector2 pos;
        Vector2 size;

    private:
        bool wasHovering = false;
        std::function<void()> c_onClick = std::function<void()>();
        std::function<void()> c_onHover = std::function<void()>();
        std::function<void()> c_onHoverEnd = std::function<void()>();
    };
}