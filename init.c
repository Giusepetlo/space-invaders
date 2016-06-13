#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "init.h"
#include "diverses.h"




//Inicializa a estrutura de pontuação do jogo(score)

void init_score() {

	score.shots = 0;
	score.points = 0;
	score.level = 1;
}





//Inicializa a posição principal, a direção, a velocidade e a cor dos inimigos.
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


//Initialize the player starting position and dimensions
void init_player() {

	player.hitbox.x = (WIDTH / 2) - (P_WIDTH / 2);
	player.hitbox.y = HEIGHT - (P_HEIGHT + 10);
	player.hitbox.w = P_WIDTH;
	player.hitbox.h = P_HEIGHT;
	player.lives = 3;
}

//Initialize the player bullets dimensions
void init_bullets(struct bullet_t b[], int max) {

	int i;

	for (i = 0; i < max; i++) {
	
		b[i].alive = 0;
		b[i].hitbox.x = 0;
		b[i].hitbox.y = 0;
		b[i].hitbox.w = B_WIDTH;
		b[i].hitbox.h = B_HEIGHT;
	}
}

//Initialize the saucer position and dimensions
void init_saucer() {

	saucer.hitbox.x = 0;	
	saucer.hitbox.y	= 0;
	saucer.hitbox.w	= 30;
	saucer.hitbox.h = 20;
	saucer.alive = 0;
	saucer.direction = right;
}


