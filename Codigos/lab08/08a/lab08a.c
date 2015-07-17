/* Nome: Lucas de Camargo Barros de Castro *
 * RA: 172678 *
 * Laboratorio: 08a */

#include <stdio.h>
#include <stdlib.h>

/* realiza a adicao n1+n2, armazendo o resultado em result */
void add(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {

    int i;

    for(i = 0; i < tam_n1; i++)
        result[i] = n1[i];

    for(i = 0; i < tam_n2; i++){
        result[i] += n2[i];
        
        if(result[i] / 10 > 0){
            result[i] = result[i] % 10;
            result[i + 1]++;
        }
    }

    return;
}

/* realiza a subtracao n1-n2, com n1>=n2, armazenando o resultado em result */
void substract(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {

    int i;

    for(i = 0; i < tam_n1; i++)
        result[i] = n1[i];

    for(i = 0; i < tam_n2; i++)
        result[i] -= n2[i];

    for(i = 0; i < tam_n1; i++){

        if(result[i] < 0){
            result[i] = 10 + result[i];
            result[i + 1]--;
        }
    }
}

/* realiza a multiplicacao n1*n2, armazendo o resultado em result */
void multiply(int *n1, int tam_n1, int *n2, int tam_n2, int *result) {

    int i, j, tamResult;

    tamResult = tam_n1 + tam_n2;
    
    for(i = 0; i < tam_n2; i++){

        for(j = 0; j < tam_n1; j++){

            result[i + j] += (n2[i] * n1[j]);
        }

        for(j = 0; j < tamResult; j++){
            if(result[j] / 10 > 0){
                result[j + 1] += result[j] / 10;
                result[j] = result[j] % 10;
                
            }
        }    
    }

    return;
}

int main() {

    int tamanho1, tamanho2, *resultado, i, j, tamResult, *numero1, *numero2;
    char operacao, recebe;

    scanf("%d %d %c", &tamanho1, &tamanho2, &operacao);

    numero1 = malloc (tamanho1 * (sizeof(int)));
    numero2 = malloc (tamanho2 * (sizeof(int)));

    for(i = 0; i < tamanho1; i++){
        scanf(" %c", &recebe);
        numero1[tamanho1 - 1 - i] = recebe - '0';
    }

    for(i = 0; i < tamanho2; i++){
        scanf(" %c", &recebe);
        numero2[tamanho2 - 1 - i] = recebe - '0';
    }

    if(operacao == 'S') {

        tamResult = tamanho1;
        resultado = malloc (tamResult * (sizeof(int)));
        substract(numero1, tamanho1, numero2, tamanho2, resultado);

    }

    if(operacao == 'A'){
 
        tamResult = tamanho1 + 1;
        resultado = malloc (tamResult * (sizeof(int)));
        add(numero1, tamanho1, numero2, tamanho2, resultado);
    }

    if(operacao == 'M'){
        
        tamResult = tamanho1 + tamanho2;
        resultado = malloc(tamResult * (sizeof(int)));
        multiply(numero1, tamanho1, numero2, tamanho2, resultado);
    }

    i = tamResult - 1;

    while((resultado[i] == 0) && (i > 0))
        i--; 

    for(j = i; j >= 0; j--)
        printf("%d", resultado[j]);
    printf("\n");

    free(numero1);
    free(numero2);
    free(resultado);

    return 0;
}