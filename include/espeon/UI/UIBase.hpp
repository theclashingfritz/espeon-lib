#pragma once

#include <functional>

#include <SDL3/SDL_rect.h>

namespace espeon {
    class UIBase {
    public:
        virtual ~UIBase() = default;
        virtual void draw() = 0;
        
        std::function<void()> c_onClick;
        SDL_FRect rect;
};
}