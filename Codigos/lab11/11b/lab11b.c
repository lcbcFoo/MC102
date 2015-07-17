/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 11a */

#include <stdio.h>
#include <string.h>

struct time {
    
    char nome[21];
    int indice, pontos, vitorias;
    int pontosGanhos, pontosPerdidos, setsGanhos, setsPerdidos; 
};

typedef struct time time_t;

/* Atualiza os atributos relativos aos sets e aos pontos */
void atualizaSetsPontos(time_t *time, int setsGanhos, int setsPerdidos, 
                        int pontosGanhos, int pontosPerdidos) {
    
    time->setsGanhos += setsGanhos;
    time->setsPerdidos += setsPerdidos;
    time->pontosGanhos += pontosGanhos;
    time->pontosPerdidos += pontosPerdidos;
    
}   

/* Atualiza os atributos relativos as partidas */
void atualizaPartida(time_t *timeGanhador, time_t *timePerdedor, 
                     int diferencaSets, int confrontoDireto[][6]) {

   timeGanhador->vitorias++;

   if (diferencaSets > 1)
      timeGanhador->pontos += 3;
   else {
      timeGanhador->pontos += 2;
      timePerdedor->pontos += 1;
   }

   confrontoDireto[timeGanhador->indice][timePerdedor->indice] = 1;
   confrontoDireto[timePerdedor->indice][timeGanhador->indice] = -1;
}   


/* Verifica qual o indice no vetor de registros do time lido */
int leituraTime(time_t grupo[], int *count){
    
    int i, aux, flag = 1;
    char leitura[21];
    
    /* Recebe o nome da selecao */
    scanf(" ");
    scanf("%s", leitura);

    /* Caso a selecao ja tenha sido lida anteriormente, retorna o indice dela */
    for(i = 0; (flag) && (i < *count); i++){

        if(strcmp(grupo[i].nome, leitura) == 0){
            aux = i;
            flag = 0;
        }
    }

    /* Caso contrario, salva esse selecao na proxima posicao nao utilizada, * 
     * salva essa posicao no seu indice e retorna seu indice */
    if(flag){
        strcpy(grupo[*count].nome, leitura);
        grupo[*count].indice = *count;
        aux = *count;
        (*count)++;
    }
    
    return aux;
}        
      
/* Le os resultados das partidas entre todos os times de uma chave */
void leResultadosChave(time_t timesChave[], int confrontoDireto[][6]) {
    
    int i, time1, time2, game, set1, set2, placar1, placar2, count = 0, aux;
    int ponto1, ponto2;
    
    /* Zera os contadores de cada posicao do vetor de registros */
    for(i = 0; i < 6; i++){
        timesChave[i].vitorias = 0;
        timesChave[i].pontos = 0;
        timesChave[i].setsGanhos = 0;
        timesChave[i].setsPerdidos = 0;
        timesChave[i].pontosGanhos = 0;
        timesChave[i].pontosPerdidos = 0;
    } 

    /* Cada volta do loop le o resultado de um jogo */
    for(i = 0; i < 15; i++){             
        time1 = leituraTime(timesChave, &count);                
        time2 = leituraTime(timesChave, &count);

        /* Zera variaveis auxiliares. Game eh uma flag que indica fim da partida * 
         * set1, set2, ponto1, ponto2 guardam os sets e os pontos ganhos da * 
         * selecao 1 e da selecao 2, respectivamente */
        game = 0;
        set1 = 0;
        set2 = 0;
        ponto1 = 0;
        ponto2 = 0;
        
        /* Cada volta do loop recebe a pontuacao de um set, ele para quando uma * 
         * selecao vencer 3 sets */
        do{
            scanf("%d-%d", &placar1, &placar2);
            ponto1 += placar1;
            ponto2 += placar2;

            /* Verifica quem ganhou o set*/
            if(placar1 > placar2)
                set1++;
                         
            else
                set2++;

            /* Caso o primeiro time ganhe a partida, chama a funcao que atualiza * 
             * os resultados passando o primeiro time como ganhador */
            if(set1 == 3){
                game = 1;
                aux = set1 - set2;
                atualizaPartida(&timesChave[time1], &timesChave[time2], aux, 
                                confrontoDireto); 
            
            }

            /* Caso o segundo time ganhe a partida, chama a funcao que atualiza * 
             * os resultados passando o segundo time como ganhador */
            if(set2 == 3){
                game = 1;
                aux = set2 - set1;
                atualizaPartida(&timesChave[time2], &timesChave[time1], aux, 
                                confrontoDireto);
            
            }
        }while(game == 0);

        /* Chama a funcao que atualiza os sets e os pontos para os 2 times */
        atualizaSetsPontos(&timesChave[time1], set1, set2, ponto1, ponto2);
        atualizaSetsPontos(&timesChave[time2], set2, set1, ponto2, ponto1);
    }
}

