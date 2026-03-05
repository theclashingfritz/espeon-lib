#pragma once

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/types/Vector2.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Layout : public UIBase {
    public:
        enum LayoutDirection {
            ROW,
            COLUMN
        };

        enum LayoutAlign {
            LEFT,
            RIGHT,
            CENTER
        };

        Layout(Vector2 pos, Vector2 size, LayoutDirection direction, LayoutAlign align, float spacing = 40.f);

        void updateLayout();

    private:
        BackendRenderer* backendRenderer;

        LayoutDirection direction;
        LayoutAlign align;
        float spacing;
    };
}