/*

this is a header for the SDL fonctions 

*/

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <SDL2/SDL.h>

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);

void draw_filled_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height);

void dispMatrix(Matrix* matrix, SDL_Renderer* renderer, bool editing);

void initSDL(SDL_Window** window, SDL_Renderer** renderer);