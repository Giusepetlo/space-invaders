//Giusepe Lopes (tessarigiusepe@yahoo.com.br)


//known bugs
//some times the bullet wont go past through a base if it hits on the far left edge. cause unknowen
//its the same bug that i found in my invaders drawing code. using the objects own hitbox as the SDL_Rect
//as the destination rectangle to blit to. using a seperate local rect in the drawing code solves it.
#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "init.h"
#include "move.h"
#include "collision.h"
#include "diverses.h"
#include "load.h"
#include "maxpont.h"

void draw_string(char s[], int x, int y);

int load_image(char filename[], SDL_Surface **surface, enum ck_t colour_key);


//Inicializa as posições iniciais e dimensões das bases.
//Initialize the bases starting position and dimensions.
void init_bases() {

	int i;
	int base_total = BASE_WIDTH * 4; 
	int space_left = WIDTH - base_total;
	int even_space = space_left / 5; // 5 gaps, 5 espaços entre as bases.
	int x = even_space;
	int y = 500;
	
	for (i = 0; i < BASE; i++) {
		
		base[i].hitbox.x = x;
		base[i].hitbox.y = y;
		base[i].hitbox.w = BASE_WIDTH;
		base[i].hitbox.h = BASE_HEIGHT;
		
		x += BASE_WIDTH + even_space; //distance apart, distancia entre uma base e outra.
	}
	
	load_image("base.bmp", &base_img[0], magenta);
	load_image("base.bmp", &base_img[1], magenta);
	load_image("base.bmp", &base_img[2], magenta);
	load_image("base.bmp", &base_img[3], magenta);
}


//Desenha o fundo
//Draw the background
void draw_background () {

	SDL_Rect src; 
	
	src.x = 0;
	src.y = 0;
	src.w = screen->w;
	src.h = screen->h;
	
	SDL_FillRect(screen,&src,0);
}


