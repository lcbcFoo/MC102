/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 02a */


#include <stdio.h>

int main () {

    int creditos, somaCred = 0, somaNota = 0;
    double CR = 0;
    char conceito;

    /*testando se o CR é indefinido*/
    scanf("%c", &conceito);
    
    if(conceito == '*') {
        printf("CR = Indefinido\n");
        
        /*CR=11 é um controle que mostra que o CR é indefinido no fim do 
        programa*/
        CR = 11;
    }

    /*Para o caso de CR nao ser indefinido, calculando somaNota e somaCred*/
    else {
        scanf("%d", &creditos);
        
        do {
            if(conceito != '*') {
                if(conceito == 'A') {
                    somaNota = somaNota + (4 * creditos);
                    somaCred = somaCred + creditos;
                }
                if(conceito == 'B') {
                    somaNota = somaNota + (3 * creditos);
                    somaCred = somaCred + creditos;
                }
                if(conceito == 'C') {
                    somaNota = somaNota + (2 * creditos);
                    somaCred = somaCred + creditos;
                }
                if(conceito == 'D') {
                    somaNota = somaNota + (1 * creditos);
                    somaCred = somaCred + creditos;
                }
                if(conceito == 'E') {
                    somaCred = somaCred + creditos;
                }
            }

            /*Verificando o fim do loop*/
            scanf("%c", &conceito);

            if(conceito != '*') {
                scanf("%d", &creditos);
            }

        } while (conceito != '*');
    }

    /*Calculando o CR se o aluno nao reprovou em todas as disciplinas*/
    if(somaNota != 0) {
        CR = somaNota / (double) somaCred;
        printf("CR = %.4f\n", CR);
    }
    
    /*Imprimindo CR = 0.0000 para o caso do aluno que reprovou em tudo*/
    else {
        if(CR != 11){
            printf("CR = 0.0000\n");
        }
    }
    return 0;
}