#pragma once

#include <SDL3/SDL_rect.h>

namespace espeon {
    class Vector2 {
    public:
        int x, y;
        Vector2(int x, int y) {
            this->x = x;
            this->y = y;
        }
    };
}