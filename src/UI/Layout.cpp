#include "espeon/UI/Layout.hpp"

namespace espeon {
    Layout::Layout(Vector2 pos, Vector2 size, LayoutDirection direction, LayoutAlign align) {
        this->setDefaultCallbacks();
        this->passthrough = true;

        this->pos = pos;
        this->size = size;
        this->backendRenderer = BackendRenderer::get();

        this->direction = direction;
        this->align = align;
    }

    void Layout::updateLayout() {

    }
}