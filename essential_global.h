//Giusepe Lopes (tessarigiusepe@yahoo.com.br)
//PUCRS
//Junho de 2016


#include "SDL/SDL.h"
#include <stdio.h>

//global variables, for convenience.
static SDL_Surface *screen;
static SDL_Surface *title_screen;
static SDL_Surface *cmap;
static SDL_Surface *invadersmap;
static SDL_Surface *player_img;
static SDL_Surface *saucer_img;
static SDL_Surface *base_img[4];
static SDL_Surface *damage_img;
static SDL_Surface *damage_top_img;
static SDL_Surface *game_over_img;
unsigned int pause_len;
Uint32 pause_time;
Uint32 title_time;

void essglo();
