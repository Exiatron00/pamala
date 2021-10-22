SDL_Texture *node1 = loadTexture("long.bmp",renderer);
    SDL_Texture *background = loadTexture("black.bmp",renderer);
    if (background == NULL || node1 == NULL) {
        SDL_Quit();
        return 1;
    }
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 320, 180);
    renderTexture(node1,renderer,10,10);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(node1);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;