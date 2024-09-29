#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int lerVarInt(const char *, const char *);
float lerVar(const char *, const char *);
void escVar(const char *, const char *, float);
void escExt(float, char *, int, int);
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
    snprintf(arquivo, sizeof(arquivo), "user%d/dados.txt", user);
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

void depReais(int user){
    float valor;
    char arquivo[25];
    printf("Digite o valor a ser depositado: ");
    scanf("%f", &valor);
    snprintf(arquivo, sizeof(arquivo), "user%d/dados.txt", user);
    escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo")) + valor);
    printf("Deposito realizado com sucesso!! Saldo atual: %f\n", lerVar(arquivo, "rSaldo"));
    escExt(valor, "r", 1, user);
    menu(user);
}

void sacarReais(int user){
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

    float valor;
    snprintf(arquivo, sizeof(arquivo), "user%d/dados.txt", user);
    while(1){
        printf("Digite o valor a ser sacado: ");
        scanf("%f", &valor);
        if(valor > lerVar(arquivo, "rSaldo")){
            printf("Saldo insuficiente!! Tente outro valor\n");
        } else{
            break;
        }
    }
    escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo")) - valor);
    printf("Saque realizado com sucesso!! Saldo atual: %f\n", lerVar(arquivo, "rSaldo"));
    escExt(valor, "r", 2, user);
    menu(user);
}

void compCrip(int user){
    float txBc = 1.02;
    float txEth = 1.01;
    float txRp = 1.01;

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

    int esc;
    float valor;
    snprintf(arquivo, sizeof(arquivo), "user%d/dados.txt", user);
    printf("Saldo disponivel: %.3f\n", lerVar(arquivo, "rSaldo"));
    printf("Criptomoedas disponiveis:\n");
    printf("1. Bitcoin\n"
    "2. Ethereum\n"
    "3. Ripple\n");
    printf("Digite sua escolha: ");
    scanf("%d", &esc);
    switch(esc){
        case 1:
            printf("Comprar Bitcoin\n");
            while(1){
                printf("Digite o valor em reais: ");
                scanf("%f", &valor);
                if(valor * txBc > lerVar(arquivo, "rSaldo")){
                    printf("Saldo insuficiente!! Digite outro\n");
                } else{
                    escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") - (valor * txBc)));
                    escVar(arquivo, "bcSaldo", (valor/(lerVar(arquivo, "bcCota"))));
                    escExt(valor/(lerVar(arquivo, "bcCota")), "bc", 3, user);
                    printf("Compra realizada com sucesso!!\n");
                    break;
                }
            }
            break;
        case 2:
            printf("Comprar Ethereum\n");
            while(1){
                printf("Digite o valor em reais: ");
                scanf("%f", &valor);
                if(valor * txEth > lerVar(arquivo, "rSaldo")){
                    printf("Saldo insuficiente!! Digite outro\n");
                } else{
                    escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") - (valor * txEth)));
                    escVar(arquivo, "ethSaldo", (valor/(lerVar(arquivo, "ethCota"))));
                    escExt(valor/(lerVar(arquivo, "ethCota")), "eth", 3, user);
                    printf("Compra realizada com sucesso!!\n");
                    break;
                }
            }
            break;
        case 3:
            printf("Comprar Ripple\n");
            while(1){
                printf("Digite o valor em reais: ");
                scanf("%f", &valor);
                if(valor * txRp > lerVar(arquivo, "rSaldo")){
                    printf("Saldo insuficiente!! Digite outro\n");
                } else{
                    escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") - (valor * txRp)));
                    escVar(arquivo, "rpSaldo", (valor/(lerVar(arquivo, "rpCota"))));
                    escExt(valor/(lerVar(arquivo, "rpCota")), "rp", 3, user);
                    printf("Compra realizada com sucesso!!\n");
                    break;
                }
            }
            break;
    }
    menu(user);
}

void venCrip(int user){
    float txBc = 0.03;
    float txEth = 0.02;
    float txRp = 0.01;

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

    int esc;
    float valor;
    float tmp;
    snprintf(arquivo, sizeof(arquivo), "user%d/dados.txt", user);
    printf("Saldo de Bitcoin: %.3f\n", lerVar(arquivo, "bcSaldo"));
    printf("Saldo de Ethereum: %.3f\n", lerVar(arquivo, "ethSaldo"));
    printf("Saldo de Ripple: %.3f\n", lerVar(arquivo, "rpSaldo"));
    printf("Criptomoedas disponiveis:\n");
    printf("1. Bitcoin\n"
    "2. Ethereum\n"
    "3. Ripple\n");
    printf("Digite sua escolha: ");
    scanf("%d", &esc);
    switch(esc){
        case 1:
            printf("Vender Bitcoin\n");
            while(1){
                printf("Digite o valor em Bitcoin: ");
                scanf("%f", &valor);
                if(valor > lerVar(arquivo, "bcSaldo")){
                    printf("Saldo insuficiente!! Digite outro\n");
                } else{
                    tmp = valor * lerVar(arquivo, "bcCota");
                    escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") + (tmp - (tmp * txBc))));
                    escVar(arquivo, "bcSaldo", (lerVar(arquivo, "bcSaldo")) - valor);
                    escExt((lerVar(arquivo, "bcSaldo")) - valor, "bc", 4, user);
                    printf("Venda realizada com sucesso!!\n");
                    break;
                }
            }
            break;
        case 2:
            printf("Vender Ethereum\n");
            while(1){
                printf("Digite o valor em Ethereum: ");
                scanf("%f", &valor);
                if(valor > lerVar(arquivo, "ethSaldo")){
                    printf("Saldo insuficiente!! Digite outro\n");
                } else{
                    tmp = valor * lerVar(arquivo, "ethCota");
                    escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") + (tmp - (tmp * txEth))));
                    escVar(arquivo, "ethSaldo", (lerVar(arquivo, "ethSaldo")) - valor);
                    escExt((lerVar(arquivo, "ethSaldo")) - valor, "eth", 4, user);
                    printf("Venda realizada com sucesso!!\n");
                    break;
                }
            }
            break;
        case 3:
            printf("Vender Ripple\n");
            while(1){
                printf("Digite o valor em Ripple: ");
                scanf("%f", &valor);
                if(valor > lerVar(arquivo, "rpSaldo")){
                    printf("Saldo insuficiente!! Digite outro\n");
                } else{
                    tmp = valor * lerVar(arquivo, "rpCota");
                    escVar(arquivo, "rSaldo", (lerVar(arquivo, "rSaldo") + (tmp - (tmp * txRp))));
                    escVar(arquivo, "rpSaldo", (lerVar(arquivo, "rpSaldo")) - valor);
                    escExt((lerVar(arquivo, "rpSaldo")) - valor, "rp", 4, user);
                    printf("Venda realizada com sucesso!!\n");
                    break;
                }
            }
            break;
    }
    menu(user);
}

