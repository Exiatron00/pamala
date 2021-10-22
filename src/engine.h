#ifndef _engine_
#define _engine_

#include <SDL2/SDL_image.h>

#include <SDL2/SDL.h>

#include <SDL2/SDL_timer.h>

#include <SDL2/SDL_ttf.h>

#include <stdio.h>

#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

void logSDLError(char * msg) {
    printf("error: %s %s", msg, SDL_GetError());
    exit(1);
}

SDL_Texture * renderText(char * message, char * fontfile, SDL_Color color, int fontSize, SDL_Renderer * renderer) {

    TTF_Font * font = TTF_OpenFont(fontfile, fontSize);
    if (font == NULL) {
        logSDLError("TTF_OpenFont");
        return NULL;
    }

    SDL_Surface * surf = TTF_RenderText_Blended(font, message, color);
    if (surf == NULL) {
        TTF_CloseFont(font);
        logSDLError("TTF_RenderText");
        return NULL;
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == NULL) {
        logSDLError("CreteTexture");
    }
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

SDL_Texture * loadTexture(char * file, SDL_Renderer * ren) {
    SDL_Texture * texture = NULL;
    SDL_Surface * loadedImage = SDL_LoadBMP(file);
    if (loadedImage != NULL) {
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == NULL) {
            logSDLError("CreateTextureFromSurface");
        }
    } else {
        logSDLError("LoadBMP");
    }
    return texture;
}

SDL_Texture *textBox(char tempBuffer[], TTF_Font* font, SDL_Color color, SDL_Renderer *renderer, int maxLength){
    int w,h;
    //TTF_SizeText(font, tempBuffer, &w, &h);
    SDL_Surface * Surface = TTF_RenderText_Blended_Wrapped(font, tempBuffer, color, maxLength);
    
    if(Surface == NULL) {
        logSDLError("TextboxCreate");
    } else {
    SDL_Texture * Texture = SDL_CreateTextureFromSurface(renderer, Surface);
    if(Texture == NULL) {
        logSDLError("TextboxCreate");
    } else {
        return Texture;
        }
    }
}
void renderTexture1(SDL_Texture * tex, SDL_Renderer * ren, SDL_Rect dst,
    SDL_Rect * clip) {

    SDL_RenderCopy(ren, tex, clip, & dst);
}

void renderTexture(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, SDL_Rect * clip) {

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != NULL) {
        dst.w = clip -> w;
        dst.h = clip -> h;
    } else {
        SDL_QueryTexture(tex, NULL, NULL, & dst.w, & dst.h);
    
    }
    renderTexture1(tex, ren, dst, clip);
}

#endif // engine defined