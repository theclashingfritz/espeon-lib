#pragma once

namespace espeon {
    class EventManager {
    public:
        static EventManager* get() {
            static EventManager instance;
            return &instance;
        }
 
        bool getDragging() {
            return this->isDragging;
        }

        void setDragging(bool dragging) {
            this->isDragging = dragging;
        }
    private:
        bool isDragging = false;
    };
}