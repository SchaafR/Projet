// /*

// this is where the algorithm behind the sand_sim is implemented

// */

#include<stdio.h>
#include<stdlib.h>
#include "window.h"
#include "process.h"
#include <SDL2/SDL.h>


#include <stdio.h>
#include <stdlib.h>


void simulate_sandfall(Matrix *m) {
    for (int i = m->height - 2; i >= 0; i--) { // Parcours de bas en haut
        for (int j = 0; j < m->width; j++) {
            if (m->matrix[i][j] == 1) { // Si c'est une particule de sable
                if (m->matrix[i + 1][j] == 0) {
                    // Le sable tombe directement
                    m->matrix[i + 1][j] = 1;
                    m->matrix[i][j] = 0;
                } else if (j > 0 && m->matrix[i + 1][j - 1] == 0) {
                    // Le sable glisse à gauche
                    m->matrix[i + 1][j - 1] = 1;
                    m->matrix[i][j] = 0;
                } else if (j < m->width - 1 && m->matrix[i + 1][j + 1] == 0) {
                    // Le sable glisse à droite
                    m->matrix[i + 1][j + 1] = 1;
                    m->matrix[i][j] = 0;
                }
                // Sinon, le sable reste en place (accumulation)
            }
        }
    }
}

