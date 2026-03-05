#include "espeon/UI/Layout.hpp"

namespace espeon {
    Layout::Layout(Vector2 pos, Vector2 size, LayoutDirection direction, LayoutAlign align, float spacing) {
        this->setDefaultCallbacks();
        this->passthrough = true;

        this->pos = pos;
        this->size = size;
        this->backendRenderer = BackendRenderer::get();

        SDL_FRect rect;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = size.x;
        rect.h = size.y;
        this->rect = rect;

        this->direction = direction;
        this->align = align;
        this->spacing = spacing;
    }

    void Layout::updateLayout() {
        switch (this->direction) {
            case ROW: {
                break;
            }
            case COLUMN: {
                switch (this->align) {
                    case LEFT: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = this->rect.x;
                                currentPos.y = (this->rect.h / 2) + 40;
                            } else {
                                currentPos.x = lastPos.x;
                                currentPos.y = lastPos.y + 40;
                            }
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                    case RIGHT: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = this->rect.w + this->rect.x;
                                currentPos.y = (this->rect.h / 2) + 40;
                            } else {
                                currentPos.x = lastPos.x;
                                currentPos.y = lastPos.y + 40;
                            }
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                    case CENTER: {
                        Vector2 lastPos = {0, 0};
                        for (auto& element : elements) {
                            Vector2 currentPos = element->pos;
                            if (lastPos.x == 0 && lastPos.y == 0) {
                                currentPos.x = (this->rect.w / 2) + this->rect.x;
                                currentPos.y = this->rect.h / 2;
                            } else {
                                currentPos.x = lastPos.x;
                                currentPos.y = lastPos.y + 40;
                            }
                            element->setPos(currentPos);
                            lastPos = currentPos;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
}