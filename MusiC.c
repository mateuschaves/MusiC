#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Estrutura de uma música.
typedef struct {
    int enable;
    char title[30];
    char author[30];
    char album[25];
    float duration;
} music;
// Criando o vetor do tipo music.
music musics[1024];

// Menu da aplicação.
int menu(void);
// Cadastra uma nova música.
int create(int n);
// Salva os dados do vetor no arquivo.
int save(char txt[], int n);

void main(void){
    // Contador de músicas.
    int count = 0;
    // Guarda a escolha do usuário no menu.
    int choice = -1;
    // Loop com o menu da aplicação, condição de saída choice = 5.
    do{
        // Chamando a função do menu e guardando a escolha em choice.
        choice = menu();
        switch (choice)
        {
            case 1:
                // Chamando a função create.
                create(count);
                // Somando mais um no contador de músicas.
                count++;
                break;
        }
    }while(choice != 5);
    // Chamando a função que salva as músicas no arquivo.
    save("music.txt", count);
    system("pause");
}

// Implementação da função menu().
int menu(void){
    // Guarda a escolha do usuário.
    int choice = -1;
    printf("1 - Create music.\n");
    printf("2 - List all musics.\n");
    printf("3 - Update music.\n");
    printf("4 - Delete music.\n");
    printf("5 - Exit.\n");
    printf("Type your choice: ");
    // Lendo a escolha do usuário e guardando em choice.
    do{
        scanf("%d", &choice);
        if(choice > 5)
            printf("Informe uma escolha valida: ");
    }while(choice > 5);
    // Retornando o valor escolhido.
    return choice;
}
// Cadastra uma nova música.
int create(int n){
    // Estado inicial de uma música é ativa. enable = 1.
    musics[n].enable = 1;
    // Lendo as informações do teclado e salvando no vetor musicas.
    printf("Title: ");
    fflush(stdin);
    fgets(musics[n].title, 30, stdin);
    printf("Author: ");
    fflush(stdin);
    fgets(musics[n].author, 30, stdin);
    printf("Album: ");
    fflush(stdin);
    fgets(musics[n].album, 25, stdin);
    printf("Duration: ");
    fflush(stdin);
    scanf("%f", &musics[n].duration);
}

// Salva os dados no arquivo.
int save(char txt[], int n){
    FILE *archive;
    // Abrindo o arquivo.
    archive = fopen(txt, "w");
    // Arquivo não encontrado.
    if(archive == NULL){
        printf("Archive not found !");
        return 0;
    }
    // Escrevendo no arquivo as informações do vetor de músicas.
    for(int i = 0; i < n; i++){
        if(musics[i].enable){
            fprintf(archive, "%s", musics[i].title);
            fprintf(archive, "%s", musics[i].author);
            fprintf(archive, "%s", musics[i].album);
            fprintf(archive, "%.2f", musics[i].duration);
            fprintf(archive, "%s", "\n\n");
        }
    }
    // Fechando o arquivo.
    fclose(archive);
    // Tudo certo, nada mudoouu
    return 1;
}