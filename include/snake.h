/* Standard C Libraries */ 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Graphics Library */
#include "SDL2/SDL.h"

/* Data Structures */
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

typedef struct { 
  uint16_t x, y; 
} Apple; 

/* Function Prototypes */
void drawGrid(SDL_Renderer*); 
void drawSnake(SDL_Renderer*);
void initSnake(void); 
void addSnakeSegment(void); 
void freeSnake(void); 
void initGrid(void); 
void moveSnake(void); 
void drawApple(SDL_Renderer*); 
bool checkCollision(uint16_t, uint16_t);
bool checkHeadCollision(uint16_t, uint16_t); 
void detectApple(void); 
void initApple(void); 
void drawOutline(SDL_Renderer*);
