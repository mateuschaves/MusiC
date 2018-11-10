#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Menu da aplicação.
int menu(void);

void main(void){
    do{
        printf("oiiiee \n");
    }while(menu() != 5);
    system("pause");
}

// Implementação da função menu().
int menu(void){
    // Guarda a escolha do usuário.
    int escolha = -1;
    printf("1 - Cadastrar musica.\n");
    printf("2 - Listar todas as musicas.\n");
    printf("3 - Editar musica.\n");
    printf("4 - Excluir musica.\n");
    printf("5 - Sair.\n");
    printf("Informe sua escolha: ");
    // Lendo a escolha do usuário e guardando em escolha.
    do{
        scanf("%d", &escolha);
        if(escolha > 5)
            printf("Informe uma escolha valida: ");
    }while(escolha > 5);
    // Retornando o valor escolhido.
    return escolha;
}