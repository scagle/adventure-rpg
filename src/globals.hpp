#pragma once
#include <SDL.h>
#include <string>

const float MAIN_CHARACTER_SPEED = 0.10;
const std::string MAIN_CHARACTER_NAME = "Bob";
const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 720;
// Colors
const SDL_Color MENU_BACKGROUND_COLOR      = { 20  , 20  , 50  , 255 };
const SDL_Color BLUR_BACKGROUND_COLOR      = { 0  , 0  , 0  , 100 };
const SDL_Color OPTION_BACKGROUND_COLOR    = { 50  , 50  , 80  , 255 };
const SDL_Color OPTION_FOREGROUND_COLOR    = { 255 , 255 , 255 , 255 };
const SDL_Color TEXT_BACKGROUND_COLOR      = { 255 , 255 , 255 , 255 };
const SDL_Color TEXT_FOREGROUND_COLOR      = { 0 , 0 , 0 , 255 };
const SDL_Color BUTTON_BACKGROUND_COLOR    = { 255 , 200 , 200 , 255 };
const SDL_Color BUTTON_FOREGROUND_COLOR    = { 50 , 50 , 50 , 255 };
const SDL_Color CONTAINER_BACKGROUND_COLOR = { 0 , 0 , 0 , 255 };
const SDL_Color CONTAINER_FOREGROUND_COLOR = { 50 , 50 , 50 , 255 };
const SDL_Color WARNING_BACKGROUND_COLOR   = { 50  , 50   , 80  , 255 };
const SDL_Color OPTION_SELECTED_BACKGROUND_COLOR  = { 100  , 100  , 150  , 255 };
const SDL_Color BUTTON_SELECTED_BACKGROUND_COLOR = { 50 , 50 , 200 , 255 };


const int DEFAULT_FONT  = 0;
