#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DONE (0)
void menu();
void clr();

int ex1(char * str){
    int qtd_v = 0;

    for(int c = 0; c < strlen(str); c++){
        str[c] = tolower(str[c]);
        if(str[c] == 'a' || str[c] == 'e' || str[c] == 'i' || str[c] == 'o' || str[c] == 'u')
            qtd_v++;
    }

    return qtd_v;
}

void ex2(){
    char str1[] = "i o pintinho piu";
    char * str2 = (char*) malloc(sizeof(char) * strlen(str1) + 1);

    strcpy(str2, str1);
    puts(str2);
}

void ex3(){
    char str1[] = "hello, ";
    char str2[] = "world!";

    char *str = (char*) malloc((strlen(str1) + strlen(str2) + 1) * sizeof(char));

    strcpy(str, str1);
    strcat(str, str2);

    puts(str);
}

void ex4(){
    char * path = "./arquivo.txt";
    char str[20];

    printf("Digite algo: ");
    fgets(str, 20, stdin);

    FILE * file = fopen(path, "w");
    if(file == NULL){
        printf("Erro ao abrir o arquivo: %s\n", path);
        return;
    }

    fputs(str, file);
    
    fclose(file);
}

int main(int argc, char ** argv) {
    int choice;
    char str[] = "o rato roeu a roupa do rei de roma";
    
    do{
        menu();
        scanf("%i%*c", &choice);
        clr();
        
        switch(choice){
            case 1: 
                printf("O numero de vogais da string \"%s\" é: %d", str, ex1(str));
                break;
            case 2:
                ex2();
                break;
            case 3:
                ex3();
                break;
            case 4:
                ex4();
                break;
            case 0:
                printf("Gubay 🤙");
                break;
            default:
                printf("opcao invalida");
                break;
        }
    } while(choice != 0);
    return DONE;
}

void menu(){
    printf("\n");
    printf("Escolha um exercicio: \n");
    printf("1. Vogais\n");
    printf("2. Copiar\n");
    printf("3. Concatenar\n");
    printf("4. Arquivo\n");
    printf("0. Sair\n");
    printf("\n");
}

void clr() {
#ifdef __unix__
  system("clear");
#elif
  system("cls");
#endif
}