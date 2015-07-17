/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 08b */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* Definindo tamanho maximo das imagens */
#define MAX_TAM 400

/* Le uma imagem em formato PGM a partir da entrada padrao.
 * Retorna 1 se a leitura for realmente de um arquivo PGM
 * e 0 caso contrario */
int ler_pgm(int img[][MAX_TAM], int *W, int *H, int *MaxV,
            int *F, double *C, double *Gama) {
    char nome_formato[3];
    int i,j;

    /* Le o formato da imagem. P2 indica o formato PGM */
    scanf("%s ", nome_formato);
    if (strcmp(nome_formato, "P2") != 0)
        return 0;

    /* Le o '#', que indica um comentario, e os numeros indicando
       o filtro e os parametros, se houver */
    scanf("# %d", F);

    if (*F == 1) {
        scanf("%lf %lf", C, Gama);
    }

    /* Le dimensoes e intensidade maxima da imagem */
    scanf("%d", W);
    scanf("%d", H);
    scanf("%d", MaxV);

    /* Le o valor de cada ponto da imagem */
    for (i = 0; i < (*H); i++) {
        for (j = 0; j < (*W); j++) {
            scanf("%d", &img[i][j]);
        }
    }

    return 1;
}

/* Escreve a imagem em formato PGM na saida padrao */
void escrever_pgm(int img[][MAX_TAM], int W, int H, int MaxV) {
    int i, j;

    /* Escreve os atributos da imagem */
    /* Tipo da imagem: P2 significa pgm*/
    printf("P2\n");

    /* Dimensoes e intensidade maxima da imagem */
    printf("%d %d %d\n", W, H, MaxV);

    /* Escreve os pontos da imagem */
    for (i = 0; i < H; i++) {
        printf("%d", img[i][0]);
        for (j = 1; j < W; j++) {
            printf(" %d", img[i][j]);
        }
        printf("\n");
    }
}

/* Transformacao de Potencia (gama) */
void potencia(int img[][MAX_TAM], int W, int H, int MaxV,
              double c, double gama) {
                
    int i, j;
    double aux;

    for(i = 0; i < H; i++)
        for(j = 0; j < W; j++) {

            aux = c * pow(img[i][j], gama);
            img[i][j] = floor(aux);

            if(img[i][j] > MaxV)
                img[i][j] = MaxV;
        }

    return;

}

/* Espelhamento */
void espelhamento(int img[][MAX_TAM], int W, int H) {

    int i, j;

    for(j = 0; j <= W / 2; j++)
        for(i = 0; i < H; i++)
            img[i][j] = img[i][W - j - 1];

    return;
}

/* Reducao de Ruidos com Filtro Gaussiano */
void reducaoRuido(int img[][MAX_TAM], int W, int H, int MaxV) {

    int i, j, k, l, mat[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
    double **aux;

    aux = malloc(H * sizeof(double *));

    for(i = 0; i < H; i++)
        aux[i] = malloc(W * sizeof(double));
    
    for(i = 1; i < H - 1; i++){
        for(j = 1; j < W - 1; j++){

            aux[i][j] = 0;

            for(k = 0; k < 3; k++)
                for(l = 0; l < 3; l++)
                    aux[i][j] += mat[k][l] * img[i + k - 1][j + l - 1];

            aux[i][j] = floor(aux[i][j] / 16);

            if(aux[i][j] > MaxV)
                aux[i][j] = MaxV;
        }
    }

    for(i = 1; i < H - 1; i++){
        for(j = 1; j < W - 1; j++)
            img[i][j] = aux[i][j];

        free(aux[i]);
    }    

    free(aux);
    
    return;
}

/* Rotacao 90 graus */
void rotacao(int img[][MAX_TAM], int W, int H) {

    int i, j, **aux;

    aux = malloc (W * sizeof(int *));

    for(i = 0; i < W; i++)
        aux[i] = malloc ( H * sizeof(int));
    
    for(i = 0; i < H; i++) 
        for(j = 0; j < W; j++)
            aux[W - 1 - j][i] = img[i][j];


    for(i = 0; i < W; i++){
        for(j = 0; j < H; j++)
            img[i][j] = aux[i][j];

        free(aux[i]);
    }

    free(aux);

    return;

}

int main() {
    /* Matriz que armazena os pixels da imagem */
    int img[MAX_TAM][MAX_TAM];
    /* Atributos da imagem */
    int W, H, MaxV, aux;
    /* Identificador do filtro a ser utilizado */
    int F;
    /* Parametros a serem passados para a potencia */
    double C, Gama;

    /* Le a imagem */
    if (ler_pgm(img, &W, &H, &MaxV, &F, &C, &Gama) != 1) {
        printf("Error: nao foi possivel ler a imagem\n");
        return 0;
    }

    /* Seleciona o filtro */
    switch (F) {
        case 1:
            potencia(img, W, H, MaxV, C, Gama);
            break;
        case 2:
            espelhamento(img, W, H);
            break;
        case 3:
            reducaoRuido(img, W, H, MaxV);
            break;
        case 4:
            rotacao(img, W, H);
            aux = W;
            W = H;
            H = aux;
            break;
    }

    /* Escreve a imagem */
    escrever_pgm(img, W, H, MaxV);

    return 0;
}