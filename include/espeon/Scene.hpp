#pragma once

#include <memory>
#include <vector>

#include <SDL3/SDL.h>

#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Scene {
    public:
        template <class CustomScene>
        static CustomScene* create(SDL_Renderer* renderer) {
            CustomScene::create();
        }

        bool setup(SDL_Renderer* renderer);
        void addElement(UIBase* element);
        void drawAllElements();
        void detectOnClick(SDL_FPoint click);
        void detectOnHover(SDL_FPoint coords);
        
    private:
        virtual bool init() {
            return false;
        }
        
        SDL_Renderer* renderer;
        std::vector<std::unique_ptr<UIBase>> elements = {};
    };
}