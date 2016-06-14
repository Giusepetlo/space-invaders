//Giusepe Lopes (tessarigiusepe@yahoo.com.br)
//PUCRS
//Junho de 2016


#include <stdio.h>
#include "maxpont.h"
#include "diverses.h"

//coloca a pontuação do jogador no arquivo maiorpont.txt
void subst() {

    FILE *arquivo;

    arquivo=fopen("maiorpont.txt","w");
    fprintf(arquivo, "%d", score.points);
    fclose(arquivo);
}

//Verifica se a ultima pontuação foi a maior pontuação do jogador
void arq() {

    FILE *arquivo;
    arquivo=fopen("maiorpont.txt","r");


    if(score.maior<score.points) {
        subst();
        score.retorno=1;
    }
    fclose(arquivo);
}



//serve de auxilio para mostrar o valor do recorde na tela de jogo
void starq() {

    FILE *arquivo;

    arquivo=fopen("maiorpont.txt","r");
    fscanf(arquivo, "%d", &score.maior);
    fclose(arquivo);
}

//Função usada para criar o arquivo maiorpont
void inic_txt() {

    FILE *arquivo;

    arquivo=fopen("maiorpont.txt","w");
    fprintf(arquivo, "0");
    fclose(arquivo);


}

//Função para imprimir a mensagem de novo recorde caso a função arq() retorne verdadeiro.
void mnsg_record() {

    if(score.retorno==1) {
        char mnsg[] = "**Temos um novo recorde!!**";
        draw_string(mnsg, 30, 435);
    }
    score.retorno=0;
}



