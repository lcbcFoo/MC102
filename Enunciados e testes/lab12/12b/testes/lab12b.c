/* Nome: Lucas de Camargo Barros de Castro * 
 * RA: 172678 *
 * Laboratorio: 12b */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
     
    int pesos[6], stats, i, j, k, rodadas, n, jogadores_rodada, indice, *notas;
    int flag, conta;
    char nomeAtual[MAXNOME];
    Jogador *jogadores, aux;
    FILE *arqin, *arqout;
    
    /* Lendo os nomes dos arquivos binarios */
    strcpy(nomeArqEstat, argv[1]);
    strcpy(nomeArqSaida, argv[2]);
    
    /* Abre os arquivos */
    arqin = fopen(nomeArqEstat, "r");
    arqout = fopen(nomeArqSaida, "w");

    /* Le o numero de jogadores contidos no scout */
    fread(&n, sizeof(int), 1, arqin);
    
    /* Aloca vetor que guardara as notas */
    notas = malloc(n * sizeof(int));
    
    /* Aloca o vetor de jogadores que guarda as estatisticas de cada jogador */
    jogadores = malloc(n * sizeof(Jogador));
    
    /* Recebe as estatisticas dos jogadores no arquivo de entrada */
    for(i = 0; i < n; i++)
        fread(&jogadores[i], sizeof(Jogador), 1, arqin);
     
    /* Fecha o scout de entrada */
    fclose(arqin);

    /* Recebe os pesos para calculo das notas */ 
    for(i = 0; i < 6; i++)
        scanf("%d", &pesos[i]);
    
    /* Recebe os numeros de rodadas */
    scanf("%d", &rodadas);
    
    /* Cada loop realiza a atualizacao dos dados de uma rodada*/
    for(i = 0; i < rodadas; i++){

        /* Recebe o numero de jogadores que serao atualizados */
        scanf("%d", &jogadores_rodada);
        
        /* Cada loop atualiza os dados de um jogador */
        for(j = 0; j < jogadores_rodada; j++){

            /* Le o nome do jogadores */
            scanf(" ");
            scanf("%s", nomeAtual);
            
            flag = 1;

            /* Seleciona o elemento correspondente a esse jogador no vetor de *
             * jogadores */
            for(k = 0;(flag) && (k < n); k++)
                if(strcmp(nomeAtual, jogadores[k].nome) == 0){
                    indice = k;
                    flag = 0;
                }   
               
            /* Recebe e atualiza suas estatisticas */   
            scanf("%d", &stats);
            jogadores[indice].C1 += stats;
            scanf("%d", &stats);
            jogadores[indice].C2 += stats;
            scanf("%d", &stats);
            jogadores[indice].C3 += stats;
            scanf("%d", &stats);
            jogadores[indice].C4 += stats;
            scanf("%d", &stats);
            jogadores[indice].C5 += stats;
            scanf("%d", &stats);
            jogadores[indice].C6 += stats;
        }
    }
  
    /* Escreve no scout atualizado o numero de jogadores e suas estatisticas *
     * atualizadas, em seguida fecha o scout atualizado */
    fwrite(&n, sizeof(int), 1, arqout);
    
    for(i = 0; i < n; i++)
        fwrite(&jogadores[i], sizeof(Jogador), 1, arqout);

    fclose(arqout);
 
    /* Calcula a media de cada jogador com base na formula do enunciado */
    for(i = 0; i < n; i++){
        notas[i] = 0;

        notas[i] += jogadores[i].C1 * pesos[0];
        notas[i] += jogadores[i].C2 * pesos[1];
        notas[i] += jogadores[i].C3 * pesos[2];

        notas[i] -= jogadores[i].C4 * pesos[3];
        notas[i] -= jogadores[i].C5 * pesos[4];
        notas[i] -= jogadores[i].C6 * pesos[5];
    }
    
    /* Identifica os 3 jogadores com melhores notas, levando a ordem lexicografica*
     * dos nomes como criterio de desempate */
    for (i = 0; i < 3; i++) {
        indice = i;
        
        /* Identfica o indice do proximo melhor colocado */
        for(j = indice + 1; j < n; j++){
            if(notas[indice] < notas[j])
                indice = j;

            else 
                if(notas[indice] == notas[j])
                    if(strcmp(jogadores[indice].nome, jogadores[j].nome) < 0)
                        indice = j;   
        }
        
        /* Troca os elementos do vetor de jogadores */
        aux = jogadores[indice];
        jogadores[indice] = jogadores[i];
        jogadores[i] = aux; 

        /* Troca a posicao das respectivas notas no vetor das notas */
        conta = notas[i];
        notas[i] = notas[indice];
        notas[indice] = conta;              
    }
    
    /* Imprime os 3 finalistas */
    for(i = 0; i < 3; i++)
        printf("%s\n", jogadores[i].nome);       
   
    /* Desaloca vetores auxiliares */
    free(jogadores);
    free(notas);

    return 0;
}