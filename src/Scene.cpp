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
        SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (auto& element : elements) {
            element->draw();
        }
        SDL_RenderPresent(this->renderer);
        SDL_RenderClear(this->renderer);
    }

    void Scene::detectOnClick(SDL_FPoint click) {
        for (auto& element : this->elements) {
            if (SDL_PointInRectFloat(&click, &element->rect)) {
                element->runOnClick();
            }
        }
    }

    bool wasHovering = false;
    void Scene::detectOnHover(SDL_FPoint coords) {
        if (!this->elements.empty()) {
            for (auto& element : this->elements) {
                bool isHovering = SDL_PointInRectFloat(&coords, &element->rect);
                if (isHovering && !wasHovering) {
                    element->runOnHover();
                }

                if (!isHovering && wasHovering) {
                    element->runOnHoverEnd();
                }

                wasHovering = isHovering;
            }
        }
    }
}