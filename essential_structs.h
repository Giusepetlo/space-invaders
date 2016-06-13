#include <stdlib.h>
#include <stdio.h>
#include "essential_defines.h"
#include "SDL/SDL.h"

enum colour_t {red, green, purple};
enum direction_t {left, right, stationary};
enum state_t {menu, options, game, game_over, pause};
enum ck_t {magenta, lime};


struct score_t {

	unsigned int shots;
	unsigned int points;
	unsigned int level;
	unsigned int maior;
};

struct saucer_t {
	
	SDL_Rect hitbox;
	unsigned int alive;
	enum direction_t direction;
};

struct enemy_t {

	SDL_Rect hitbox;
	enum colour_t colour;
	unsigned int alive;
	unsigned int points;
};

struct invaders_t {

	struct enemy_t enemy[5][10];
	enum direction_t direction;
	unsigned int killed;
	int speed;
	int state;
	int state_speed;
	Uint32 state_time;
};

struct base_t {

	SDL_Rect hitbox;
};

struct player_t {

	SDL_Rect hitbox;
	int lives;
};

struct bullet_t {
	
	SDL_Rect hitbox;
	unsigned int alive;
};

struct score_t score;
struct invaders_t invaders;
struct saucer_t saucer;
struct base_t base[BASE];
struct player_t player;
struct bullet_t bullets[P_BULLETS];
struct bullet_t e_bullets[E_BULLETS];
enum state_t state;

void esstr();
