 }
 
 void graphicsShutdown(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 	SDL_Quit();
 
 	releaseBitmap(defaultFont);