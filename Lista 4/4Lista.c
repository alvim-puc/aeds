#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DONE (0)
#define ALPHABET_SIZE (26)
void menu();
void clr();
void cesarFile(char *inputFile, char *outputFile, char method);
char encryptChar(char ch);
char decryptChar(char ch);

void ex01(int **um, int **dois) {
    int aux;

    aux = *um;
    *um = *dois;
    *dois = aux;
}

void ex02(char* str1, char* str2) {
    char *str = (char*) malloc(sizeof(char) * (strlen(str2) + strlen(str1) + 1));

    strcpy(str, str1);
    strcat(str, str2);
    
    puts(str);
}

void ex03() {
    char * inputFile = "./files/lorem.txt";
    char * outputFile = "./files/vogals.txt";

    FILE *fin = fopen(inputFile, "r");
    if (fin == NULL) {
        printf("Error opening input file: %s\n", inputFile);
        return;
    }
    
    FILE *fout = fopen(outputFile, "w");
    if (fout == NULL) {
        printf("Error opening output file: %s\n", outputFile);
        fclose(fin);
        return;
    }

    int qtd_V = 0, qtd_v = 0;
    char c;
    while ((c = fgetc(fin)) != EOF) {
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            qtd_V++;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            qtd_v++;
    }

    fprintf(fout, "Quantidade de vogais \nMaiúsculas: %d \nMinúsculas: %d", qtd_V, qtd_v);
    
    fclose(fin);
    fclose(fout);
}

void ex04() {
    char* inputFile = "./files/icesar.txt";
    char* outputFile = "./files/iicesar.txt";

    cesarFile(inputFile, outputFile, 'e');
}

void ex05() {
    char* inputFile = "./files/iicesar.txt";
    char* outputFile = "./files/icesar.txt";

    cesarFile(inputFile, outputFile, 'd');
}

void ex06() {
    char * inputFile = "./files/lorem.txt";
    char * outputFile = "./files/charlen.txt";

    FILE *fin = fopen(inputFile, "r");
    if (fin == NULL) {
        printf("Error opening input file: %s\n", inputFile);
        return;
    }
    
    FILE *fout = fopen(outputFile, "w");
    if (fout == NULL) {
        printf("Error opening output file: %s\n", outputFile);
        fclose(fin);
        return;
    }

    int qtd_c = 0;
    char c;
    while ((c = fgetc(fin)) != EOF) qtd_c++;

    fprintf(fout, "Quantidade de caracteres: %d", qtd_c);
    
    fclose(fin);
    fclose(fout);
}

void ex07() {
    int * nums = (int *) malloc(sizeof(int) * 2);

    printf("Digite dois números: ");
    scanf("%d %d", &nums[0], &nums[1]);

    printf("Soma: %d", nums[0] + nums[1]);
}

void ex08() {
    char * str;
    int tam;

    printf("Digite o tamanho da string: ");
    scanf("%d%*c", &tam);

    printf("Digite uma string: ");
    str = (char *) malloc(sizeof(char) * (tam + 1));
    fgets(str, tam, stdin);
    
    for(int c = 0; c < tam; c++){
        str[c] = toupper(str[c]);
    }

    puts(str);
}

void ex09() {
    int tam;
    char * str;
    char alvo, bala;

    printf("Digite o tamanho da string: ");
    scanf("%d%*c", &tam);

    printf("Digite uma string: ");
    str = (char *) malloc(sizeof(char) * (tam + 1));
    fgets(str, tam, stdin);

    printf("Digite um caractere a ser caçado: ");
    scanf("%c%*c", &alvo);

    printf("Digite um caractere a abater o alvo: ");
    scanf("%c%*c", &bala);

    for(int c = 0; c < tam; c++){
        if(str[c] == alvo)
            str[c] = bala;
    }

    puts(str);
}

int ex10(int num) {
    return num % 2 == 0 ? 1 : 0;
}

int main(int argc, char ** argv) {
    int choice;
    int num;
    int * ptrNum;
    int* um = 10, *dois = 20;
    char str1[] = "olá, ", str2[] = "mundo!";
    
    do{
        menu();
        scanf("%i%*c", &choice);
        clr();
        switch(choice){
            case 1: 
                printf("um: %d, dois: %d\n", um, dois);
                ex01(&um, &dois);
                printf("um: %d, dois: %d\n", um, dois);
                break;
            case 2:
                ex02(str1, str2);
                break;
            case 3:
                ex03();
                break;
            case 4:
                ex04();
                break;
            case 5:
                ex05();
                break;
            case 6:
                ex06();
                break;
            case 7:
                ex07();
                break;
            case 8:
                ex08();
                break;
            case 9:
                ex09();
                break;
            case 10:
                printf("Digite um numero: ");
                scanf("%d%*c", &num);
                ptrNum = &num;
                printf("return: %d", ex10(*ptrNum));
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
    printf("01. Inverter\n");
    printf("02. Concatena\n");
    printf("03. Vogais\n");
    printf("04. Encrypt\n");
    printf("05. Decrypt\n");
    printf("06. Caracteres\n");
    printf("07. Soma\n");
    printf("08. toUpper\n");
    printf("09. Caça\n");
    printf("10. Grupos\n");
    printf("00. Even?\n");
    printf("\n");
}

void clr() {
  #ifdef __unix__
    system("clear");
  #else 
    system("cls");
  #endif
}

char encryptChar(char ch) {
  if (ch >= 'a' && ch <= 'z') {
    return ((ch - 'a') + 5) % ALPHABET_SIZE + 'a';
  } else if (ch >= 'A' && ch <= 'Z') {
    return ((ch - 'A') + 5) % ALPHABET_SIZE + 'A';
  } else {
    return ch;
  }
}

char decryptChar(char ch) {
  if (ch >= 'a' && ch <= 'z') {
    return ((ch - 'a') - 5 + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
  } else if (ch >= 'A' && ch <= 'Z') {
    return ((ch - 'A') - 5 + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
  } else {
    return ch;
  }
}

void cesarFile(char *inputFile, char *outputFile, char method) {
    FILE *fin = fopen(inputFile, "r");
    if (fin == NULL) {
        printf("Error opening input file: %s\n", inputFile);
        return;
    }
    
    FILE *fout = fopen(outputFile, "w");
    if (fout == NULL) {
        printf("Error opening output file: %s\n", outputFile);
        fclose(fin);
        return;
    }
    
    char c;
    while ((c = fgetc(fin)) != EOF) {
        fputc(method == 'e' ? encryptChar(c) : decryptChar(c), fout);
    }
    
    fclose(fin);
    fclose(fout);
}