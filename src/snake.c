#include "snake.h"

const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 640; 

int main(void){
  SDL_Window* window = NULL; 
  SDL_Renderer* renderer = NULL; 

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError()); 
    goto _return; 
  } 
 
  window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, 
                                          SDL_WINDOWPOS_CENTERED, 
                                          SCREEN_WIDTH, 
                                          SCREEN_HEIGHT, 
                                          0); 

  if (window == NULL) {
    printf("SDL could not create window! SDL_Error: %s\n", SDL_GetError()); 
    goto _return;   
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 

  if (renderer == NULL) {
    printf("SDL could not create renderer! SDL_Error: %s\n", SDL_GetError()); 
    goto _return; 
  }
  
  bool quit = false; 
  while(!quit) {
    SDL_Event event; 

    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT: 
          quit = true; 
          break;   
      }
    }
    SDL_SetRenderDrawColor(renderer, 0x8, 0x8, 0x8, SDL_ALPHA_OPAQUE); 
    SDL_RenderClear(renderer); 
    SDL_RenderPresent(renderer);  
  }
  
_return: 
  if (window != NULL) SDL_DestroyWindow(window); 
  if (renderer != NULL) SDL_DestroyRenderer(renderer); 

  return 0; 
}
