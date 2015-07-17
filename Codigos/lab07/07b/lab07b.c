/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 07b */

#include <stdio.h>

/* Essa funcao eh responsavel por iniciar todos os elementos da matriz *
 * auxiliar com '0' a cada vez que um novo caminho for testado */
void ZeraCaminho(int rota[][50], int N, int M) {

    int i, j;

    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            rota[i][j] = 0;

    return;
}

int main () {

    int linha, i, j, N, M, trap, loop, win, passos, TamLoop, rota[50][50];
    char tabuleiro[50][50], posicao;

    /* Recebe o tamanho do tabuleiro */
    scanf("%d %d", &N, &M);

    /* Recebe os comandos existentes em cada posicao do tabuleiro */
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            scanf(" %c", &tabuleiro[i][j]);

    /* Cada volta do for testa um caminho a partir de uma nova linha */
    for(linha = 0; linha < N; linha++) {

        /* Reinicia as variaveis utilizadas em cada volta do loop. "i" e "j" *
         * indicam a posicao atual. "trap", "win", "loop" sao flags que *
         * indicam que o robo encontrou: armadilha, saida, entrou em um loop. *
         * "passos" conta os passos dados; um passo eh dado a cada volta. *
         * ZeraCaminho" eh a funcao que zera a matriz auxiliar */
        i = linha;
        j = 0;
        trap = 0;
        win = 0;
        loop = 0;
        passos = 0;
        ZeraCaminho(rota, N, M);

        /* Esse loop para quando o robo sair, encontrar uma armadilha ou *
         * entrar em loop. */
        while(!(trap) && !(loop) && !(win)) {

            /* "posicao" recebe o comando da posicao atual do tabuleiro */
            posicao = tabuleiro[i][j];

            /* Se a posicao for 'X', imprime que existe uma armadilha e o
             * numero de passos. Aciona flag de armadilha */
            if(posicao == 'X') {
                printf("Armadilha em (%d,%d) apos %d passo(s)\n",
                 i + 1, j + 1,passos);

                trap++;
            }

            /* Se a posicao for 'D' guarda na posicao atual da matriz "rota" *
             * o valor atual de "passos" e se move para a linha de baixo */
            if(posicao == 'D') {
                rota[i][j] = passos;
                i++;
            }

            /* Se a posicao for 'U', guarda na posicao atual da matriz "rota" *
             * o valor atual de "passos" e se move para a linha de cima */
            if(posicao == 'U') {
                rota[i][j] = passos;
                i--;
            }

            /* Se a posicao for 'R' : */
            if(posicao == 'R') {

                /* Verifica se o robo saiu. Imprime o local onde ele saiu e *
                 * o numero de passos dados. Aciona flag de saida */
                if(j == M - 1) {
                    printf("Saiu em (%d,%d) apos %d passo(s)\n",
                     i + 1, M, passos);

                    win++;
                }

                /* Caso contrario, guarda na posicao atual da matriz "rota" o *
                 * valor atual de "passos", se move para a coluna da direita */
                else {
                    rota[i][j] = passos;
                    j++;
                }
            }

            /* Se a posicao for 'L', guarda na posicao atual da matriz "rota" *
             * o valor atual de passos e se move para a coluna da esquerda */
            if(posicao == 'L') {
                rota[i][j] = passos;
                j--;
            }

            /* Incrementa "passos" */
            passos++;

            /* Se a posicao atual na matriz auxiliar for diferente de zero, *
             * isso indica que o robo ja passou por esse ponto e entrou em *
             * um loop */
            if(rota[i][j]) {

                /* Calcula o tamanho do loop. Aciona a flag "loop". Imprime o *
                 * tamanho do loop */
                TamLoop = passos - rota[i][j];
                loop++;
                printf("Loop de tamanho %d\n", TamLoop);
            }
        }
    }

    return 0;
}