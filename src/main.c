#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "engine.h"


struct node {
    int waitState;
    int acc;
    int sec;
    int pc;
    char * memPool[12][3];
}
node0, node1, node2, node3, node4, node5, node6, node7, node8, node9, node10, node11;

char* savePath;
int nth, j, x;

int Z  = -1; int Y = -1; int X = -1;

void tokenize(char * instruction) {
    struct node nodeSet[12] = {
        node0,
        node1,
        node2,
        node3,
        node4,
        node5,
        node6,
        node7,
        node8,
        node9,
        node10,
        node11
    };
    char * zDelim[60];
    char * xDelim[60];
    int a = 0, b = 0;
    zDelim[a] = strtok(instruction, "\n");
    while (zDelim[a] != NULL) {
        if (strcmp(zDelim[a], "@") == 0) {
            Z++;
            Y = -1;
        } else {
            Y++;
            X = -1;
            xDelim[b] = strtok(zDelim[a], " ");
            while (xDelim[b] != NULL) {
                if (X == 3) {
                    X = -1;
                } else {
                    X++;
                    nodeSet[Z].memPool[Y][X] = xDelim[b];
                    printf("%u:%u:%u : %s\n", Z, Y, X, nodeSet[Z].memPool[Y][X]);
                    xDelim[b] = strtok(NULL, " ");
                }
            }
        }
        zDelim[++a] = strtok(NULL, "\n");
    }
}

void clean(char * stream, int lineCount) {
    for (nth = 0; stream[nth] == ' ' || stream[nth] == '\t'; nth++);
    for (j = 0; stream[nth]; nth++) {
        stream[j++] = stream[nth];
    }
    stream[j] = '\0';
    for (nth = 0; stream[nth] != '\0'; nth++) {
        if (stream[nth] != ' ' && stream[nth] != '\t')
            j = nth;
    }
    stream[j + 1] = '\0';
    char * instruction[lineCount];
    instruction[x] = stream;

    tokenize(instruction[x]);
    x++;

}

int fetch() {

    int lineCount;
    FILE * saveFile = fopen(savePath, "r");
    if (saveFile == NULL) {
        perror("Savefile missing!"); //sdl needs to handle this.
        return 1;
    }
    char lineBuffer[128];
    while (fgets(lineBuffer, sizeof(lineBuffer), saveFile) != NULL) {
        lineCount++;
        clean(lineBuffer, lineCount);
    }
}

