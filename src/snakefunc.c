#include "snake.h"

extern const int SCREEN_WIDTH; 
extern const int SCREEN_HEIGHT; 
 
const int GRID_SIZE = 20; 

typedef enum {
  UP, 
  DOWN, 
  LEFT, 
  RIGHT
} Direction; 

typedef struct Snake {
  struct Snake* next; 
  struct Snake* prev; 
  uint16_t x, y; 
  Direction dir;   
} Snake;

Snake* head; 
Snake* tail; 

void drawGrid(SDL_Renderer* renderer) { 
  int x, y; 
  int GRID_DIM = SCREEN_WIDTH * 3 / 4;    
 
  SDL_Rect rect = {.x = 0, .y = 0, .w = GRID_DIM / GRID_SIZE, .h = GRID_DIM / GRID_SIZE};  
  SDL_SetRenderDrawColor(renderer, 184, 191, 187, SDL_ALPHA_OPAQUE); 

  for (x = 0; x < GRID_SIZE; x++) {
    for (y = 0; y < GRID_SIZE; y++) {
      rect.x = (GRID_DIM / GRID_SIZE) * x + (SCREEN_WIDTH - GRID_DIM) / 2; 
      rect.y = (GRID_DIM / GRID_SIZE) * y + (SCREEN_HEIGHT - GRID_DIM) / 2; 
      
      SDL_RenderDrawRect(renderer, &rect); 
    }
  }
   
  return; 
}

void initSnake(void) {
  Snake* snake = (Snake*)malloc(sizeof(Snake)); 
  snake -> x = (rand() % SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 4);   
  snake -> y = (rand() % SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 4); 
  snake -> next = NULL; 
  snake -> prev = NULL; 
  snake -> dir = UP;
  
  head = snake; 
  tail = snake;  
}

void drawSnake(SDL_Renderer* renderer) { 
  int GRID_DIM = SCREEN_WIDTH * 3 / 4;    
 
  SDL_SetRenderDrawColor(renderer, 73, 176, 35, SDL_ALPHA_OPAQUE); 
  
  Snake* curr = head;    
  SDL_Rect rect = {.x = 0, .y = 0, .w = GRID_DIM / GRID_SIZE, .h = GRID_DIM / GRID_SIZE};  

  while (curr != NULL) {
    rect.x = curr -> x; 
    rect.y = curr -> y; 
   
    curr = curr -> next; 

    SDL_RenderFillRect(renderer, &rect); 
  } 
}