//Desenha a interface
//Draw the HUD
void draw_hud() {
	
	SDL_Rect r; 
	
	r.x = WIDTH;
	r.y = 0;
	r.w = SCREEN_WIDTH - WIDTH;
	r.h = SCREEN_HEIGHT;
	
	SDL_FillRect(screen, &r, 41);
	
	char score_label[] = "Pontuacao";
	draw_string(score_label, WIDTH, 0);
	
	char score_num[10];
	snprintf(score_num, 10, "%d", score.points);
	draw_string(score_num, WIDTH, 20);

	char max_score[] = "Recorde";
	draw_string(max_score, WIDTH, 60);
	
	char max_num[10];
	snprintf(max_num, 10, "%d", score.maior);
	draw_string(max_num, WIDTH, 80);

	char level[] = "Nivel";
	draw_string(level, WIDTH, 120);
	
	char level_num[2];
	snprintf(level_num, 2, "%d", score.level);
	draw_string(level_num, WIDTH, 140);
	
	char lives[] = "Vidas";
	draw_string(lives, WIDTH, 180);
	
	char lives_num[2];
	snprintf(lives_num, 2, "%d", player.lives);
	draw_string(lives_num, WIDTH, 200);
	
	char shots_cab[] = "Tiros";
	draw_string(shots_cab, WIDTH, 240);

	char score_shots[1000];
	snprintf(score_shots, 1000, "%d", score.shots);
	draw_string(score_shots, WIDTH, 260);

	char ini_mortos[]= "Inimigos";
	draw_string(ini_mortos, WIDTH, 300);
	
	char ini_mortos_2[]= "mortos";
	draw_string(ini_mortos_2, WIDTH, 320);

	char qtd_mortos[1000];
	snprintf(qtd_mortos, 1000, "%d - 50", invaders.killed);
	draw_string(qtd_mortos, WIDTH, 340);

	char author[] = "Criado por:";
	draw_string(author, WIDTH, 540);
	
	char name[] = "J lambert";
	draw_string(name, WIDTH, 560);
}
//Desenha a tela de inicio
//Draw the title screen
void draw_title_screen() {
	
	SDL_Rect src;
	SDL_Rect dest;
	
	src.x = 0;
	src.y = 0;
	src.w = title_screen->w;
	src.h = title_screen->h;
	
	dest.x = (SCREEN_WIDTH / 2) - (title_screen->w / 2);
	dest.y = 0;
	dest.w = title_screen->w;
	dest.h = title_screen->h;
	
	SDL_BlitSurface(title_screen, &src, screen, &dest);
}
//Desenha o saucer se ele estiver vivo
//Draw the saucer if its alive
void draw_saucer() {

	SDL_Rect src;
	
	src.x = 0;
	src.y = 0;
	src.w = 30;
	src.h = 20;
	
	if (saucer.alive == 1) {
		
		SDL_BlitSurface(saucer_img, &src, screen, &saucer.hitbox);
	}
}
//Desenha os invaders, se eles estiverem vivos
//Draw the invaders if there alive
void draw_invaders() {
	
	SDL_Rect src, dest;
	int i,j;
	
	src.w = E_WIDTH;
	src.h = E_HEIGHT;
	
	for (i = 0; i < 5; i++) {
		
		for (j = 0; j < 10; j++) {
			
			if (invaders.enemy[i][j].alive == 1) {
				//se i tiver valor 0, os invaders terão a cor roxa e estarão na primeira linha da tela
				//purple
				if(i == 0) {	
					
					if (invaders.state == 0) {
						
						src.x = 0;
						src.y = 0;
					
					} else {
						
						src.x = 30;
						src.y = 0;				
					}
				
				//se i tiver valor entre 0 e 3, os invaders terão a cor verde e estarão na segunda e terceira linha da tela
				//green
				} else if (i > 0 && i < 3) {
					
					if (invaders.state == 0) {
						
						src.x = 0;
						src.y = E_HEIGHT;

					} else {
						
						src.x = 30;
						src.y = E_HEIGHT;
					}
				//se i tiver valor entre 0 e 3, os invaders terão a cor vermelha e estarão na quarta e quinta linha da tela
				//red
				} else {
					
					if (invaders.state == 0) {
					
						src.x = 0;
						src.y = E_HEIGHT * 2;
					
					} else {
					
						src.x = 30;
						src.y = E_HEIGHT * 2;	
					}
				}
				
				dest.x = invaders.enemy[i][j].hitbox.x;
				dest.y = invaders.enemy[i][j].hitbox.y;
				dest.w = invaders.enemy[i][j].hitbox.w;
				dest.h = invaders.enemy[i][j].hitbox.h;
			
				SDL_BlitSurface(invadersmap, &src, screen, &dest);
			}
		}
	}
}
//Desenha as bases
//Draw the bases
void draw_bases() {
	
	SDL_Rect src;
	
	src.x = 0;
	src.y = 0;
	src.w = BASE_WIDTH;
	src.h = BASE_HEIGHT;

	int i;

	for(i = 0; i < BASE; i++) {
		
		SDL_BlitSurface(base_img[i], &src, screen, &base[i].hitbox);
	}
}
//Desenha o jogador
//Draw the player
void draw_player() {
	
	SDL_Rect src;
	
	src.x = 0;
	src.y = 0;
	src.w = P_WIDTH;
	src.h = P_HEIGHT;
	
	SDL_BlitSurface(player_img, &src, screen, &player.hitbox);
}
//Desenha as balas tanto do jogador quanto dos inimigos, se elas estiverem "vivas"
//Draw both the enemy and the players bullets if there alive
void draw_bullets(struct bullet_t b[], int max) {
	
	//Uint8 c = SDL_MapRGB(screen->format, 255, 255, 255);
	int i;


	for (i = 0; i < max; i++) {
		
		if (b[i].alive == 1) {
		
			SDL_FillRect(screen, &b[i].hitbox, 255);
		}
	}
}
//Desenha um caractere
//Draw a char
int draw_char(char c, int x, int y) {

	SDL_Rect src;
	SDL_Rect dest;
	int i,j;
	char *map[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
			"abcdefghijklmnopqrstuvwxyz",
			"!@#$%^&*()_+{}|:\"<>?,.;'-=",
			"0123456789"};
	
	src.x = 0;
	src.y = 0;
	src.w = 20;
	src.h = 20;
	
	dest.x = x;
	dest.y = y;
	dest.w = 20;
	dest.h = 20;
	
	for (i = 0; i < 4; i++) {
	
		for(j = 0; j < strlen(map[i]); j++) {
			
			if (c == map[i][j]) {
			
				SDL_BlitSurface(cmap, &src, screen, &dest);
				return 0;
			}
			
			src.x += 20;
		}
	
		src.y += 20;//move down one line on the image file, passa para a próxima linha da imagem
		src.x = 0; //reset to start of line, reinicia para o inicio da linha da imagem
	}

	return 0;
}
//Desenha uma string de caracteres
//Draw a string of chars
void draw_string(char s[], int x, int y) {

	int i;

	for (i = 0; i < strlen(s); i++) {
	
		draw_char(s[i],x,y);
		x += 20;
	}
}




