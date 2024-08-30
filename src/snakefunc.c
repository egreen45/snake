#include "snake.h"

extern const int SCREEN_WIDTH; 
extern const int SCREEN_HEIGHT; 
 
const int GRID_SIZE = 32; 
int GRID_DIM; 

Snake* head; 
Snake* tail; 
Apple apple = {.x = -1, .y = -1}; 

void initGrid(void) {
  if (GRID_SIZE % 4 != 0) {
    printf("Not a valid GRID_SIZE!\n"); 
    exit(1); 
  }

  if (GRID_DIM % 8 != 0) {
    printf("Not a valid GRID_DIM!\n"); 
    exit(1); 
  }

  GRID_DIM = SCREEN_WIDTH * 3 / 4; 
}

void drawOutline(SDL_Renderer* renderer) {
  int x, y; 

  SDL_Rect rect = {.x = 0, .y = 0, .w = GRID_DIM / GRID_SIZE, .h = GRID_DIM / GRID_SIZE}; 
  SDL_SetRenderDrawColor(renderer, 184, 191, 187, SDL_ALPHA_OPAQUE); 
  
  /*top bar*/
  rect.y = (SCREEN_WIDTH - GRID_DIM) / 2 - (GRID_DIM / GRID_SIZE);  
  for (x = -1; x < GRID_SIZE + 1; x++) {
    rect.x = (GRID_DIM / GRID_SIZE) * x + (SCREEN_WIDTH - GRID_DIM) / 2; 
    SDL_RenderFillRect(renderer, &rect); 
  }
  
  /*bottom bar*/
  rect.y = (SCREEN_WIDTH - GRID_DIM) / 2 + GRID_DIM;  
  for (x = -1; x < GRID_SIZE + 1; x++) {
    rect.x = (GRID_DIM / GRID_SIZE) * x + (SCREEN_WIDTH - GRID_DIM) / 2; 
    SDL_RenderFillRect(renderer, &rect); 
  }
  /*left bar*/
  rect.x = (SCREEN_WIDTH - GRID_DIM) / 2 - (GRID_DIM / GRID_SIZE);  
  for (y = 0; y < GRID_SIZE; y++) {
    rect.y = (GRID_DIM / GRID_SIZE) * y + (SCREEN_WIDTH - GRID_DIM) / 2; 
    SDL_RenderFillRect(renderer, &rect); 
  }
  /*right bar*/
  rect.x = (SCREEN_WIDTH - GRID_DIM) / 2 + GRID_DIM;  
  for (y = 0; y < GRID_SIZE; y++) {
    rect.y = (GRID_DIM / GRID_SIZE) * y + (SCREEN_WIDTH - GRID_DIM) / 2; 
    SDL_RenderFillRect(renderer, &rect); 
  }
 
}
void drawGrid(SDL_Renderer* renderer) { 
  int x, y; 
 
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
  Direction dir[] = {UP, DOWN, LEFT, RIGHT}; 
  Snake* snake = (Snake*)malloc(sizeof(Snake)); 

  snake -> x = ((rand() % GRID_SIZE / 2) + GRID_SIZE / 4) * (GRID_DIM / GRID_SIZE) + (SCREEN_WIDTH - GRID_DIM) / 2;   
  snake -> y = ((rand() % GRID_SIZE / 2) + GRID_SIZE / 4) * (GRID_DIM / GRID_SIZE) + (SCREEN_WIDTH - GRID_DIM) / 2;  
  snake -> next = NULL; 
  snake -> prev = NULL; 
  snake -> dir = dir[rand() % 4];
  
  head = snake; 
  tail = snake;  
}

