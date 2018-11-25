#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Estrutura de uma música.
typedef struct {
    int enable;
    int saved_before;
    char title[30];
    char author[30];
    char album[30];
    char duration[6];
} music;
// Criando o vetor do tipo music.
music musics[1024];

// Menu da aplicação.
int menu(void);
// Cadastra uma nova música.
int create(int n);
// Salva os dados do vetor no arquivo.
int save(char txt[], int n);
// Carrega as informações do arquivo no vetor.
int load(char txt[]);
// Imprime o vetor de músicas.
void show(int n);
// Deleta uma música.
int delete(int n);
// Procura uma música na lista.
int search(char title[50], int n);
// Função responsável por retornar o número de músicas cadastradas.
int get_num_musics();
// Função responsável por atualizar o número de músicas cadastradas.
void set_num_musics(int num);

void main(void){
    // Carregando as músicas salvas no arquivo.
    load("music.txt");
    // Carregando a quantidade de músicas armazenadas.
    int count = get_num_musics();
    // Guarda a escolha do usuário no menu.
    int choice = -1;
    // Quantidade de músicas deletadas.
    int d = 0;
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
                show(count);
                break;
            case 2:
                // Lista todas as músicas.
                show(count);
                break;
            case 4:
                if ( delete(count)  == -1)
                    printf("\n\nPlease type a valid value ! \n\n");
                d++;
                break;
        }
    }while(choice != 5);
    // Chamando a função que salva as músicas no arquivo.
    save("music.txt", count);
    // Salvando o número de músicas armazenadas no arquivo.
    set_num_musics(count - d);
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
        fflush(stdin);
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
    // Indica se essa música já foi salva antes.
    musics[n].saved_before = 0;
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
    fgets(musics[n].duration, 6, stdin);
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
        if(musics[i].enable == 1){
            fprintf(archive, "%s", musics[i].title);
            fprintf(archive, "%s", musics[i].author);
            fprintf(archive, "%s", musics[i].album);
            fprintf(archive, "%s", musics[i].duration);
            // Só salva com o espaçamento se ela ainda não foi salva no arquivo.
            if(musics[i].saved_before == 0){
                fprintf(archive, "%d", 1);
                fprintf(archive, "%s", "\n\n");
            }else{
                fprintf(archive, "%d", 1);
            }
        }
    }
    // Fechando o arquivo.
    fclose(archive);
    // Tudo certo, nada mudoouu
    return 1;
}

// Carrega as dados do arquivo.
int load(char txt[]){
   FILE *archive;
   char l[30];
   int i, k = 0;
   // Abrindo o arquivo.
   archive = fopen(txt,"r");
   // Verificando se o arquivo existe.
   if (archive == NULL){
        printf("Erro! Impossivel abrir o arquivo!\n");
        exit(1);
   }
   // Lendo os dados do arquivo e salvando no vetor.
   while(!feof(archive)){
       musics[i].enable = 1;
       fgets(musics[i].title, 30, archive);
       fgets(musics[i].author, 30, archive);
       fgets(musics[i].album, 30, archive);
       fgets(musics[i].duration, 6, archive);
       fgets(l, 30, archive);
       fscanf(archive, "%d", k);
       i++;
   }
   fclose(archive);
   return 0;
}

// Imprime o vetor com as músicas.
void show(int n){
    printf("\n\n\n-=-=-=-=-=-=-=-=-=-= Musicas cadastradas -=-=-=-=-=-=-=-=-=-=\n\n\n");
    for(int i = 0; i < n; i++){
        if(musics[i].enable == 1 || musics[i].enable == 0 ){
            printf("Enable: %d\n", musics[i].enable);
            printf("Title: %s", musics[i].title);
            printf("Author: %s", musics[i].author);
            printf("Album: %s", musics[i].album);
            printf("Duration: %s\n\n", musics[i].duration);
        }
    }
}

// Deleta uma música.
int delete(int n){
    // Guarda o índice da música que o jovem deseja deletar.
    int index;
    printf("Type the index of the song: ");
    // Lendo o índice da música informada pelo usuário.
    fflush(stdin);
    scanf("%d", &index);
    // Verificando se o índice informado existe .
    if(index > (n - 1)){
        return -1;
    }else{
        // Editando o status "enable" da música informada para false (0).
        musics[index].enable = 0;
    }
}

// Procura uma música na playlist.
int search(char title[50], int n){
    // Loop que percorre o vetor de músicas
    for(int i = 0; i < n; i++){
        // Verificando se a string procurada é igual ao título da música
        //printf("Comparando %s com %s : %d\n", musics[i].title, title, i);
        if ( strcmp(musics[i].title, strcat(title, "\n")) == 0 )
            // Retornando o índice da música que possui o nome informado
            return i;
    }
    // Deu ruim borracha.
    return -1;
}

// Retorna a quantidade de músicas já cadastradas na plataforma.
int get_num_musics(){
    FILE *archive;
    // Guarda a quantidade de músicas.
    int n;
    // Abrindo o arquivo com que guarda a quantidade de músicas cadastradas.
    archive = fopen("counter.txt", "r");
    // Lendo o valor e guardando na variável n.
    fscanf(archive, "%d", &n);
    // Fechando o arquivo.
    fclose(archive);
    // Retornando o valor.
    return n;
}

// Função responsável por atualizar o número de músicas cadastradas.
void set_num_musics(int num){
    FILE *archive;
    // Abrindo o arquivo em modo de edição.
    archive = fopen("counter.txt", "w");
    // Atualizando o valor do arquivo.
    fprintf(archive, "%d", num);
    // Fechando o arquivo.
    fclose(archive);
}
