/*
this is the main
*/

#include<stdio.h>
#include<stdlib.h>
#include "window.h"
#include "process.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>



int main(int argc, char** argv) {
    printf("Sand sim just started\n");

    TTF_Font* font = TTF_OpenFont("FreeSans.ttf", 12);
    if (!font) {
        SDL_Log("Error loading font: %s", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Window *window;
    SDL_Renderer *renderer;
    initSDL(&window, &renderer);

    // init lmatrix
    Matrix* matrix = initMatrix(WIDTH, HEIGHT);

    // main loop
    bool running = true, editing = false;
    while (running) {
    SDL_Event event;
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
            }
        }
    }

    // Botton down check
    Uint32 mouseState = SDL_GetMouseState(&x, &y);
    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) { 
        matrix->matrix[y / GRAIN_SIZE][x / GRAIN_SIZE] = !matrix->matrix[y / GRAIN_SIZE][x / GRAIN_SIZE];
        
    }

    // Matrix update
    if (!editing) {
        simulate_sandfall(matrix); 
    }

    // Display
    dispMatrix(matrix, renderer, editing, font);
    SDL_Delay((int)(1000. / (float)REQ_FPS));
    // Ajouter un encart avec du texte dans l'angle droit
    SDL_Color textColor = {0, 0, 0, 255}; // Noir
    draw_text(renderer, font, "Mode: Editing", WIDTH * GRAIN_SIZE - 200, 10, textColor);
    

}

        // Matrix update
        if(editing == false){ 
           simulate_sandfall(matrix);
        
        // display
        
        dispMatrix(matrix, renderer, editing);
        SDL_Delay((int)(1000. / (float)REQ_FPS));
    }

    // clean and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    TTF_CloseFont(font);
    SDL_Quit();

    return EXIT_SUCCESS;
}