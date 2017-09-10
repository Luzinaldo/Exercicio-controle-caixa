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
    char tipo; //Credito ou Debito
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

    int contascadastradasG = 0, contmovDeb = 0, contmovCred = 0, cont_operacao = 0;

void CadastroConta();
void AcessarConta();
void Operacao();
void FuncMovimentacaoCred();
void FuncMovimentacaoDeb();
void ListarMovContaEspecif();

int main(){
    int opcao;
    setlocale(LC_ALL, "Portuguese");

        do{
            printf("\n\t -------------- Fluxo de Caixa --------------\n");
            printf("\n\t1 - Cadastro: ");
            printf("\n\t2 - Acessar Conta: ");
            printf("\n\t3 - Efetuar Operação");
            printf("\n\t4 - Listar Movimentações");
            printf("\n\t5 - Sair");
            printf("\n\t\t Escolha uma opção: ");
            scanf("%d", &opcao);
            setbuf(stdin, NULL);

            switch(opcao){

                case 1: CadastroConta(); break;
                case 2: AcessarConta(); break;
                case 3: Operacao(); break;
                case 4: ListarMovContaEspecif(); break;
                case 5: printf("\n Saindo..."); break;
                default: printf("\nOpçao inválida !! "); break;
            }
        }while(opcao != 5);
    return 0;
}

void CadastroConta(){
    int codigo;
    char descricao[100];

    printf("\nDigite o codigo da conta: ");
	scanf("%d", &codigo);
	setbuf(stdin, NULL);

	printf("Digite a descricao da conta: ");
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
         break;
        }else if(codigo != conta[LINHA].codigo){
            printf("\n\t>>    Essa conta não existe    <<\n");
            printf("\t---------------------------------\n");
            break;
        }
    }
}

void Operacao(){
    setlocale(LC_ALL, "Portuguese");
    char operacao;

    printf("Tipo de operação: ");
    printf("D - Débito || C - Credito: ");
    scanf("%c", &operacao);

    historico[cont_operacao].tipo = operacao;

    switch(historico[cont_operacao].tipo){

        case 'D': FuncMovimentacaoDeb(); break;
        case 'C': FuncMovimentacaoCred(); break;
        default: printf("TIPO DE OPERAÇÃO INVÁLIDA ");
    cont_operacao++;
    }
}

void FuncMovimentacaoDeb(){
    int data, codigo, LINHA, pos;
    float valor;
    char descricao[100];

        printf("\n\t Informe o codigo da conta: ");
        scanf("%d", &codigo);
    for(LINHA = 0; LINHA < contascadastradasG; LINHA++){
        if(codigo == conta[LINHA].codigo){
            /*printf("\nDia: ");
            scanf("%d", &data);*/
            printf("Valor: ");
            scanf("%f", &valor);
            printf("O que foi feito: ");
            scanf("%s", &descricao);

            movimentacao[LINHA].valor = movimentacao[LINHA].valor - valor;
            strcpy(movimentacao[LINHA].complemento, descricao);
        }
    }

    contmovDeb++;
}

void FuncMovimentacaoCred(){
    int /*data*/codigo, LINHA;
    float valor;
    char descricao[100];

        printf("\n\t Informe o codigo da conta: ");
        scanf("%d", &codigo);
    for(LINHA = 0; LINHA < contascadastradasG; LINHA++){
        if(codigo == conta[LINHA].codigo){

            /*printf("\nDia: ");
            scanf("%d", &data);*/
            printf("Valor: ");
            scanf("%f", &valor);
            printf("O que foi feito: ");
            scanf("%s", &descricao);

            movimentacao[LINHA].valor = movimentacao[LINHA].valor + valor;
            strcpy(movimentacao[LINHA].complemento, descricao);
        }
    }
    contmovCred++;
}

void ListarMovContaEspecif(){
    int codigo, LINHA, pos = contmovCred + contmovDeb;

    printf("Digite o codigo da conta: ");
    scanf("%d", &codigo);

    printf("\n\n POS: %d", pos);

    for(LINHA = 0; LINHA < pos; LINHA++){
        if(codigo == conta[LINHA].codigo){
                                    printf("\n\t\t Listagem de Movimentação da sua conta ");
            printf("\n\t Movimentações %d -- Conta: %d -- Descrição da conta: %s ", LINHA+1, conta[LINHA].codigo, conta[LINHA].descricao);
            printf("\n\t Descrição: %s", movimentacao[LINHA].complemento);
            printf("\n\t Tipo da Movimentação: %c", historico[LINHA].tipo);
            printf("\n\t Valor da movimentação: %0.2f", movimentacao[LINHA].valor);
            printf("\n\n");
        }
    }
}
