/*
this is the main
*/


#include<stdio.h>
#include<stdlib.h>
#define radius 1 // Rayon de la zone affectée
#include <time.h>
#include "window.h"
#include "process.h"
#include <SDL2/SDL.h>


int main(int argc, char** argv) {
    printf("Sand sim just started\n");
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    initSDL(&window, &renderer);

    // init lmatrix
    Matrix* matrix = initMatrix(WIDTH, HEIGHT);

    // main loop
    bool running = true, editing = false;
    while (running) {
    SDL_Event event;
    int state; // type of particule
    int x, y; // mouse coord
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;

                case SDLK_SPACE:
                    editing = !editing;
                    printf("edit mode : %s\n", editing ? "ON" : "OFF");
                    break;

                case SDLK_BACKSPACE:
                    if (editing) {
                        printf("reset Window\n");
                        emptyMatrix(matrix);   
                    }
                    break;

                case SDLK_s:
                    state = 1;
                    break;

                case SDLK_w:
                    state = 2;
                    break;

                case SDLK_u:
                    state = 3;
                    break;
            }
        }
    }

    
    // Botton down check
    Uint32 mouseState = SDL_GetMouseState(&x, &y);
    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) { 
        int centerX = x / GRAIN_SIZE; // Calculate cordonates inside matrice
        int centerY = y / GRAIN_SIZE;

        // draw square surface
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                int newX = centerX + dx;
                int newY = centerY + dy;

                // Check coordonate inside matrix
                if (newX >= 0 && newX < matrix->width && newY >= 0 && newY < matrix->height) {
                    // add grain of sand
                    matrix->matrix[newY][newX] = 1; // activate cells
                }
            }
        }
    }

    // Matrix update
    if (!editing) {
        switch (state){
            case 1:
                simulate_sandfall(matrix);
                break;
            case 2:
                simulate_waterfall(matrix);
                break;
            case 3:
                simulate_wetsandfall(matrix);
                break;
        }
    }

    // Display
    dispMatrix(matrix, renderer, editing);
    SDL_Delay((int)(1000. / (float)REQ_FPS));
}

        // Matrix update
        if(editing == false){ 
           simulate_sandfall(matrix);
           simulate_waterfall(matrix);
           simulate_wetsandfall(matrix);
        
        // display
        
        dispMatrix(matrix, renderer, editing);
        SDL_Delay((int)(1000. / (float)REQ_FPS));
    }

    // clean and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}