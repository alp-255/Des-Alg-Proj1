#include <stdio.h>
#include <string.h>
#include <time.h>

int lerVarInt(const char *, const char *);
float lerVar(const char *, const char *);
void escVar(const char *, const char *, float);
void escExt(float, char *, int);
void menu(int);


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
            printf("Login realizado com sucesso. Bem-vindo, usuario %d!\n", user);
            break;
        }
    }

    return user;
}

void consSaldo(int user){
    char arquivo[25];
    while(1){
        char senhaDigitada[10];
        printf("Informe sua senha: ");
        scanf("%s", senhaDigitada);
        char senhaArq[10];
        snprintf(arquivo, sizeof(arquivo), "user%d/cpfesenha.txt", user);
        int senhaInt = lerVarInt(arquivo, "senha");
        snprintf(senhaArq, sizeof(senhaArq), "%d", senhaInt);
        if(strcmp(senhaDigitada, senhaArq) != 0){
            printf("Senha incorreta!! Digite novamente\n");
        } else{
            break;
        }
    }
    printf("Saldo da sua conta: \n");
    printf("Reais: %.3f\n", lerVar(arquivo, "rSaldo"));
    printf("BitCoin: %.3f\n", lerVar(arquivo, "bcSaldo"));
    printf("Ethereum: %.3f\n", lerVar(arquivo, "ethSaldo"));
    printf("Ripple: %.3f\n", lerVar(arquivo, "rpSaldo"));
    menu(user);
}

void consExt(int user){
    char arquivo[25];
    while(1){
        char senhaDigitada[10];
        printf("Informe sua senha: ");
        scanf("%s", senhaDigitada);
        char senhaArq[10];
        snprintf(arquivo, sizeof(arquivo), "user%d/cpfesenha.txt", user);
        int senhaInt = lerVarInt(arquivo, "senha");
        snprintf(senhaArq, sizeof(senhaArq), "%d", senhaInt);
        if(strcmp(senhaDigitada, senhaArq) != 0){
            printf("Senha incorreta!! Digite novamente\n");
        } else{
            break;
        }
    }
    snprintf(arquivo, sizeof(arquivo), "user%d/extrato.txt", user);
    char linha[100];
    FILE *arq = fopen(arquivo, "r");
    printf("Extrato da sua conta: \n");
    while(fgets(linha, 100, arq) != NULL){
        printf("%s", linha);
    }
    fclose(arq);
    menu(user);
}

void escExt(float valor, char moeda[], int user){
    char arquivo[25];
    snprintf(arquivo, sizeof(arquivo), "user%d/extrato.txt", user);

    FILE *arq = fopen(arquivo, "a");

    if(arq == NULL){
        printf("erro\n");
    }

    time_t t;
    time(&t); // le o horario atual pra imprimir o extrato
    
    if(strcmp(moeda, "r") == 0){
        fprintf(arq, "Depositado %f em Reais na data %s", valor, ctime(&t));
    } else if(strcmp(moeda, "bc") == 0){
        fprintf(arq, "Depositado %f em BitCoin na data %s", valor, ctime(&t));
    } else if(strcmp(moeda, "eth") == 0){
        fprintf(arq, "Depositado %f em Ethereum na data %s", valor, ctime(&t));
    } else{
        fprintf(arq, "Depositado %f em Ripple na data %s", valor, ctime(&t));
    }
    
    fclose(arq);
    menu(user);
}

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

void menu(int user){
    int esc;
    
    printf("----------------------------------------");
    printf("Menu:\n");
    printf("1. Consultar Saldo\n"
    "2. Consultar Extrato\n"
    "3. Depositar Reais\n"
    "4. Sacar Reais\n"
    "5. Comprar Criptomoedas\n"
    "6. Vender Criptomoedas\n"
    "7. Atualizar Cotacao\n"
    "8. Sair\n");
    printf("----------------------------------------");
    printf("Digite sua escolha: ");
    scanf("%d", &esc);
    switch(esc){
        case 1:
            consSaldo(user);
            break;
        case 2:
            consExt(user);
            break;
    }
}

int main(){
    int user = login();
    menu(user);

    
    return 0;
}
