#pragma once

#include <SDL3/SDL.h>

namespace espeon {
    struct HoverRect {
        SDL_FRect rect;
        bool hovered = false;

        HoverRect() = default;
        HoverRect(SDL_FRect rect) : rect(rect) {}

        bool update(SDL_FPoint mouse) {
            bool isHovered = SDL_PointInRectFloat(&mouse, &rect) == true;
            bool changed = isHovered != hovered;
            hovered = isHovered;
            return changed;
        }

        bool justEntered() const { return hovered; }
        bool justLeft() const { return !hovered; }
    };
}