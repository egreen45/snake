#include "snake.h"

#define NUM_REFRESHES 5
#define GRID 0 

const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 640; 

extern Snake* head; 

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
  
  /*seed random number generator for different behavior each run*/
  srand(time(NULL)); 
 
  /*initialize snake*/
  initGrid(); 
  initSnake(); 
  initApple(); 
  addSnakeSegment(); 

  bool quit = false, moved;  
  uint16_t count = 0; 
  while(!quit) {
    SDL_Event event; 

    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT: 
          quit = true; 
          break;   
        case SDL_KEYDOWN: 
          moved = true; 
          switch(event.key.keysym.sym) {
            case SDLK_LEFT:
              if (head -> dir == LEFT) {
                moved = false; 
                break; 
              } 
              if (head -> dir == RIGHT) break; 
              head -> dir = LEFT; 
              break; 
            case SDLK_RIGHT: 
              if (head -> dir == RIGHT) {
                moved = false; 
                break; 
              }
              if (head -> dir == LEFT) break; 
              head -> dir = RIGHT; 
              break; 
            case SDLK_UP: 
              if (head -> dir == UP) {
                moved = false;  
                break; 
              }
              if (head -> dir == DOWN) break; 
              head -> dir = UP; 
              break; 
            case SDLK_DOWN: 
              if (head -> dir == DOWN) {
                moved = false; 
                break; 
              }
              if (head -> dir == UP) break; 
              head -> dir = DOWN; 
              break; 
          }
          if (moved) count = 0; 
      }
    }
    SDL_SetRenderDrawColor(renderer, 0x8, 0x8, 0x8, SDL_ALPHA_OPAQUE); 
    SDL_RenderClear(renderer); 
#if GRID
    drawGrid(renderer); 
#endif
    if (count == 0) {
      moveSnake(); 
      detectApple(); 
    }  
   
    drawSnake(renderer); 
    drawApple(renderer); 
    drawOutline(renderer);  
    SDL_RenderPresent(renderer); 
    count = (count + 1) % NUM_REFRESHES;  

    SDL_Delay(20); 
  }
  
  freeSnake(); 

_return: 
  if (window != NULL) SDL_DestroyWindow(window); 
  if (renderer != NULL) SDL_DestroyRenderer(renderer); 

  return 0; 
}
