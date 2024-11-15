

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <SDL2/SDL.h>

 // variables for the window

#define HEIGHT 200
#define WIDTH 170
#define GRAIN_SIZE 4 // in pixel
#define REQ_FPS 20


typedef struct Matrix_ {
    int ** matrix;
    int height, width;
} Matrix;

//for matrix init
Matrix* initMatrix(int width, int height);

void freeMatrix(Matrix* matrix); 
void emptyMatrix(Matrix* matrix);



// For SDL

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void draw_filled_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height);
void dispMatrix(Matrix* matrix, SDL_Renderer* renderer, bool editing);
void initSDL(SDL_Window** window, SDL_Renderer** renderer);

#endif