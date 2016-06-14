#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "move.h"
#include "collision.h"
#include "diverses.h"

//define a velocidade de movimento dos invaders
//Set invader movment speed
void set_invaders_speed() {

    switch (invaders.killed) {

    case 10:

        invaders.speed = 2;
        invaders.state_speed = 800;
        break;

    case 20:

        invaders.speed = 4;
        invaders.state_speed = 600;
        break;

    case 30:

        invaders.speed = 8;
        invaders.state_speed = 200;
        break;

    case 40:

        invaders.speed = 16;
        invaders.state_speed = 0;
        break;
    }
}
//Move posições de ambas balas dos inimigos e do jogador na tela
//Move positions of both enemy and player bullets on screen
int move_bullets(struct bullet_t b[], int max, int speed) {

    int i;

    for(i = 0; i < max; i++) {

        if (b[i].alive == 1) {

            b[i].hitbox.y += speed;

            if (b[i].hitbox.y <= 0) {

                b[i].alive = 0;
            }

            if (b[i].hitbox.y + b[i].hitbox.h >= HEIGHT) {

                b[i].alive = 0;
            }
        }
    }

    return 0;
}
//Move os invaders um espaço para baixo assim que eles chegam no limite da tela
//Move invaders down one space once the reach the edge
void move_invaders_down() {

    int g,i,j;

    for (i = 0; i < 5; i++) {

        for (j = 0; j < 10; j++) {

            invaders.enemy[i][j].hitbox.y += 15;
        }
    }
}
//Move os invaders baseado na sua direção atual
//Move invaders based on there current direction
int move_invaders(int speed) {

    set_invaders_speed();

    int i,j;

    switch (invaders.direction) {

    case left:

        for (i = 0; i < 10; i++) {

            for (j = 0; j < 5; j++) {

                if (invaders.enemy[j][i].alive == 1) {

                    if (invaders.enemy[j][i].hitbox.x <= 0) {

                        invaders.direction = right;
                        move_invaders_down();
                        return 0;
                    }

                    if (invaders.state_time + invaders.state_speed < SDL_GetTicks()) {

                        invaders.state_time = SDL_GetTicks();

                        if (invaders.state == 1) {

                            invaders.state = 0;

                        } else {

                            invaders.state = 1;
                        }
                    }
                    //altera a velocidade em numero de pixels dos invaders
                    //move invader speed number of pixels
                    invaders.enemy[j][i].hitbox.x -= invaders.speed;
                }
            }
        }

        break;

    case right:

        for (i = 9; i >= 0; i--) {

            for (j = 0; j < 5; j++) {

                if (invaders.enemy[j][i].alive == 1) {

                    if (invaders.enemy[j][i].hitbox.x + E_WIDTH >= WIDTH) {

                        invaders.direction = left;
                        move_invaders_down();
                        return 0;
                    }

                    if (invaders.state_time + invaders.state_speed < SDL_GetTicks()) {

                        invaders.state_time = SDL_GetTicks();

                        if (invaders.state == 1) {

                            invaders.state = 0;

                        } else {

                            invaders.state = 1;
                        }
                    }

                    invaders.enemy[j][i].hitbox.x += invaders.speed;
                }
            }
        }

        break;

    default:
        break;

    }

    return 0;
}
//Move o jogador para a direita ou para a esquerda
//Move player left or right
void move_player(enum direction_t direction) {

    if (direction == left) {

        if (player.hitbox.x > 0) {

            player.hitbox.x -= 10;
        }

    } else if (direction == right) {

        if (player.hitbox.x + player.hitbox.w < WIDTH) {

            player.hitbox.x += 10;
        }
    }
}
//Move o saucer baseado na posição atual que se ele se encontra
//Move saucer based on there current direction
void move_saucer() {

    if (saucer.alive == 1) {

        if (saucer.direction == left) {

            saucer.hitbox.x -= 5;

            if (saucer.hitbox.x < 0) {

                saucer.alive = 0;
                saucer.hitbox.x = 0;
                saucer.direction = right;
            }
        }

        if (saucer.direction == right) {

            saucer.hitbox.x += 5;

            if (saucer.hitbox.x + saucer.hitbox.w > WIDTH) {

                saucer.alive = 0;
                saucer.hitbox.x = WIDTH - saucer.hitbox.w;
                saucer.direction = left;
            }
        }
    }
}
