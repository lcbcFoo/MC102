/* Nome: Lucas de Camargo Barros de Castro * 
 * RA: 172678 *
 * Laboratorio: 12a */


#include <stdio.h>
#include <string.h>

#define MAX_FILENAME 25
#define MAX_ENTITY 10

/* Funcao que converte uma entidade no caractere correspondente,
 *  supondo que o caractere '&' foi previamente lido no arquivo de
 *  entrada (arqin). Se a entidade eh diferente de aspas simples ou
 *  aspas dupla, a funcao simplesmente o ignora, caso contrario ela
 *  imprime o caractere correspondente no arquivo de saida (arqout). */
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
     * imprime o caractere no arquivo de saida */
    if (!strcmp(entidade, "#39"))
        fprintf(arqout, "\'");
    else if(!strcmp(entidade, "quot"))
        fprintf(arqout, "\"");
}


void extrai_tweets(char nomearqin[], char nomearqout[]){
    
    FILE *arqin, *arqout;

    /* strings auxiliares e variavel que recebe cada char lido do arquivo de entrada */
    char leitura[49], recebe, lido[5];

    /* strings que determinam o inicio eo fim de um tweet */
    char fim[] = "</p>", inicio[] = "<p class=\"ProfileTweet-text js-tweet-text u-dir\"";
    int i, flag, flag2;
    
    /* abre o arquivo de entrada e o arquivo de saida */
    arqin = fopen(nomearqin, "r");
    arqout = fopen(nomearqout, "w");

    /* a string 'leitura' e 'lido' serao comparadas a 'inicio' e 'fim', respectivamente *
     * para verificar quando um tweet comeca ou termina. Coloca '\0' na ultima posicao *
     * de 'leitura e 'lido' */     
    leitura[48] = '\0';
    lido[4] = '\0';
   
    /* o while continuara ateh ter lido o arquivo de entrada inteiro */
    while(fscanf(arqin, "%c", &recebe) != EOF){
        
        /* Como a string de inicio de tweet comeca com '<p', caso esses caracteres *
         * sejam lidos em sequencia, copia uma string do tamanho da string de *
         * inicio e verifica se elas sao iguais */

        /* Os caracteres '<' e 'p' sao lidos anteriormente para evitar *
         * testes desnecessarios de comparacao de strings */
        if(recebe == '<'){
            leitura[0] = recebe;
            
            fscanf(arqin, "%c", &recebe);
            
            if(recebe == 'p'){
                leitura[1] = recebe;
                
                /* Copia os proximos caracteres lidos para a string auxiliar */
                for(i = 2; i < 48; i++)
                    fscanf(arqin, "%c", &leitura[i]);              
                
                /* Caso a string auxiliar seja igual a de inicio, sinaliza que *
                 * um tweet sera lido */
                if(strcmp(leitura, inicio) == 0){            
                    flag = 1;
                    flag2 = 1;

                    while(flag){

                        /* Procura o primeiro caractere localizado depois de uma tag */
                        while(flag2){
                            fscanf(arqin, "%c", &recebe);
                            
                            if(recebe == '>')
                                flag2 = 0;
                        }
                        
                        flag2 = 1;                           
                        
                        /* Imprime no arquivo de saida todos os caracteres ateh ser *
                         * lido um '<', indicando uma nova tag */
                        while(flag2){
                            fscanf(arqin, "%c", &recebe);
                            
                            if(recebe == '<'){
                                lido[0] = recebe;
                                flag2 = 0;
                            }
                            
                            else{
                                /* Caso seja lido '&', chama a funcao de conversao */
                                if(recebe == '&')
                                    converte_entidade(arqin, arqout);
                                
                                else
                                    fprintf(arqout, "%c", recebe);
                            }
                        }
                    
                        flag2 = 1;
                        
                        /* Copia a tag seguinte na string 'lido' */
                        for(i = 1; (flag2) && (i < 4); i++){
                            
                            fscanf(arqin, "%c", &lido[i]);
                            
                            if(lido[i] == '>'){
                                flag2 = 1;
                                flag2 = 0;
                            }    
                        }  

                        /* Caso essa string seja igual a string que indica fim do *
                         * tweet, termina de copiar este tweet */
                        if(strcmp(lido, fim) == 0){
                            fprintf(arqout, "\n");
                            flag = 0;     
                        }
                    }    
                }    
            }
        }
    }

    /* Fecha os arquivos */
    fclose(arqin);
    fclose(arqout);               
}    

int main(int argc, char *argv[]) {  
    char nomearqin[MAX_FILENAME], nomearqout[MAX_FILENAME];
    
    /* Copia os nomes do arquivo de entrada e de saida nas variaveis */
    strcpy(nomearqin, argv[1]);
    strcpy(nomearqout, argv[2]);
    
    extrai_tweets(nomearqin, nomearqout);
    
    return 0;
}