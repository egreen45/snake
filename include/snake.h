/* Standard C Libraries */ 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Graphics Library */
#include "SDL2/SDL.h"

/* Function Prototypes */
void drawGrid(SDL_Renderer*); 
void drawSnake(SDL_Renderer*);
void initSnake(void); 
