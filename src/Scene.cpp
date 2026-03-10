#include "espeon/Scene.hpp"

#include "espeon/backend/BackendRenderer.hpp"

namespace espeon {
    bool Scene::setup(SDL_Renderer* renderer) {
        this->renderer = renderer;
        BackendRenderer::get()->setup(renderer);

        return this->init();
    }

    void Scene::addElement(UIBase* element) {
        this->elements.push_back(std::unique_ptr<UIBase>(element));
    }

    void Scene::drawAllElements() {
        for (auto& element : elements) {
            element->draw();
        }
        SDL_RenderPresent(this->renderer);
        SDL_RenderClear(this->renderer);
    }

    void Scene::detectOnClick(SDL_FPoint click) {
        for (auto& element : this->elements) {
            if (element->passthrough) {
                element->detectOnClick(click);
            }

            if (SDL_PointInRectFloat(&click, &element->rect.rect)) {
                element->runOnClick();
            }
        }
    }

    void Scene::detectOnHover(SDL_FPoint coords) {
        bool wasHovering = false;
        if (!this->elements.empty()) {
            for (auto& element : this->elements) {
                if (element->passthrough) {
                    element->detectOnHover(coords);
                }

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

    void Scene::detectOnDrag() {
        for (auto& element : this->elements) {
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            SDL_FPoint mouseRect = {mouseX, mouseY};

            if (element->passthrough) {
                element->detectOnDrag(mouseRect);
            } else {
                if (SDL_PointInRectFloat(&mouseRect, &element->rect.rect)) {
                    element->runOnDrag();
                }
            }
        }
    }
}