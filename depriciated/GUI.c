#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <SDL2/SDL_image.h>

#include <SDL2/SDL.h>

#include <SDL2/SDL_timer.h>

#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

void logSDLError(char * msg) {
    printf("error: %s %s", msg, SDL_GetError());
    exit(1);
}

SDL_Texture * renderText(char* message, char* fontfile,SDL_Color color, int fontSize,SDL_Renderer *renderer) {
    
    TTF_Font *font = TTF_OpenFont(fontfile,fontSize);
    if (font == NULL) {
        logSDLError("TTF_OpenFont");
        return NULL;
    }

    SDL_Surface *surf = TTF_RenderText_Blended(font,message,color);
    if(surf == NULL) {
        TTF_CloseFont(font);
        logSDLError("TTF_RenderText");
        return NULL;
    }
    
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surf);
    if(texture == NULL) {
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

void renderTexture(SDL_Texture * tex, SDL_Renderer * ren, int x, int y) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(tex, NULL, NULL, & dst.w, & dst.h);
    SDL_RenderCopy(ren, tex, NULL, & dst);
}



int SDL_main(int argc, char * argv[]) {
 
    if (TTF_Init() != 0) {
	logSDLError("TTF_Init");
	SDL_Quit();
	return 1;
}

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError("SDL_Init");
    }
    SDL_Window * window = SDL_CreateWindow("Assembler", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        logSDLError("CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        logSDLError("CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture * Splash = loadTexture("assets/splash.bmp",renderer);
    SDL_Texture * asmBttn = loadTexture("assets/asm.bmp", renderer);
    SDL_Texture * memBttn = loadTexture("assets/mem.bmp", renderer);
    SDL_Texture * StartBttn = loadTexture("assets/pixil-frame-0.bmp", renderer);
    SDL_Texture * StopBttn = loadTexture("assets/pixil-frame-3.bmp", renderer);
    SDL_Texture * StepBttn = loadTexture("assets/pixil-frame-6.bmp", renderer);
    SDL_Texture * node1 = loadTexture("assets/node1.bmp", renderer);
    SDL_Texture * node2 = loadTexture("assets/node2.bmp", renderer);
    SDL_Texture * node3 = loadTexture("assets/node3.bmp", renderer);
    SDL_Texture * node4 = loadTexture("assets/node4.bmp", renderer);
    SDL_Texture * node5 = loadTexture("assets/node1.bmp", renderer);
    SDL_Texture * node6 = loadTexture("assets/node2.bmp", renderer);
    SDL_Texture * node7 = loadTexture("assets/node3.bmp", renderer);
    SDL_Texture * node8 = loadTexture("assets/node4.bmp", renderer);
    SDL_Texture * node9 = loadTexture("assets/node1.bmp", renderer);
    SDL_Texture * node10 = loadTexture("assets/node2.bmp", renderer);
    SDL_Texture * node11 = loadTexture("assets/node3.bmp", renderer);
    SDL_Texture * node12 = loadTexture("assets/node4.bmp", renderer);
    SDL_Texture * background = loadTexture("assets/black.bmp", renderer);

    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Texture *fonTest = renderText("MOV ACC LEFT", "assets/res/Minecraftia-Regular.ttf",color, 14, renderer);
    SDL_Texture *fonTest1 = renderText("MOV RIGHT DOWN", "assets/res/Minecraftia-Regular.ttf",color, 14, renderer);
    SDL_Texture *fonTest2 = renderText("LOOP:", "assets/res/Minecraftia-Regular.ttf",color, 14, renderer);
    SDL_Texture *fonTest3 = renderText("JMP LOOP", "assets/res/Minecraftia-Regular.ttf",color, 14, renderer);
    renderTexture(Splash,renderer, 0,0);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

   
    SDL_Event mainHandler;
    int GameState = 1;
    while (GameState != 0) {
        while (SDL_PollEvent(&mainHandler)) {
       
            if (mainHandler.type == SDL_KEYDOWN) {
                GameState = 0;
            }
            if (mainHandler.type == SDL_MOUSEBUTTONDOWN) {
                GameState = 0;
            }
        }
        
        

        renderTexture(background, renderer, 320, 180);
              
        renderTexture(node1, renderer, 10, 250);
        renderTexture(node2, renderer, 277, 250);
        renderTexture(node3, renderer, 544, 250);
        renderTexture(node4, renderer, 811, 250);

        renderTexture(node5, renderer, 10, 500);
        renderTexture(node6, renderer, 277, 500);
        renderTexture(node7, renderer, 544, 500);
        renderTexture(node8, renderer, 811, 500);
        
        renderTexture(node9, renderer, 10, 750);
        renderTexture(node10, renderer, 277, 750);
        renderTexture(node11, renderer, 544, 750);
        renderTexture(node12, renderer, 811, 750);
        
        renderTexture(StartBttn,renderer,10,10);
        renderTexture(StopBttn,renderer,210,10);
        renderTexture(StepBttn,renderer,410,10);
        renderTexture(asmBttn,renderer,610,10);
        renderTexture(memBttn,renderer,810,10);
        
        renderTexture(fonTest2, renderer, 20, 505+5);
        renderTexture(fonTest1, renderer, 20, 525+5);
        renderTexture(fonTest, renderer, 20, 545+5);
        renderTexture(fonTest1, renderer, 20, 565+5);
        renderTexture(fonTest, renderer, 20, 585+5);
        renderTexture(fonTest1, renderer, 20, 605+5);
        renderTexture(fonTest3, renderer, 20, 625+5);

        renderTexture(fonTest2, renderer, 20, 755+5);
        renderTexture(fonTest1, renderer, 20, 775+5);
        renderTexture(fonTest, renderer, 20, 795+5);
        renderTexture(fonTest1, renderer, 20, 815+5);
        renderTexture(fonTest, renderer, 20, 835+5);
        renderTexture(fonTest1, renderer, 20, 855+5);
        renderTexture(fonTest3, renderer, 20, 875+5);
        SDL_RenderPresent(renderer);
    }
    IMG_Quit();
    SDL_Quit();
    return 0;
}