#pragma once

#define PRESSED true
#define RELEASED false


class KeyboardHandler
{
    private:
    bool keys[255] = { 0 };

    public:
    KeyboardHandler();
    int getVertical();
    int getHorizontal();
    bool isPressed(unsigned char);
    bool isReleased(unsigned char);
    void handleEvent(SDL_Event*);
};
