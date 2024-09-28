#include <stdio.h>
#include <string.h>
#include <time.h>

int lerVarInt(const char *, const char *);

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

int login(){
    int user;
    while(1){
        char cpfDigitado[11];
        printf("Digite seu CPF: ");
        scanf("%s", cpfDigitado);
        char cpfArq[5];
        char arquivo[25];
        for(int i = 1; i <= 10; i++){
            snprintf(arquivo, sizeof(arquivo), "user%d/cpfesenha.txt", i);
            int cpfInt = lerVarInt(arquivo, "cpf");
            snprintf(cpfArq, sizeof(cpfArq), "%d", cpfInt);
            if(strcmp(cpfDigitado, cpfArq) == 0){
                printf("Login para o usuario %d\n", i);
                user = i;
                break;
            }
        }
        char senhaDigitada[10];
        printf("Digite sua senha: ");
        scanf("%s", senhaDigitada);
        char senhaArq[10];
        int senhaInt = lerVarInt(arquivo, "senha");
        snprintf(senhaArq, sizeof(senhaArq), "%d", senhaInt);
        if(strcmp(senhaDigitada, senhaArq) != 0){
            printf("CPF e/ou senha errados!! Digite novamente\n");
        } else{
            printf("Login realizado com sucesso. Bem-vindo, usuario %d!", user);
            break;
        }
    }
    menu();
    
    return user;
}

void escExt(char arquivo[], float valor, char moeda[]){
    char tmp[10];
    strcpy(tmp, arquivo);

    strcat(tmp, "extrato.txt");

    FILE *arq = fopen(tmp, "a");

    if(arq == NULL){
        printf("erro\n");
    }

    time_t t;
    time(&t); // le o horario atual pra imprimir o extrato
    
    if(strcmp(moeda, "r") == 0){
        fprintf(arq, "Depositado %f em reais na data %s", valor, ctime(&t));
    } else if(strcmp(moeda, "bc") == 0){
        fprintf(arq, "Depositado %f em bitcoin na data %s", valor, ctime(&t));
    } else if(strcmp(moeda, "eth") == 0){
        fprintf(arq, "Depositado %f em ethereum na data %s", valor, ctime(&t));
    } else{
        fprintf(arq, "Depositado %f em ripple na data %s", valor, ctime(&t));
    }
    
    fclose(arq);
}

// Escolher qual pasta vai abrir:
    // char esc[3];
    // char arquivo[6] = "user";

    // printf("Digite 1 para user 1 e 2 para user 2: \n");
    // scanf("%s", esc);

    // // escArq(strcat(strcat(arquivo, esc), "/"));  Adiciona a escolha e "/" ao final de "user"

float lerVar(const char *arquivo, const char *variavel){
    FILE *arq = fopen(arquivo, "r");

    char linha[100];

    while(fgets(linha, sizeof(linha), arq)){
        char tmpVar[15];
        float tmpVal;

        if(sscanf(linha, "%[^ ] %f", tmpVar, &tmpVal) == 2){  // %[^ ] procura até o espaço, %d lê o valor da variável
            if(strcmp(tmpVar, variavel) == 0){
                fclose(arq);
                return tmpVal;
            }
        }
    }
    return 0;
}

int lerVarInt(const char *arquivo, const char *variavel){
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
    int nao = login();
    printf("%d", nao);
    
    return 0;
}
