
#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "diverses.h"


//Determine for game over event
void game_over_ai() {
	
	if (player.lives < 0) {
		
		state = game_over;
	}
}



//Shoot bullet/s from player
void player_shoot() {

	int i;
	
	for (i = 0; i < P_BULLETS; i++) {
				
		if (bullets[i].alive == 0) {
			
			//count number of shots fired
			score.shots++;

			bullets[i].hitbox.x = player.hitbox.x + (P_WIDTH / 2);
			//-5 at the end so the bullets ends closer to the top of the screen due to 30px speed
			bullets[i].hitbox.y = player.hitbox.y - (bullets[i].hitbox.h + 10);
			bullets[i].alive = 1;
			break;
		}
	}
}


//Determine game level
void calculate_level() {

	if (invaders.killed != 0 && invaders.killed % 50 == 0) {
		
		score.level++;
		init_invaders();
		init_bases();
		init_saucer();
		pause_for(500);
	}
}

//Determine when saucer should appear
void saucer_ai() {

	//every 20 shots
	if (score.shots != 0 && score.shots % 20 == 0) {
	
		saucer.alive = 1;
	}
}

//Determine when invaders should shoot
void enemy_ai() {

	int i, j, k;

	for (i = 0; i < 10; i++) {
		
		for (j = 4; j >= 0; j--) {
			
			if (invaders.enemy[j][i].alive == 1) {
				
				//player
				int mid_point = player.hitbox.x + (player.hitbox.w / 2);
				
				//enemy
				int start = invaders.enemy[j][i].hitbox.x;
				int end = invaders.enemy[j][i].hitbox.x + invaders.enemy[j][i].hitbox.w;

				if (mid_point > start && mid_point < end) {

					//fire bullet if available
					for (k = 0; k < E_BULLETS; k++) {
			
						if (e_bullets[k].alive == 0) {
				
							int r = rand() % 30;

							if (r == 1) {
								e_bullets[k].hitbox.x = start + (E_WIDTH / 2) ;
								e_bullets[k].hitbox.y = invaders.enemy[j][i].hitbox.y;
								e_bullets[k].alive = 1;
							}

							break;
						}
					}
				}
				
				//alive enemy found reversing up the enemy grid dont check the rest of the colum
				break;
			}
		}
	}
}

//Determin when to pause game and how long for
void pause_game() {

	if (SDL_GetTicks() > pause_time + pause_len) {
	
		state = game;
	}
}

//Set amount of time to pause game for
void pause_for(unsigned int len) {

	state = pause;
	pause_time = SDL_GetTicks();
	pause_len = len;
}
