#include <stdio.h>
#include <string.h>
#include "funcsArquivos.h"

void menu(){
    printf("Menu:\n");
    printf("1. Consultar Saldo\n"
    "2. Consultar Extrato\n"
    "3. Depositar Reais\n"
    "4. Sacar Reais\n"
    "5. Comprar Criptomoedas\n"
    "6. Vender Criptomoedas\n"
    "7. Atualizar Cotacao\n"
    "8. Sair\n");
}

void escArq(char arquivo[]){
    char tmp[10];
    strcpy(tmp, arquivo);

    strcat(tmp, "teste.txt");

    FILE *arq = fopen(tmp, "a");

    if(arq == NULL){
        printf("erro\n");
    }
    fprintf(arq, "teste\n");
    fclose(arq);
}

// Escolher qual pasta vai abrir:
    // char esc[3];
    // char arquivo[6] = "user";

    // printf("Digite 1 para user 1 e 2 para user 2: \n");
    // scanf("%s", esc);

    // // escArq(strcat(strcat(arquivo, esc), "/"));  Adiciona a escolha e "/" ao final de "user"

float lerArquivo(const char *variavel, const char *arquivo){
    FILE *arq = fopen(arquivo, "r");

    char linha[100];

    while(fgets(linha, sizeof(linha), arq)){
        char tmpVar[15];
        int tmpVal;

        if(sscanf(linha, "%[^ ] %d", tmpVar, &tmpVal) == 2){  // %[^ ] procura até o espaço, %d lê o valor da variável
            if(strcmp(tmpVar, variavel) == 0){
                fclose(arq);
                return tmpVal;
            }
        }
    }
    return 0;
}

void escVar(const char *arquivo, const char *variavel, float valor){
    FILE *arq = fopen(arquivo, "r");
    
    int achouVar = 0; // diz se achou a variavel no txt
    char linha[100];
    char buffer[100];

    while(fgets(linha, sizeof(linha), arq)){
        char tmpVar[15];
        float tmpVal;
        
        if(sscanf(linha, "%[^ ] %f", tmpVar, &tmpVal) == 2){
            if(strcmp(tmpVar, variavel) != 0){ // se as variaveis forem dif
                snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s %f\n", tmpVar, tmpVal);
            } else{
                snprintf(buffer + strlen(buffer), sizeof(buffer) - strlen(buffer), "%s %f\n", tmpVar, valor);
                achouVar = 1;
            }
        } else{
            strncat(buffer, linha, sizeof(buffer) - strlen(buffer) - 1); // deixa a linha igual se nn for usar
        }
    } // nada disso ta escrevendo ainda, so armazenando em variavel
    fclose(arq);

    if(achouVar == 1){
        arq = fopen(arquivo, "w");
        fputs(buffer, arq);
        fclose(arq);
    }
}

int main(){
    int i = 10;
    int j = 20;

    int k = soma(i, j);

    printf("%d", k);

    return 0;
}