//Desenha a mensagem de fim de jogo
//Draw Game Over message
void draw_game_over() {
	
	SDL_Rect src;
	SDL_Rect dest;
	
	src.x = 0;
	src.y = 0;
	src.w = game_over_img->w;
	src.h = game_over_img->h;
	
	dest.x = (WIDTH / 2) - (game_over_img->w / 2);
	dest.y = (HEIGHT / 2) - (game_over_img->h / 2);
	dest.w = game_over_img->w;
	dest.h = game_over_img->h;
	
	SDL_BlitSurface(game_over_img, &src, screen, &dest);

}

//Cria dano para a base tanto para colisões de balas do jogador ou dos inimigos
//Create damage to the base sprite for player and enemy bullet collisions
void bullet_base_damage(struct base_t *base, int b_num, struct bullet_t *bullet, int l) {

	int i;
	int x,y;
	SDL_Rect src;
	SDL_Rect dest;
	SDL_LockSurface(base_img[b_num]);
	Uint8 *raw_pixels;
	
	raw_pixels = (Uint8 *) base_img[b_num]->pixels;
	
	int pix_offset;
	
	//bottom
	if (l == 0) {
		//quão longe da esquerda a bala atingiu a base
		//how far from the left did the bullet hit the base sprite
		x = (bullet->hitbox.x + 3) - base->hitbox.x;
		//começa da parte de baixo da sprite
		//start from bottom of the base sprite
		y = base->hitbox.h - 1;

		for(i = 0; i < base->hitbox.h; i++) {
			//o calculo de x pode levar até a coluna 60, quando a coluna maxima possivel é 59
			//the x calculation can get us to pixel column 60 when 59 is the maximum (0 - 59 is 60 pixels)
			if (x >= BASE_WIDTH) {
				x = BASE_WIDTH - 1;
			}

			pix_offset = y * base_img[b_num]->pitch  + x;	
			
			//encontrada parte da base que não é magenta, procurando a partir da parte de baixo
			//found part part of the base sprite that is NOT magenta(index)
			//searching from the bottom up
			if (raw_pixels[pix_offset] != 227) {
					
				bullet->alive = 0;
				
				src.x = 0;
				src.y = 0;
				src.w = 11;
				src.h = 15;

				dest.x = x - 3;
				dest.y = y - 14;
				dest.w = 11;
				dest.h = 15;
				
				SDL_UnlockSurface(base_img[b_num]);
				SDL_BlitSurface(damage_img, &src, base_img[b_num], &dest);
				
				break;
			}
			
			y--;
		}
	}
	//topo
	//top
	if (l == 1) {
		//quão longe da esquerda a bala acertou a base
		//how far from the left did the bullet hit the base sprite
		x = (bullet->hitbox.x + 3) - base->hitbox.x;
		//começa do topo da base
		//start from top of the base sprite
		y = 0;
		
		for(i = 0; i < base->hitbox.h; i++) {
			//o calculo de x pode levar até a coluna 60, quando a coluna maxima possivel é 59
			//the x calculation can get us to pixel column 60 when 59 is the maximum (0 - 59 is 60 pixels)
			if (x >= BASE_WIDTH) {
				x = BASE_WIDTH - 1;
			}

			pix_offset = y * base_img[b_num]->pitch  + x;	
			
			//encontrada parte da base que não é magenta, procurando a partir do topo
			//found part part of the base sprite that is NOT magenta(index)
			//searching from the top down
			if (raw_pixels[pix_offset] != 227) {
					
				bullet->alive = 0;
			
				src.x = 0;
				src.y = 0;
				src.w = 11;
				src.h = 15;

				dest.x = x - 3;
				dest.y = y;
				dest.w = 11;
				dest.h = 15;
				
				SDL_UnlockSurface(base_img[b_num]);
				SDL_BlitSurface(damage_top_img, &src, base_img[b_num], &dest);
				
				break;
			}
			
			y++;
		}
	}

	SDL_UnlockSurface(base_img[b_num]);
}