void drawSnake(SDL_Renderer* renderer) { 
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

void addSnakeSegment(void) {
  Snake* new = (Snake*)malloc(sizeof(Snake)); 
 
  switch(tail -> dir) {
    case UP: 
      new -> x = tail -> x; 
      new -> y = tail -> y + GRID_DIM / GRID_SIZE; 
      break; 
    case DOWN: 
      new -> x = tail -> x; 
      new -> y = tail -> y - GRID_DIM / GRID_SIZE; 
      break; 
    case LEFT: 
      new -> x = tail -> x + GRID_DIM / GRID_SIZE; 
      new -> y = tail -> y; 
      break; 
    case RIGHT: 
      new -> x = tail -> x - GRID_DIM / GRID_SIZE; 
      new -> y = tail -> y; 
      break; 
  }

  new -> next = NULL; 
  new -> prev = tail; 
  new -> dir = tail -> dir; 

  tail -> next = new; 
  
  tail = new; 
}

void freeSnake(void) {
  Snake* curr = head; 
  Snake* temp; 

  while (curr != NULL) {
    temp = curr -> next; 
    free (curr); 
    curr = temp; 
  }
}

void moveSnake(void) {
  Snake* new_head = tail; 
  Snake* new_tail = tail -> prev; 

  switch(head -> dir) {
    case UP: 
      tail -> x = head -> x; 
      tail -> y = head -> y - GRID_DIM / GRID_SIZE; 
      break; 
    case DOWN: 
      tail -> x = head -> x; 
      tail -> y = head -> y + GRID_DIM / GRID_SIZE; 
      break; 
    case LEFT: 
      tail -> x = head -> x - GRID_DIM / GRID_SIZE; 
      tail -> y = head -> y; 
      break; 
    case RIGHT: 
      tail -> x = head -> x + GRID_DIM / GRID_SIZE; 
      tail -> y = head -> y; 
      break; 
  }

  /*new tail setup*/
  new_tail -> next = NULL; 

  /*tail is new head*/
  new_head -> next = head; 
  new_head -> prev = NULL; 
  new_head -> dir = head -> dir;

  /*tail will always be new_tail no matter what*/
  tail = new_tail; 

  /*head setup*/
  head -> prev = new_head; 
  head = new_head; 

  /*check to see if the snake has collided*/
  if (checkHeadCollision(head -> x, head -> y)) {
    SDL_Delay(1000); 
    freeSnake(); 
    initSnake(); 
    initApple(); 
    addSnakeSegment();  
  }  
} 

void drawApple(SDL_Renderer* renderer) { 
  if (checkCollision(apple.x, apple.y)) {
    apple.x = (rand() % GRID_SIZE) * (GRID_DIM / GRID_SIZE) + (SCREEN_WIDTH - GRID_DIM) / 2;   
    apple.y = (rand() % GRID_SIZE) * (GRID_DIM / GRID_SIZE) + (SCREEN_WIDTH - GRID_DIM) / 2;  
  
    while (checkCollision(apple.x, apple.y)) {
      apple.x = (rand() % GRID_SIZE) * (GRID_DIM / GRID_SIZE) + (SCREEN_WIDTH - GRID_DIM) / 2;   
      apple.y = (rand() % GRID_SIZE) * (GRID_DIM / GRID_SIZE) + (SCREEN_WIDTH - GRID_DIM) / 2;  
    }
  }

  SDL_Rect rect = {.w = GRID_DIM / GRID_SIZE, .h = GRID_DIM / GRID_SIZE, .x = apple.x, .y = apple.y}; 
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); 
  SDL_RenderFillRect(renderer, &rect); 
}

bool checkCollision(uint16_t x, uint16_t y) {
  Snake* curr = head; 

  while (curr) {
    if (curr -> x == x && curr -> y == y) return true; 
    curr = curr -> next; 
  }

  return false; 
}

bool checkHeadCollision(uint16_t x, uint16_t y) {
  Snake* curr = head -> next; 

  while (curr != NULL) {
    if (curr -> x == x && curr -> y == y) return true; 
    curr = curr -> next; 
  }
  
  if (x > SCREEN_WIDTH * 7 / 8 - (GRID_DIM / GRID_SIZE) || y > SCREEN_HEIGHT * 7 / 8 - (GRID_DIM / GRID_SIZE) 
      || x < SCREEN_WIDTH / 8 || y < SCREEN_HEIGHT / 8) 
      return true; 
  
  return false; 
}

void detectApple(void) {
  if (apple.x == head -> x && apple.y == head -> y) {
    addSnakeSegment(); 
  }
}

void initApple(void) {
  apple.x = (rand() % GRID_SIZE) * (GRID_DIM / GRID_SIZE) + (SCREEN_WIDTH - GRID_DIM) / 2;   
  apple.y = (rand() % GRID_SIZE) * (GRID_DIM / GRID_SIZE) + (SCREEN_WIDTH - GRID_DIM) / 2;  
}
