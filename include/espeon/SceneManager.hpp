#pragma once

#include <functional>

#include "espeon/backend/EventManager.hpp"
#include "espeon/Scene.hpp"

namespace espeon {
    class SceneManager {
    public:
        static SceneManager* get() {
            static SceneManager instance;
            return &instance;
        }

        template <typename T>
        void loadScene(SDL_Renderer* renderer) {
            loadQueuedScene = [this, renderer]() {
                currentScene = T::create(renderer);
            };
            sceneChanged = true;
        }

        template <typename T>
        T getScene() {
            return static_cast<T>(this->currentScene);
        }

        void unloadScene() {
            if (currentScene != nullptr) {
                delete currentScene;
                currentScene = nullptr;
            }
        }

        void updateScene() {
            if (sceneChanged) {
                this->unloadScene();
                loadQueuedScene();
                sceneChanged = false;
            }

            currentScene->drawAllElements();
        }

        void updateSceneEvents(SDL_Event* event) {
            if (currentScene != nullptr) {
                auto eventManager = EventManager::get();

                if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                    SDL_FPoint click = {event->button.x, event->button.y};
                    eventManager->setDragging(true);
                    currentScene->detectOnClick(click);
                }

                if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
                    eventManager->setDragging(false);
                }

                if (event->type == SDL_EVENT_MOUSE_MOTION && eventManager->getDragging()) {
                    currentScene->detectOnDrag();
                }

                SDL_FPoint mouseCoords;
                SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
                currentScene->detectOnHover(mouseCoords);
            }
        } 

    private:
        bool sceneChanged;
        Scene* currentScene;
        std::function<void()> loadQueuedScene;
    };
}