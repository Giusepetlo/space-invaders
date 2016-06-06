//Inicializa a posição principal, a direção, a velocidade e a cor dos inimigos.
#include "SDL/SDL.h"
#include "init_invaders.h"
#define E_WIDTH 30
#define E_HEIGHT 30

void init_invaders() {

    invaders.direction = right;
    invaders.speed = 1;
    invaders.state = 0;
    invaders.killed = 0;
    invaders.state_speed = 1000;
    invaders.state_time = SDL_GetTicks();

    int i,j;
    int x = 0;
    int y = 30;

    for (i = 0; i < 5; i++) {

        for (j = 0; j < 10; j++) {

            invaders.enemy[i][j].alive = 1;
            invaders.enemy[i][j].hitbox.x = x;
            invaders.enemy[i][j].hitbox.y = y;
            invaders.enemy[i][j].hitbox.w = E_WIDTH;
            invaders.enemy[i][j].hitbox.h = E_HEIGHT;

            x += E_WIDTH + 15; // Tamanho do espaço.

            if (i == 0) {

                invaders.enemy[i][j].colour = purple;
                invaders.enemy[i][j].points = 30;

            } else if (i >= 1 && i < 3) {

                invaders.enemy[i][j].colour = green;
                invaders.enemy[i][j].points = 20;

            } else {

                invaders.enemy[i][j].colour = red;
                invaders.enemy[i][j].points = 10;
            }
        }

        x = 0; //Reinicia a linha.
        y += E_HEIGHT + 15;
    }
}
