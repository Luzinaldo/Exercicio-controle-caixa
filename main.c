#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TAMCONTA 100

typedef struct{
    int codigo;
    char descricao[100];
}Conta;
    Conta conta[TAMCONTA];

typedef struct{
    int codigo;
    char descricao[100];
    int tipo; //Credito ou Debito
}Historico;
    Historico historico;

typedef struct{
    int data; //dia, mes, ano
    Conta conta;
    Historico historico;
    char complemento[100];
}Movimentacao;
    Movimentacao movimentacao;

int main(){



    return 0;
}
