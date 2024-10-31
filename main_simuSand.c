/*
this is the main
*/


#include<stdio.h>
#include<stdlib.h>


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
        // "Quit" event 
        SDL_Event event;
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
                        printf("edit mode : %s\n", editing? "ON": "OFF");
                        break;

                    case SDLK_BACKSPACE:
                        if(editing) {
                            printf("Empt\n");
                            //emptyMatrix(matrix);
                        }
                        break;

                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT && editing) {
                    matrix->matrix[event.button.y/GRAIN_SIZE][event.button.x/GRAIN_SIZE] = !matrix->matrix[event.button.y/GRAIN_SIZE][event.button.x/GRAIN_SIZE];
                } 
            }

        }

        // Matrix update
        if(editing == false) 
            //updateMatrix(matrix);
        
        // display
        // printMatrix(matrix);
        dispMatrix(matrix, renderer, editing);
        SDL_Delay((int)(1000. / (float)REQ_FPS));
    }

    // clean and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}