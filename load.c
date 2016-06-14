//Giusepe Lopes (tessarigiusepe@yahoo.com.br)
//PUCRS
//Junho de 2016


#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "diverses.h"
#include "load.h"

//Carrega os arquivos de imagens
//Load image files
int load_image(char filename[], SDL_Surface **surface, enum ck_t colour_key) {

    SDL_Surface *temp;
    //carrega a imagem
    //load image
    temp = SDL_LoadBMP(filename);

    if (temp == NULL) {

        printf("Unable to load %s.\n", filename);
        return 1;
    }

    Uint32 colourkey;
    /*Determina a cor da imagem(struct color_key)
    /* Set the image colorkey. */
    if (colour_key == magenta) {

        colourkey = SDL_MapRGB(temp->format, 255, 0, 255);

    } else if (colour_key == lime) {

        colourkey = SDL_MapRGB(temp->format, 0, 255, 0);
    }

    SDL_SetColorKey(temp, SDL_SRCCOLORKEY, colourkey);
    //converte a superficie da imagem para o mesmo tipo da imagem da tela
    //convert the image surface to the same type as the screen
    (*surface) = SDL_DisplayFormat(temp);

    if ((*surface) == NULL) {

        printf("Unable to convert bitmap.\n");
        return 1;
    }

    SDL_FreeSurface(temp);

    return 0;
}
