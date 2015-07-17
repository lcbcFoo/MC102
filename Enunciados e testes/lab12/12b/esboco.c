/* Laboratorio 12b - Bola de Ouro
   Autor: Seu nome e RA aqui
   Email: Seu e-mail aqui
*/

#include <stdio.h>
#include <string.h>

/* Tamanho maximo do nome do jogador */
#define MAXNOME 26
/* Tamanho maximo do nome dos arquivos de entrada/saida */
#define MAXNOMEARQ 101
/* Numero maximo de jogadores */
#define MAXJOGADORES 40

/* Jogador:
 * nome = nome do jogador
 * C1 = numero de gols
 * C2 = numero de assistencias
 * C3 = numero de dribles feitos
 * C4 = numero de gols contra
 * C5 = numero de cartoes vermelhos
 * C6 = numero de cartoes amarelos
 */
struct Jogador {
    char nome[MAXNOME];
    int C1;
    int C2;
    int C3;
    int C4;
    int C5;
    int C6;
};

typedef struct Jogador Jogador;

int main(int argc, char **argv) {
    /* Nome do arquivo binario com as estatisticas */
    char nomeArqEstat[MAXNOMEARQ];
    /* Nome do arquivo binario de saida */
    char nomeArqSaida[MAXNOMEARQ];
    
    /* Lendo os nomes dos arquivos binarios */
    strcpy(nomeArqEstat, argv[1]);
    strcpy(nomeArqSaida, argv[2]);   

    /*
     *
     * Implemente aqui o restante da funcao principal
     *
     */
    
    return 0;
}