int startAsm() {
    fetch();

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
    SDL_Window * window = SDL_CreateWindow("Sandbox", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    

    SDL_Texture * Splash = loadTexture("assets/splash.bmp", renderer);
    SDL_Texture * tnode1 = loadTexture("assets/node1.bmp", renderer);
    SDL_Texture * tnode2 = loadTexture("assets/node2.bmp", renderer);
    SDL_Texture * tnode3 = loadTexture("assets/node3.bmp", renderer);
    SDL_Texture * tnode4 = loadTexture("assets/node4.bmp", renderer);
    SDL_Texture * tnode5 = loadTexture("assets/node1.bmp", renderer);
    SDL_Texture * tnode6 = loadTexture("assets/node2.bmp", renderer);
    SDL_Texture * tnode7 = loadTexture("assets/node3.bmp", renderer);
    SDL_Texture * tnode8 = loadTexture("assets/node4.bmp", renderer);
    SDL_Texture * tnode9 = loadTexture("assets/node1.bmp", renderer);
    SDL_Texture * tnode10 = loadTexture("assets/node2.bmp", renderer);
    SDL_Texture * tnode11 = loadTexture("assets/node3.bmp", renderer);
    SDL_Texture * tnode12 = loadTexture("assets/node4.bmp", renderer);
    SDL_Texture * background = loadTexture("assets/black.bmp", renderer);
    SDL_Texture * menu = loadTexture("assets/menu.bmp", renderer);
    
    SDL_Texture * asmSheet = loadTexture("assets/asmSheet.bmp", renderer);
    SDL_Texture * startSheet = loadTexture("assets/startSheet.bmp", renderer);
    SDL_Texture * stopSheet = loadTexture("assets/stopSheet.bmp", renderer);
    SDL_Texture * stepSheet = loadTexture("assets/stepSheet.bmp", renderer);
    SDL_Texture * memSheet = loadTexture("assets/memSheet.bmp", renderer);
    SDL_Texture * quitSheet = loadTexture("assets/quitSheet.bmp", renderer);
    SDL_Texture * loadSheet = loadTexture("assets/loadSheet.bmp", renderer);
    SDL_Color color = {
        255,
        255,
        255,
        255
    };

    SDL_Texture * fonTest = renderText("MOV ACC LEFT", "assets/res/Minecraftia-Regular.ttf", color, 14, renderer);
    SDL_Texture * fonTest1 = renderText("MOV RIGHT DOWN", "assets/res/Minecraftia-Regular.ttf", color, 14, renderer);
    SDL_Texture * fonTest2 = renderText("LOOP:", "assets/res/Minecraftia-Regular.ttf", color, 14, renderer);
    SDL_Texture * fonTest3 = renderText("JMP LOOP", "assets/res/Minecraftia-Regular.ttf", color, 14, renderer);

    SDL_Rect asmClips[3];
    SDL_Rect startClips[3];
    SDL_Rect stopClips[3];
    SDL_Rect stepClips[3];
    SDL_Rect memClips[3];
    SDL_Rect loadClips[3];
    SDL_Rect quitClips[3];
    
    loadClips[0].x = 0;
    loadClips[0].y = 0;
    loadClips[0].h = 200;
    loadClips[0].w = 600;

    loadClips[1].x = 600;
    loadClips[1].y = 0;
    loadClips[1].h = 200;
    loadClips[1].w = 600;

    loadClips[2].x = 1200;
    loadClips[2].y = 0;
    loadClips[2].h = 200;
    loadClips[2].w = 600;

    quitClips[0].x = 0;
    quitClips[0].y = 0;
    quitClips[0].h = 200;
    quitClips[0].w = 600;

    quitClips[1].x = 600;
    quitClips[1].y = 0;
    quitClips[1].h = 200;
    quitClips[1].w = 600;

    quitClips[2].x = 1200;
    quitClips[2].y = 0;
    quitClips[2].h = 200;
    quitClips[2].w = 600;

    asmClips[0].x = 0;
    asmClips[0].y = 0;
    asmClips[0].h = 200;
    asmClips[0].w = 200;

    asmClips[1].x = 200;
    asmClips[1].y = 0;
    asmClips[1].h = 200;
    asmClips[1].w = 200;

    asmClips[2].x = 400;
    asmClips[2].y = 0;
    asmClips[2].h = 200;
    asmClips[2].w = 200;

    startClips[0].x = 0;
    startClips[0].y = 0;
    startClips[0].h = 200;
    startClips[0].w = 200;

    startClips[1].x = 200;
    startClips[1].y = 0;
    startClips[1].h = 200;
    startClips[1].w = 200;

    startClips[2].x = 400;
    startClips[2].y = 0;
    startClips[2].h = 200;
    startClips[2].w = 200;

    stopClips[0].x = 0;
    stopClips[0].y = 0;
    stopClips[0].h = 200;
    stopClips[0].w = 200;

    stopClips[1].x = 200;
    stopClips[1].y = 0;
    stopClips[1].h = 200;
    stopClips[1].w = 200;

    stopClips[2].x = 400;
    stopClips[2].y = 0;
    stopClips[2].h = 200;
    stopClips[2].w = 200;

    stepClips[0].x = 0;
    stepClips[0].y = 0;
    stepClips[0].h = 200;
    stepClips[0].w = 200;

    stepClips[1].x = 200;
    stepClips[1].y = 0;
    stepClips[1].h = 200;
    stepClips[1].w = 200;

    stepClips[2].x = 400;
    stepClips[2].y = 0;
    stepClips[2].h = 200;
    stepClips[2].w = 200;

    memClips[0].x = 0;
    memClips[0].y = 0;
    memClips[0].h = 200;
    memClips[0].w = 200;

    memClips[1].x = 200;
    memClips[1].y = 0;
    memClips[1].h = 200;
    memClips[1].w = 200;

    memClips[2].x = 400;
    memClips[2].y = 0;
    memClips[2].h = 200;
    memClips[2].w = 200;

    int xMouse, yMouse;
    SDL_Event menuState;
    SDL_Event buttonPress;
    
    //splashscreen
    renderTexture(Splash, renderer, 0, 0, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    SDL_RenderClear(renderer);

    //main menu for selecting tings
    int mainMenu = 1;
    // test level for development - new level states will be added for levels.
    int testState = 0;

    while(mainMenu ==1) {
        while(SDL_PollEvent(&menuState)) {
            renderTexture(menu, renderer, 0, 0,NULL);
            
            SDL_GetMouseState(&xMouse, &yMouse);
            if (xMouse > 660 && xMouse <= 660+600 && yMouse > 400 && yMouse <= 400+200) {
                if (SDL_GetMouseState(&xMouse, &yMouse)&SDL_BUTTON(1) == 1) {
                    renderTexture(loadSheet, renderer, 660, 400, &loadClips[0]);
                    SDL_RenderClear(renderer);
                    savePath = "save/save.txt";
                    mainMenu = 0;
                } else {
                    renderTexture(loadSheet, renderer, 660, 400, &loadClips[1]);
                }
            } else {
                renderTexture(loadSheet, renderer, 660, 400, &loadClips[2]);
            }
            if (xMouse > 660 && xMouse <= 660+600 && yMouse > 620 && yMouse <= 620+200) {
                if (SDL_GetMouseState(&xMouse, &yMouse)&SDL_BUTTON(1) == 1) {
                    renderTexture(quitSheet, renderer, 660, 620, &quitClips[0]);
                    IMG_Quit();
                    SDL_Quit();
                    return 1;
                } else {
                    renderTexture(quitSheet, renderer, 660, 620, &quitClips[1]);
                }
            } else {
                renderTexture(quitSheet, renderer, 660, 620, &quitClips[2]);
            }
            SDL_RenderPresent(renderer);
        }   
    }
    testState = 1;
    char tempBuffer[100] = " ";
    SDL_RenderClear(renderer);
    SDL_StartTextInput();
    while (testState == 1) {
        
        while(SDL_PollEvent(&buttonPress)){
            
            renderTexture(tnode1,renderer,10,220,NULL);
            renderTexture(tnode5,renderer,10,430,NULL);
            renderTexture(tnode9,renderer,10,640,NULL);
            renderTexture(tnode3,renderer,10,850,NULL);
            renderTexture(textBox(tempBuffer,TTF_OpenFont("assets/res/Minecraftia-Regular.ttf", 14),color,renderer,200),renderer,20,240,NULL);
            
            // get global mouse state for all subroutines to use
            SDL_GetMouseState(&xMouse, &yMouse);
            if (xMouse > 10 && xMouse <= 210 && yMouse > 10 && yMouse <= 210) {
                if (SDL_GetMouseState(&xMouse, &yMouse)&SDL_BUTTON(1) == 1) {
                    renderTexture(asmSheet, renderer, 10, 10, &asmClips[0]);
                    startAsm();
                } else {
                    renderTexture(asmSheet, renderer, 10, 10, &asmClips[1]);
                }
            } else {
                renderTexture(asmSheet, renderer, 10, 10, &asmClips[2]);
            }
            if (xMouse > 210 && xMouse <= 410 && yMouse > 10 && yMouse <= 210 ) {
                if(SDL_GetMouseState(&xMouse, &yMouse)&SDL_BUTTON(1) == 1){
                    renderTexture(startSheet, renderer, 210, 10, &startClips[0]);
                    
                } else {
                    renderTexture(startSheet, renderer, 210, 10, &startClips[1]);
                }
            } else {
                renderTexture(startSheet, renderer, 210, 10, &startClips[2]);
            }
            if (xMouse > 410 && xMouse <= 610 && yMouse > 10 && yMouse <= 210 ) {
                if(SDL_GetMouseState(&xMouse, &yMouse)&SDL_BUTTON(1) == 1){
                    renderTexture(stopSheet, renderer, 410, 10, &stopClips[0]);
                    //stop Func
                } else {
                    renderTexture(stopSheet, renderer, 410, 10, &stopClips[1]);
                }
            } else {
                renderTexture(stopSheet, renderer, 410, 10, &stopClips[2]);
            }
            if (xMouse > 610 && xMouse <= 810 && yMouse > 10 && yMouse <= 210 ) {
                if(SDL_GetMouseState(&xMouse, &yMouse)&SDL_BUTTON(1) == 1) {
                    renderTexture(stepSheet, renderer, 610, 10, &stepClips[0]);
                    //step Func
                } else {
                    renderTexture(stepSheet, renderer, 610, 10, &stepClips[1]);
                }
            } else {
                renderTexture(stepSheet, renderer, 610, 10, &stepClips[2]);
            }
            if (xMouse > 810 && xMouse <= 1010 && yMouse > 10 && yMouse <= 210 ) {
                if(SDL_GetMouseState(&xMouse, &yMouse)&SDL_BUTTON(1) == 1) {
                    renderTexture(memSheet, renderer, 810, 10, &memClips[0]);
                    //memory Func
                } else {
                    renderTexture(memSheet, renderer, 810, 10, &memClips[1]);
                }
            } else {
                renderTexture(memSheet, renderer, 810, 10, &memClips[2]);
            }
            if(buttonPress.type == SDL_TEXTINPUT || buttonPress.type == SDL_KEYDOWN){
                if(buttonPress.type == SDL_KEYDOWN && buttonPress.key.keysym.sym == SDLK_BACKSPACE && strlen(tempBuffer) > 1) {
                    tempBuffer[strlen(tempBuffer)-1] = '\0';
                    renderTexture(textBox(tempBuffer,TTF_OpenFont("assets/res/Minecraftia-Regular.ttf", 14),color,renderer,200),renderer,20,240,NULL);
                } else if(buttonPress.type == SDL_TEXTINPUT){
                    
                    strcat(tempBuffer,buttonPress.text.text);
                    renderTexture(textBox(tempBuffer,TTF_OpenFont("assets/res/Minecraftia-Regular.ttf", 14),color,renderer,200),renderer,20,240,NULL);
                    //printf("%s",tempBuffer);
                   
                } if(buttonPress.key.keysym.sym == SDLK_RETURN) {
                    strcat(tempBuffer,"\n ");
                    renderTexture(textBox(tempBuffer,TTF_OpenFont("assets/res/Minecraftia-Regular.ttf", 14),color,renderer,200),renderer,20,240,NULL);
                }
            }
        }

    //update frame

    SDL_RenderPresent(renderer);
    }
    IMG_Quit();
    SDL_Quit(); 
}