//Cria dano para a base para colisões entre os inimigos e a base
//Create damage to the base sprite for enemy and base collisions
void enemy_base_damage(struct enemy_t *enemy, struct base_t *base, int index) {
	
	int x,y;
	SDL_Rect dest;

	//o ponto x é escolhido do topo esquerdo da sprite com velocidade em pixes adicionada caso os inimigos pulem os ultimos pixels,
	//e a colisão não é mais detectada. Velocidade em pixels é subtraída se viajando para a esquerda
	//the x hot spot is taken from the top left of the sprite with the speed in pixels
	//added ahead in case the enemy skips the last few pixels of the sprite and
	//the collision is no longer detected. Speed in pixels is subtracted if traveling left
	
	if (invaders.direction == right) {
	
		x = (enemy->hitbox.x + invaders.speed) - base->hitbox.x;
		y = enemy->hitbox.y - base->hitbox.y;
		
		if (x > 0) {
			
			dest.x = 0;
			dest.y = y;
			dest.w = x;
			dest.h = enemy->hitbox.h;
		
			SDL_FillRect(base_img[index], &dest, 227);
		}
	
	} else if (invaders.direction == left){
		
		x = (enemy->hitbox.x + (enemy->hitbox.w - 1)) - invaders.speed;
		x = x - base->hitbox.x;
		y = enemy->hitbox.y - base->hitbox.y;

		if (x < base->hitbox.w) {
		
			dest.x = x;
			dest.y = y;
			dest.w = base->hitbox.w - 1;
			dest.h = enemy->hitbox.h;
		
			SDL_FillRect(base_img[index], &dest, 227);
		}
	}		
}
//Detecta colisões entre inimigos e a base 
//Look for collisions based on enemy and base rectangles
void enemy_base_collision() {

	int i,j,k,c;

	for (i = 0; i < 5; i++) {

		for (j = 0;  j < 10; j++) {
		
			for (k = 0;  k < BASE; k++) {
			
				if (invaders.enemy[i][j].alive == 1) {
				
					c = collision(invaders.enemy[i][j].hitbox,base[k].hitbox);		
					
					if (c == 1) {
						
						enemy_base_damage(&invaders.enemy[i][j], &base[k], k);
					}
				}
			}
		}
	}
}
//Detecta colisões entre as balas e as bases
//Look for collisions based on bullet and base rectangles
void bullet_base_collision(struct bullet_t b[], int max, int l) {

	int i,j,c;

	for (i = 0; i < max; i++) {
		
		for (j = 0; j < BASE; j++) {
	
			if (b[i].alive == 1) {
			
				c = collision(b[i].hitbox, base[j].hitbox);

				if (c == 1) {
					
					bullet_base_damage(&base[j], j, &b[i],l);
				}
			}
		}
	}
}
//programa principal
//Main program
int main() {
	/*Inicializa o sistema de video SDL e checa se há erros*/
	/* Initialize SDL’s video system and check for errors */
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	/*Inicializa o sistema de audio SDL*/
	SDL_Init(SDL_INIT_AUDIO);
	/*Garante que SDL_Quit será chamado quando o programa for fechado!*/
	/* Make sure SDL_Quit gets called when the program exits! */
	atexit(SDL_Quit);
	/*Determina o titulo da janela*/
	/*set window title*/
	SDL_WM_SetCaption("Space Invaders", "P");
	/*Tenta iniciar modo de video com cores 8 bits e tela 800x600*/
	/* Attempt to set a 800x600 8 bit color video mode */
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 8, SDL_DOUBLEBUF );
	
	if (screen == NULL) {
		
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
	//carrega todas as imagens necessárias
	//load images
	load_image("titlescreen.bmp", &title_screen, magenta);
	load_image("cmap.bmp", &cmap, magenta);
	load_image("invaders.bmp", &invadersmap, magenta);
	load_image("player.bmp", &player_img, magenta);
	load_image("saucer.bmp", &saucer_img, magenta);
	load_image("gameover.bmp", &game_over_img, magenta);
	load_image("damage.bmp", &damage_img, lime);
	load_image("damagetop.bmp", &damage_top_img, lime);

	Uint32 next_game_tick = SDL_GetTicks();
	int sleep = 0;
	Uint8 *keystate = 0;
	int quit = 0;
	SDL_Event event;
	

	//Função da biblioteca SDL_mixer, que recebe como parâmetros a frequencia que a musica será reproduzida, o formato, o numero de canais e o buffer.
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	Mix_Music* music;	
	music=Mix_LoadMUS("8bits.wav");
	Mix_PlayMusic(music,-1);

	
	init_score();
	init_invaders();
	init_bases();
	init_player();
	init_saucer();
	init_bullets(bullets, P_BULLETS);
	init_bullets(e_bullets, E_BULLETS);
	state = menu;
	title_time = SDL_GetTicks();
		
	/*Inicia*/
	/* Animate */
	while (quit == 0) {
		
		/*Faz uma captura do teclado*/
		/* Grab a snapshot of the keyboard. */
		keystate = SDL_GetKeyState(NULL);
		
		while (SDL_PollEvent(&event)) {

			switch(event.type) {
				
				case SDL_KEYDOWN:
					
					switch( event.key.keysym.sym ) {
						//sai do loop do jogo se ESC for pressionado
						//exit out of game loop if escape is pressed
						case SDLK_ESCAPE:
							
							quit = 1;
						break;
						//caso espaço seja pressionado
						case SDLK_SPACE:	
							//inicia o jogo
							if (state == menu) {

								state = game;
							//atira
							} else if (state == game){
								
								player_shoot();
								saucer_ai();
							//reinicia o jogo
							} else if (state == game_over) {
							
								init_invaders();
								init_bases();
								init_score();
								init_player();
								state = game;
							}
						break;
						//caso s seja apertado.
						case SDLK_s:
							
							if (state == menu){
								
								inic_txt();
						}
						
						break;
						//caso p seja apertado, o jogo pausa.
						case SDLK_p:
							if (state == game){
								pause_for(100000);
								pause_game();
							}

							else if (state == pause){
						
								state = game;

						}
						
						break;

						default:
						break;
					}
				break;
			}
		}
	
		draw_background();

		if (state == menu) {
			
			char s[] = "Pressione ESPACO para jogar";
			SDL_Rect src[60];
			
			int i;

			if (title_time + 2000 < SDL_GetTicks())  {
			
				src[0].x = 180;
				src[0].y = 40;
				src[0].w = 440;
				src[0].h = 230;
			
				SDL_FillRect(screen, &src[0], 248);
			
			} else {
			
				int y = 0;

				for (i = 0; i < 60; i++) {
				
					src[i].x = 0;
					src[i].y = y;
					src[i].w = SCREEN_WIDTH;
					src[i].h = 10;

					SDL_FillRect(screen, &src[i], 227);
				
					y += 10;							
				}
			
				for (i = 0; i < 60; i++) {

					SDL_FillRect(screen, &src[i], rand() % 255);

				}
			}
			
			draw_title_screen();	
			draw_string(s, (SCREEN_WIDTH / 2) - (strlen(s) * 10), 500);

		} else if (state == game) {
			//movimenta o jogador
			//move player
			if (keystate[SDLK_LEFT]) {
				
				move_player(left);
			}

			if (keystate[SDLK_RIGHT]) {
				
				move_player(right);
			}
			starq();
			draw_hud();
			draw_player();
			draw_bases();
			draw_invaders();
			draw_saucer();
			draw_bullets(bullets, P_BULLETS);
			draw_bullets(e_bullets, E_BULLETS);
			enemy_hit_collision();
			player_hit_collision();
			enemy_base_collision();
			saucer_hit_collision();
			bullet_base_collision(e_bullets, E_BULLETS, 1);
			bullet_base_collision(bullets, P_BULLETS, 0);
			enemy_player_collision();
			move_invaders(invaders.speed);
			move_saucer();
			move_bullets(bullets, P_BULLETS, -30);
			move_bullets(e_bullets, E_BULLETS, 15);
			calculate_level();
			enemy_ai();
			game_over_ai();
			pause_game();
		
		} else if (state == game_over) {
			
			arq();
			mnsg_record();
			draw_hud();
			draw_player();
			draw_bases();
			draw_invaders();
			draw_saucer();
			draw_bullets(bullets, P_BULLETS);
			draw_bullets(e_bullets, E_BULLETS);
			draw_game_over();
		
		} else if (state == pause) {
			
			draw_hud();
			draw_player();
			draw_bases();
			draw_invaders();
			draw_saucer();
			draw_bullets(bullets, P_BULLETS);
			draw_bullets(e_bullets, E_BULLETS);
			
			pause_game();
		}
		/*pede para o SDL atualizar a tela inteira*/
		/* Ask SDL to update the entire screen. */
		SDL_Flip(screen);

		next_game_tick += 1000 / 30;
		sleep = next_game_tick - SDL_GetTicks();
	
		if( sleep >= 0 ) {

            		SDL_Delay(sleep);
        	}
	
	}
	

	//libera a variavel music e fecha o audio
	Mix_FreeMusic(music);
	Mix_CloseAudio();

	return 0;
}
