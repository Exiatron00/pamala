#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <SDL2/SDL_image.h>

#include <SDL2/SDL.h>

#include <SDL2/SDL_timer.h>

#include <SDL2/SDL_ttf.h>

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum buttonState {normal = 0, hover = 1, pressed = 2};



