#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"


void abertura(){
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

int jachutou(char letra, char chutes[26], int chutesdados){
    int achou = 0;
    //a letra ja foi chutada?
    for(int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

int acertou(char palavra_secreta[TAMANHO_PALAVRA], char chutes[26], int chutesdados){
    for(int i = 0; i < strlen(palavra_secreta); i++){
        if (!jachutou(palavra_secreta[i], chutes, chutesdados)){
            return 0;
        }
    }
    return 1;
}

void chuta(char chutes[26], int* chutesdados){
    char chute;
    scanf (" %c", &chute);

    chutes[(*chutesdados)] = chute;
    (*chutesdados)++;
}

void desenhaforca(char palavra_secreta[TAMANHO_PALAVRA], char chutes[26], int chutesdados){
    //imprimi a palavra secreta
    int erros = chuteserrados(chutes, chutesdados, palavra_secreta);

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), 
        (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), 
        (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), 
        (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
    
    for(int i = 0; i < strlen(palavra_secreta); i++){
            
        int achou = jachutou(palavra_secreta[i], chutes, chutesdados);
            
        if (achou){
            printf("%c ", palavra_secreta[i]);
        } else{
        printf("_ ");
        }
    }
    printf("\n");
}

void escolhepalavra(char palavra_secreta[TAMANHO_PALAVRA]){
    FILE* f;
    f = fopen("palavras.txt", "r");

    // verificando se o arquivo nao abriu
    if (f == 0){
        printf("Desculpe, banco de dados indisponivel\n\n\n");
        exit(1);
    }

    int qtdpalavras;
    fscanf(f, "%d", &qtdpalavras);

    srand(time(0));
    int randomico = rand() % qtdpalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavra_secreta);
    }

    fclose(f);
}

int chuteserrados(char chutes[26], int chutesdados, char palavra_secreta[TAMANHO_PALAVRA]){
    int erros = 0;
    
    for (int i =0; i < chutesdados; i++){
        int existe = 0;
        for (int j=0; j < strlen(palavra_secreta); j++){
            if (chutes[i] == palavra_secreta[j]){
                existe = 1;
                break;
            }
        }
        if (!existe) erros++;
    }
    // se tivermos mais do que 5 erros, retornamos 1
    // caso contrario, retornamos 0.
    return erros;
}

int enforcou(char chutes[26], int chutesdados, char palavra_secreta[TAMANHO_PALAVRA]) {
    return chuteserrados(chutes, chutesdados,palavra_secreta) >= 5;
}


void adiciona_palavra(){
    char quer;
    printf ("Voce deseja adicionar uma nova palavra no jogo? (S/N)");
    scanf(" %c", &quer);

    if (quer == 'S'){
        char nova_palavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra? ");
        scanf("%s", nova_palavra);

        FILE * f;
        f = fopen("palavras.txt", "r+");

        if (f == 0){
           printf("Desculpe, banco de dados indisponivel\n\n\n");
        exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", nova_palavra);

        fclose(f);
    }
}

int main(){
    
    char palavra_secreta[TAMANHO_PALAVRA];

    //declarando para que fique como booleano

    char chutes[26];
    int chutesdados = 0;
    
    escolhepalavra(palavra_secreta);

    abertura();

    do{
        desenhaforca(palavra_secreta, chutes, chutesdados);

        chuta(chutes, &chutesdados);

    } while(!acertou(palavra_secreta, chutes, chutesdados) && !enforcou(chutes,chutesdados, palavra_secreta));

    if(acertou(palavra_secreta, chutes, chutesdados)){
        printf("\nParabens vc acertou!\n\n");
    } else{
        printf("\nA palavra secreta era: %s\n\n", palavra_secreta);
    }
    
    adiciona_palavra();
}