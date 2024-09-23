#include <stdio.h>
#include <string.h>

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

int main(){
    menu();
    char esc[3];
    char arquivo[6] = "user";

    printf("Digite 1 para user 1 e 2 para user 2: \n");
    scanf("%s", esc);

    escArq(strcat(strcat(arquivo, esc), "/")); // Adiciona a escolha e "/" ao final de "user"

    return 0;
}