void atualizar(int user){
    float valor = (float)rand() / (float)RAND_MAX;
    
    valor = (valor * 0.1) + 0.95;
    char arquivo[25];
    for(int i = 1; i <= 10; i++){
        snprintf(arquivo, sizeof(arquivo), "user%d/dados.txt", i);
        escVar(arquivo, "bcCota", (lerVar(arquivo, "bcCota")) * valor);
        escVar(arquivo, "ethCota", (lerVar(arquivo, "ethCota")) * valor);
        escVar(arquivo, "rpCota", (lerVar(arquivo, "rpCota")) * valor);
    }
    printf("Cotas atualizadas com sucesso!!");
    menu(user);
}

void escExt(float valor, char moeda[], int operacao, int user){ // operacao = 1 pra depositar, 2 pra sacar, 3 pra comprar, 4 pra vender
    char arquivo[25];
    snprintf(arquivo, sizeof(arquivo), "user%d/extrato.txt", user);

    FILE *arq = fopen(arquivo, "a");

    if(arq == NULL){
        printf("erro\n");
    }

    time_t t;
    time(&t); // le o horario atual pra imprimir o extrato
    
    switch(operacao){
        case 1:
            if(strcmp(moeda, "r") == 0){
                fprintf(arq, "Depositados %.3f em Reais na data %s", valor, ctime(&t));
            } else if(strcmp(moeda, "bc") == 0){
                fprintf(arq, "Depositados %.3f em BitCoin na data %s", valor, ctime(&t));
            } else if(strcmp(moeda, "eth") == 0){
                fprintf(arq, "Depositados %.3f em Ethereum na data %s", valor, ctime(&t));
            } else{
                fprintf(arq, "Depositados %.3f em Ripple na data %s", valor, ctime(&t));
            }
            break;
        case 2:
            if(strcmp(moeda, "r") == 0){
                fprintf(arq, "Sacados %.3f em Reais na data %s", valor, ctime(&t));
            } else if(strcmp(moeda, "bc") == 0){
                fprintf(arq, "Sacados %.3f em BitCoin na data %s", valor, ctime(&t));
            } else if(strcmp(moeda, "eth") == 0){
                fprintf(arq, "Sacados %.3f em Ethereum na data %s", valor, ctime(&t));
            } else{
                fprintf(arq, "Sacados %.3f em Ripple na data %s", valor, ctime(&t));
            }
            break;
        case 3:
            if(strcmp(moeda, "bc") == 0){
                fprintf(arq, "Comprados %.3f em BitCoin na data %s", valor, ctime(&t));
            } else if(strcmp(moeda, "eth") == 0){
                fprintf(arq, "Comprados %.3f em Ethereum na data %s", valor, ctime(&t));
            } else{
                fprintf(arq, "Comprados %.3f em Ripple na data %s", valor, ctime(&t));
            }
            break;
        case 4:
            if(strcmp(moeda, "bc") == 0){
                fprintf(arq, "Vendidos %.3f em BitCoin na data %s", valor, ctime(&t));
            } else if(strcmp(moeda, "eth") == 0){
                fprintf(arq, "Vendidos %.3f em Ethereum na data %s", valor, ctime(&t));
            } else{
                fprintf(arq, "Vendidos %.3f em Ripple na data %s", valor, ctime(&t));
            }
            break;
    }
    fclose(arq);
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
    char buffer[200] = "";

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
    
    printf("----------------------------------------\n");
    printf("Menu:\n");
    printf("1. Consultar Saldo\n"
    "2. Consultar Extrato\n"
    "3. Depositar Reais\n"
    "4. Sacar Reais\n"
    "5. Comprar Criptomoedas\n"
    "6. Vender Criptomoedas\n"
    "7. Atualizar Cotacao\n"
    "8. Sair\n");
    printf("----------------------------------------\n");
    printf("Digite sua escolha: ");
    scanf("%d", &esc);
    switch(esc){
        case 1:
            consSaldo(user);
            break;
        case 2:
            consExt(user);
            break;
        case 3:
            depReais(user);
            break;
        case 4:
            sacarReais(user);
            break;
        case 5:
            compCrip(user);
            break;
        case 6:
            venCrip(user);
        case 7:
            atualizar(user);
        case 8:
            printf("Saindo do programa, tchau!!!!");
            exit(0);
    }
}

int main(){
    srand((unsigned int)time(NULL));
    int user = login();
    menu(user);
    
    return 0;
}
