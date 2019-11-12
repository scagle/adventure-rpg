#pragma once

// Forward Declarations
union SDL_Event;

namespace game
{
    class KeyboardHandler
    {
        private:
            bool keys[255] = { 0 };

        public:
            KeyboardHandler();
            int getVerticalDirection();
            int getHorizontalDirection();
            bool isPressed(unsigned char);
            bool isReleased(unsigned char);
            void handleInput(SDL_Event*);
    };
};