/* Encontra o indice do melhor colocado para a iteracao atual do selection * 
 * sort */
int indiceMaior(time_t vet[], int inicio, int desempate[][6]) {
    
    int j, max = inicio;
    double setMax, setJ, pontosMax, pontosJ;
    
    /* Verifica o time que possui o maior numero de pontos */
    for (j = inicio + 1; j < 6; j++){
        if (vet[max].pontos < vet[j].pontos)
            max = j;
        
        /* Caso os pontos sejam iguais, qual tem mais vitorias */
        else if(vet[max].pontos == vet[j].pontos){
            
            if(vet[max].vitorias < vet[j].vitorias)
                max = j;
            
            /* Caso as vitorias tambem sejam iguais, qual tem maior aproveitamento de sets*/
            else if(vet[max].vitorias == vet[j].vitorias){
                setMax = vet[max].setsGanhos / (double) (vet[max].setsGanhos + 
                         vet[max].setsPerdidos);

                setJ = vet[j].setsGanhos / (double) (vet[j].setsGanhos + 
                       vet[j].setsPerdidos);
                
                if(setMax < setJ)
                    max = j;
              
                /* Continuando o empate, verifica qual o maior aproveitamento de pontos */
                else if(setMax == setJ){
                    pontosMax = vet[max].pontosGanhos / (double) (vet[max].pontosGanhos + 
                                vet[max].pontosPerdidos);
                    
                    pontosJ = vet[j].pontosGanhos / (double) (vet[j].pontosGanhos + 
                    vet[j].pontosPerdidos);
                    
                    if(pontosMax < pontosJ)
                        max = j;
                    
                    /* Caso o empate persista, verifica quem ganhou o confronto direto */
                    else if(pontosMax == pontosJ)

                        if(desempate[max][j] < 0)
                            max = j;
                }
            }
        }    
    }                    
        
    return max;
}

/* Troca dois elemenots do vetor de registro durante a ordenacao */
void troca(time_t *a, time_t *b) {

    time_t aux;
    
    aux = *a;
    *a = *b;
    *b = aux;
}

/* Ordena o vetor de times */
void ordenaTimes(time_t times[], int n, int confrontoDireto[][6]) {
    
    int i, max;

    /* Ordena os 4 primeiros colocados de um grupo, ja que os 2 ultimos * 
     * nao sao reelevantes para a formacao das quartas de final */
    for (i = 0; i < 4; i++) {
        max = indiceMaior(times, i, confrontoDireto);
        troca(&times[i], &times[max]);
    }
}


int main() {
    
    /* variaveis de entrada */
    time_t timesChaveA[6], timesChaveB[6];
    
    /* variaveis auxiliares */
    int i, confrontosChaveA[6][6], confrontosChaveB[6][6];
    
    /* le entrada */
    leResultadosChave(timesChaveA, confrontosChaveA);
    leResultadosChave(timesChaveB, confrontosChaveB);

    /* ordena os vetores de times na ordem de classificacao */
    ordenaTimes(timesChaveA, 6, confrontosChaveA);
    ordenaTimes(timesChaveB, 6, confrontosChaveB);

    /* imprime a saida */
    for (i = 0; i < 4; i++) {
        printf("%s x %s\n", timesChaveA[i].nome, timesChaveB[3-i].nome);
    }
    
    return 0;
}    