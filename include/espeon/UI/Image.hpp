#pragma once

#include <string>

#include "espeon/backend/BackendRenderer.hpp"
#include "espeon/UI/UIBase.hpp"

namespace espeon {
    class Image : public UIBase {
    public:
        Image(Vector2 pos, Vector2 size, std::string imagePath);

        void draw() override;

        bool loadTexture(std::string texturePath);
        void unloadTexture();
    
    private:
        using UIBase::runOnClick;
        using UIBase::runOnDrag;
        using UIBase::runOnHover;
        using UIBase::runOnHoverEnd;

        BackendRenderer* backendRenderer;

        SDL_Texture* texture;
    };
}