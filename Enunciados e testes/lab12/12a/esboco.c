/* Laboratorio 12a - Tweet Extractor
   Autor: 
   Email: 
*/

#include <stdio.h>
#include <string.h>

#define MAX_FILENAME 25
#define MAX_ENTITY 10

/* Funcao que converte uma entidade no caractere correspondente,
   supondo que o caractere '&' foi previamente lido no arquivo de
   entrada (arqin). Se a entidade eh diferente de aspas simples ou
   aspas dupla, a funcao simplesmente o ignora, caso contrario ela
   imprime o caractere correspondente no arquivo de saida (arqout). */
void converte_entidade(FILE *arqin, FILE *arqout) {
    char c, entidade[MAX_ENTITY];
    int i = 0;
    
    /* armazena o codigo da entidade ate encontrar o caractere ';' */
    c = fgetc(arqin);
    while (c != ';') {
        entidade[i++] = c;
        c = fgetc(arqin);
    }
    entidade[i] = '\0';
    
    /* se a entidade corresponde ao caractere aspas simples ou aspas duplas,
       imprime o caractere no arquivo de saida */
    if (!strcmp(entidade, "#39"))
        fprintf(arqout, "\'");
    else if(!strcmp(entidade, "quot"))
        fprintf(arqout, "\"");
}

void extrai_tweets(char nomearqin[], char nomearqout[]) {

}


int main(int argc, char *argv[]) {  
    char nomearqin[MAX_FILENAME], nomearqout[MAX_FILENAME];
    
    /* Copia os nomes do arquivo de entrada e de saida nas variaveis */
    strcpy(nomearqin, argv[1]);
    strcpy(nomearqout, argv[2]);
 
    extrai_tweets(nomearqin, nomearqout);

    return 0;
}
