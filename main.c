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
    Historico historico[TAMCONTA];

typedef struct{
    int data; //dia, mes, ano
    Conta conta;
    Historico historico;
    float valor;
    char complemento[100];
}Movimentacao;
    Movimentacao movimentacao[TAMCONTA];

    int contascadastradasG = 0, contmovDeb = 0, contmovCred = 0;

void CadastroConta();
void AcessarConta();
void Operacao();
void FuncMovimentacaoCred();
void FuncMovimentacaoDeb();

int main(){
    int opcao;
    setlocale(LC_ALL, "Portuguese");

        do{
            printf("\n\t -------------- Fluxo de Caixa --------------\n");
            printf("\n\t1 - Cadastro: ");
            printf("\n\t2 - Acessar Conta: ");
            printf("\n\t3 - Efetuar Operação");
            printf("\n\t4 - Sair");
            printf("\n\t\t Escolha uma opção: ");
            scanf("%d", &opcao);
            setbuf(stdin, NULL);

            switch(opcao){

                case 1: CadastroConta(); break;
                case 2: AcessarConta(); break;
                case 3: Operacao(); break;
                case 4: printf("\n Saindo..."); break;
                default: printf("\nOpçao inválida !! "); break;
            }
        }while(opcao != 4);
    return 0;
}

void CadastroConta(){
    int codigo;
    char descricao[100];

    printf("\n Digite o codigo da conta: ");
	scanf("%d", &codigo);
	setbuf(stdin, NULL);

	printf("\n Digite a descricao da conta: ");
	scanf("%s", &descricao);
	setbuf(stdin, NULL);

	conta[contascadastradasG].codigo = codigo;
	strcpy(conta[contascadastradasG].descricao, descricao);
	contascadastradasG++; //Incremento de quantas contas serão cadastradas
}

void AcessarConta(){

    int codigo, LINHA;
    int pos = contascadastradasG;
    printf("Digite o codigo da conta: ");
    scanf("%d", &codigo);

    for(LINHA = 0; LINHA < pos; LINHA++){
        if(codigo == conta[LINHA].codigo){
                printf("\n\t>>>>>> Dados Da conta <<<<<< \n");
         printf("\nConta: %d", conta[LINHA].codigo);
         printf("\nDescrição: %s", conta[LINHA].descricao);
         printf("\nSaldo: %0.2f", movimentacao[LINHA].valor);
        }
    }
}

void Operacao(){
    char operacao;

    printf("Tipo de operação: ");
    printf("D - Débito || C - Credito: ");
    scanf("%c", &operacao);


    switch(operacao){

        case 'D': FuncMovimentacaoDeb(); break;
        case 'C': FuncMovimentacaoCred(); break;
        default: printf("Opção invlida... "); break;
    }
}

void FuncMovimentacaoDeb(){
    int data;
    float valor;
    char descricao[100];

    /*printf("\nDia: ");
    scanf("%d", &data);*/
    printf("Valor: ");
    scanf("%f", &valor);
    printf("O que foi feito: ");
    scanf("%s", &descricao);

    movimentacao[contmovDeb].valor = movimentacao[contmovDeb].valor - valor;
    strcpy(movimentacao[contmovDeb].complemento, descricao);

    contmovDeb++;
}

void FuncMovimentacaoCred(){
    int data;
    float valor;
    char descricao[100];

    /*printf("\nDia: ");
    scanf("%d", &data);*/
    printf("Valor: ");
    scanf("%f", &valor);
    printf("O que foi feito: ");
    scanf("%s", &descricao);

    movimentacao[contmovCred].valor = movimentacao[contmovCred].valor + valor;
    strcpy(movimentacao[contmovCred].complemento, descricao);

    contmovCred++;
}
