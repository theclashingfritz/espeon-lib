# Scene
The base for a UI Screen

### How to Use
```c++
class CustomScene : public espeon::Scene<CustomScene> {
    bool init() override {
        // rendering code here
    }

public:
    static CustomScene* create(SDL_Renderer* renderer) {
        auto* ret = new CustomScene();
        if (!ret->setup(renderer)) {
            return nullptr;
        }
        return ret;
    }
};
```