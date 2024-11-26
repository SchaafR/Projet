#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "process.h"

TTF_Font* font = TTF_OpenFont("FreeSans.ttf", 12);

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Noir
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void draw_filled_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_SetRenderDrawColor(renderer, 168, 95, 12, 255); // Marron clair
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

void draw_text(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    // Crée une surface pour le texte
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        SDL_Log("Error creating text surface: %s", TTF_GetError());
        return;
    }

    // Crée une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Error creating texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Détermine la position et la taille du texte
    SDL_Rect dstrect = {x, y, surface->w, surface->h};

    // Copie la texture sur le renderer
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    // Libère les ressources
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void dispMatrix(Matrix* matrix, SDL_Renderer* renderer, bool editing, TTF_Font* font) {
    u_char tone = editing ? 200 : 255;
    SDL_SetRenderDrawColor(renderer, tone, tone, tone, 255); // Fond blanc
    SDL_RenderClear(renderer);

    // Dessine la matrice
    for (int y = 0; y < matrix->height; y++) {
        draw_line(renderer, 0, y * GRAIN_SIZE, matrix->width * GRAIN_SIZE - 1, y * GRAIN_SIZE);
        for (int x = 0; x < matrix->width; x++) {
            if (matrix->matrix[y][x]) {
                draw_filled_rectangle(renderer, x * GRAIN_SIZE, y * GRAIN_SIZE, GRAIN_SIZE, GRAIN_SIZE);
            }
        }
    }

    // Affiche un encart avec du texte dans l'angle droit
    SDL_Color textColor = {0, 0, 0, 255}; // Noir
    draw_text(renderer, font, editing ? "Mode: Editing" : "Mode: Running",
              matrix->width * GRAIN_SIZE - 150, 10, textColor);

    // Met à jour le rendu
    SDL_RenderPresent(renderer);
}

void initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    const int WINDOW_WIDTH = WIDTH * GRAIN_SIZE;
    const int WINDOW_HEIGHT = HEIGHT * GRAIN_SIZE;

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Error initializing SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Création de la fenêtre
    *window = SDL_CreateWindow("Sand Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!*window) {
        SDL_Log("Error creating window: %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Création du renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        SDL_Log("Error creating renderer: %s", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Initialisation SDL_ttf
    if (TTF_Init() == -1) {
        SDL_Log("Error initializing SDL_ttf: %s", TTF_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}