# Creating Custom Elements
This page will walkthrough how to make custom elements.  
Every element in espeon inherites from `UIBase`, so your element will need to also.  
You will need a constructor for your element, and you also will need to override the draw function.

```c++
#include <espeon/backend/BackendRenderer.hpp>
#include <espeon/types/Vector2.hpp>
#include <espeon/UI/UIBase.hpp>

class CustomElement : public espeon::UIBase {
public:
    CustomElement(Vector2 pos, Vector2 size, SDL_Color fillColor) : espeon::UIBase(pos, size) {
        this->text = text;
    }

    void draw() override {
        // TODO: Create more functions for rendering instead of raw SDL
        auto renderer = BackendRenderer::get()->getRenderer()
        SDL_SetRenderDrawColor(renderer, this->fillColor.r, this->fillColor.g, this->fillColor.b, this->fillColor.a);
        SDL_RenderFillRect(renderer, &this->rect.rect);
    }

private:
    SDL_Color fillColor;
};
```