#pragma once

namespace espeon {
    class EventManager {
    public:
        static EventManager* get() {
            static EventManager instance;
            return &instance;
        }
 
        bool isDragging() {
            return this->dragging;
        }

        void setDragging(bool dragging) {
            this->dragging = dragging;
        }
    private:
        bool dragging = false;
    };
}