#include "espeon/UI/Checkbox.hpp"

namespace espeon {
    Checkbox::Checkbox(Vector2 pos, Vector2 size, CheckboxTextures textures, bool checked) : UIBase(pos, size) {
        this->backendRenderer = BackendRenderer::get();
    }
}