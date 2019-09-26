#pragma once
#include <SDL.h>
#include <string>

const float MAIN_CHARACTER_SPEED = 0.10;
const std::string MAIN_CHARACTER_NAME = "Bob";
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
// Colors
const SDL_Color MENU_BACKGROUND_COLOR      = { 20  , 20  , 50  , 128 };
const SDL_Color MENU_BLUR_BACKGROUND_COLOR = { 50  , 50  , 50  , 128 };
const SDL_Color OPTION_BACKGROUND_COLOR    = { 50  , 50  , 80  , 0   };
const SDL_Color OPTION_FOREGROUND_COLOR    = { 0   , 255 , 255 , 0   };
const SDL_Color WARNING_BACKGROUND_COLOR   = { 50  , 0   , 50  , 0   };


const int DEFAULT_FONT  = 0;
