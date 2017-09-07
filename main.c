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

    int contascadastradasG = 0;

int main(){
    int opcao;
    setlocale(LC_ALL, "Portuguese");

        do{
            printf("\n\t -------------------------- Gerenciamento de Contas --------------------------\n");
            printf("\n\t1 - Cadastro: ");


            printf("\n\t4 - Sair");
            printf("\n\t\t Escolha uma opção: ");
            scanf("%d", &opcao);

        }while(opcao =! 4);
    return 0;
}

void CadastroConta(){
    int codigo;
    char descricao;

    printf(" Digite codigo da conta ");
	scanf(" %d ", &codigo);
	setbuf(stdin, NULL);

	printf(" Digite descricao da conta ");
	scanf(" %s ", &descricao);
	setbuf(stdin, NULL);

	conta[contascadastradasG].codigo = codigo;
	strcpy(conta[contascadastradasG].descricao, descricao);

	contascadastradasG++;
}
