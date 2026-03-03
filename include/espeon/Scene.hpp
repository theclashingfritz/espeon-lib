#pragma once

#include <memory>
#include <vector>

#include <SDL3/SDL.h>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    template <class CustomScene>
    class Scene {
    public:
        static CustomScene* create(SDL_Renderer* renderer) {
            CustomScene::create();
        }

        bool setup(SDL_Renderer* renderer) {
            this->renderer = renderer;
            BackendRenderer::get()->setup(renderer);

            return this->init();
        }

        void addElement(UIBase* element) {
            this->elements.push_back(std::unique_ptr<UIBase>(element));
        }

        void drawAllElements() {
            for (auto& element : elements) {
                element->draw();
            }
            SDL_RenderPresent(this->renderer);
        }

        void detectOnClick(SDL_FPoint click) {
            for (auto& element : this->elements) {
                if (SDL_PointInRectFloat(&click, &element->rect)) {
                    element->c_onClick();
                }
            }
        }
        
    private:
        virtual bool init() {
            return false;
        }
        
        SDL_Renderer* renderer;
        std::vector<std::unique_ptr<UIBase>> elements;
    };
}