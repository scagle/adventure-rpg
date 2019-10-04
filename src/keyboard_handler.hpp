#pragma once

#define PRESSED true
#define RELEASED false

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
