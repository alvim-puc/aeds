#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DONE (0)
#define SEQI (5)
#define WRDLEN (15)
#define STRLEN (30)
void menu();
void clr();

void ex01(int seq[SEQI]) {
  int qtdp = 0, qtdn = 0, qtdz = 0;

  printf("Sequencia: ");
  for (int i = 0; i < SEQI; i++) {
    printf("%d ", seq[i]);
    if (seq[i] < 0)
      qtdn++;
    if (seq[i] > 0)
      qtdp++;
    if (seq[i] == 0)
      qtdz++;
  }

  printf("\nPositivos: %d \nNegativos: %d \nZeros: %d \n", qtdp, qtdn, qtdz);
}


void ex02(int a, int b, int c) {
  int delta;
  float x1, x2;

  delta = pow(b, 2) - (4 * a * c);
  x1 = ((-b) + sqrt(delta)) / 2 * a;
  x2 = ((-b) - sqrt(delta)) / 2 * a;

  printf("x': %.1f \nx'': %.1f\n", x1, x2);
}


char *ex03(int x, int y) { 
    return (y % x == 0) ? "é" : "não é"; 
}


void ex04() {
  int qtd = 0;
  char p;

  scanf("%c", &p);

  if (tolower(p) == 't') {
    printf("Digite a quantidade de tortas que deseja: ");
    scanf("%d", &qtd);

    printf("Total a pagar comprando %d tortas: %dR$\n", qtd, qtd * 70);
  } else if (tolower(p) == 'f') {
    printf("Digite a quantidade de fatias de torta que deseja: ");
    scanf("%d", &qtd);

    printf("Total a pagar comprando %d fatias de torta: %dR$\n", qtd, qtd * 10);
  } else {
    printf("tente novamente.\n");
  }
}


void ex05(int ini, int fim){
    bool p;
    
    printf("Numeros primos entre %d e %d: ", ini, fim);
    for(ini; ini <= fim; ini++){
        p = true;
        for(int k = 2; ini > k; k++){
            if(ini % k == 0) {
                p = false; 
                break;
            }
        }
        if(p) printf("%d ", ini);
    }
    printf("\n");
}


void ex06(){
    char word[WRDLEN];
    char drow[WRDLEN];
    char tmp;

    fgets(word, WRDLEN, stdin);
    word[strlen(word) - 1] = '\0'; //troca o '\n' pelo '\0'

    strcpy(drow, word);

    //inverte a tring drow
    for(int i = 0, j = strlen(drow) - 1; i < j; i++, j--){
        tmp = drow[i];
        drow[i] = drow[j];
        drow[j] = tmp;
    }

    printf("A palavra \"%s\" %s um palindromo\n", word, (strcmp(word, drow) == 0) ? "é" : "não é");
}


void ex07(){
    char str[STRLEN];
    int qtd_vog = 0, qtd_con = 0;

    fgets(str, STRLEN, stdin);
    str[strlen(str) - 1] = '\0'; //troca o '\n' pelo '\0'

    for(int i = 0; i < strlen(str); i++){
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u') qtd_vog++;
        else qtd_con++;
    }

    printf("A frase \"%s\" possui %d vogais e %d consoantes\n", str, qtd_vog, qtd_con);
}


void ex08(int nums[SEQI + 1]){
    int res[SEQI+1];
    int rng;
    int equals = 0;
    bool already_exists;
    srand((unsigned)time(NULL));

    for(int i = 0; i < SEQI + 1; i++){
        rng = 1 + (rand() % 60);
        if(i == 0) res[i] = rng;
        else {
            already_exists = false;
            for(int j = 0; j < i; j++){
                if(res[j] == rng) {
                    already_exists = true;
                    break;
                }
            }
            // Se o número já existe, gera outro número
            if(already_exists) i--; // decrementa o índice para gerar outro número na próxima iteração
            else res[i] = rng;
        }
    }

    for(int i = 0; i < SEQI + 1; i++){
        for(int j = 0; j < SEQI + 1; j++){
            if(nums[i] == res[j]) equals++;
        }
    }
    printf("Total de correspondências: %d\n", equals);
    printf("Resultado: [ ");
    for(int i = 0; i < SEQI + 1; i++) printf("%d ", res[i]);
    printf("]\n");
}


void ex09(){
    int saldo = 1000;
    int opcao = -1;

    while (opcao != 0) {
        printf("\n----------------------------- \n");
        printf("\n    BANCO DO ALVINO ☝️ 🤓     \n");
        printf("\n------------------------------\n");
        printf("Selecione a operacao desejada:\n");
        printf("1. Verificar saldo\n");
        printf("2. Sacar dinheiro\n");
        printf("3. Depositar dinheiro\n");
        printf("0. Sair\n");

        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Seu saldo atual e: R$%d\n", saldo);
                break;
            case 2:
                printf("Digite o valor que deseja sacar: ");
                int saque;
                scanf("%d", &saque);
                if (saque > saldo) {
                    printf("Saldo insuficiente.\n");
                } else {
                    saldo -= saque;
                    printf("Voce sacou R$%d. \nSaldo restante: R$%d\n", saque, saldo);
                }
                break;
            case 3:
                printf("Digite o valor que deseja depositar: ");
                int deposito;
                scanf("%d", &deposito);
                saldo += deposito;
                printf("Voce depositou R$%d. \nSaldo atual: R$%d\n", deposito, saldo);
                break;
            case 0:
                printf("...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    }
}


void printWord(char *frc, char *res) {
    for (int i = 0; i < strlen(frc); i++) {
        if (res[i] != '\0') {
            printf("%c ", res[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void updateResult(char *frc, char *res, char guess) {
    for (int i = 0; i < strlen(frc); i++) {
        if (frc[i] == guess) {
            res[i] = guess;
        }
    }
}

void ex10(){
    char * frc = "antedeguemon";
    int qtd_er = 0;
    char res[WRDLEN-2];
    char r;

    //inicio
    printf("----\n");
    printf("|   \n");
    printf("|  \n");
    printf("|  \n");
    printf("/\\\n");
    for(int i = 0; i < WRDLEN-2; i++) printf("_ ");
    printf("\n");
    
    do{
        scanf(" %c", &r);
        getchar();
        clr();

        // Verifica se a letra está na palavra
        int found = 0;
        for (int i = 0; i < strlen(frc); i++) {
            if (frc[i] == r) {
                found = 1;
                break;
            }
        }

        if (found) {
            updateResult(frc, res, r);
        } else {
            qtd_er++;
        }

        if(qtd_er == 6){
            printf("----\n");
            printf("|   O\n");
            printf("|  /|\\\n");
            printf("|  /\\\n");
            printf("/\\\n");
        } else if (qtd_er == 5){
            printf("----\n");
            printf("|   O\n");
            printf("|  /|\\\n");
            printf("|  /\n");
            printf("/\\\n");
        } else if (qtd_er == 4){
            printf("----\n");
            printf("|   O\n");
            printf("|  /|\\\n");
            printf("|  \n");
            printf("/\\\n");
        } else if (qtd_er == 3){
            printf("----\n");
            printf("|   O\n");
            printf("|  /|\n");
            printf("|  \n");
            printf("/\\\n");
        } else if (qtd_er == 2){
            printf("----\n");
            printf("|   O\n");
            printf("|  /\n");
            printf("|  \n");
            printf("/\\\n");
        } else if (qtd_er == 1){
            printf("----\n");
            printf("|   O\n");
            printf("|  \n");
            printf("|  \n");
            printf("/\\\n");
        } else if (qtd_er == 0){
            printf("----\n");
            printf("|   \n");
            printf("|  \n");
            printf("|  \n");
            printf("/\\\n");
        }
        printWord(frc, res);
    }while(strcmp(frc, res) != 0 && qtd_er < 6);

    if (qtd_er == 6) {
        printf("You lost! The word was: %s\n", frc);
    } else {
        printf("Congratulations! You guessed the word.\n");
    }
}

int main(int argc, char **argv) {
  int seq[SEQI];
  int nums[SEQI+1];
  int a, b, c, x, y, ini, fim;
  int choice;

  do {
    menu();
    scanf("%i%*c", &choice);
    clr();
    switch (choice) {
    case 1:
      printf("Digite uma sequencia de 5 números: ");
      scanf("%d %d %d %d %d", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4]);
      ex01(seq);
      break;
    case 2:
      printf("Insira a, b e c: ");
      scanf("%d %d %d", &a, &b, &c);
      ex02(a, b, c);
      break;
    case 3:
      printf("Digite 2 números: ");
      scanf("%d %d", &x, &y);
      printf("%d %s divisor de %d\n", x, ex03(x, y), y);
      break;
    case 4:
      printf("Digite 't' para Torta ou 'f' para Fatia: ");
      ex04();
      break;
    case 5:
      printf("Informe o inicio e o fim de um intervalo: ");
      scanf("%d %d", &ini, &fim);
      ex05(ini, fim);
      break;
    case 6:
      printf("Escreva uma palavra: ");
      ex06();
      break;
    case 7:
      printf("Insira uma string: ");
      ex07();
      break;
    case 8:
      printf("Insira 6 numeros da sorte: ");
      scanf("%d %d %d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3], &nums[4], &nums[5]);
      ex08(nums);
      break;
    case 9:
      ex09();
      break;
    case 10:
      ex10();
      break;
    case 0:
      printf("Gubay 🤙");
      break;
    default:
      printf("opção inválida\n");
      break;
    }
  } while (choice != 0);

  return DONE;
}

void menu() {
  printf("\n");
  printf("01. Conjuntos\n");
  printf("02. Bhaskara\n");
  printf("03. Divisível?\n");
  printf("04. Padaria\n");
  printf("05. Primos\n");
  printf("06. Palindromo?\n");
  printf("07. Vogais X Consoantes\n");
  printf("08. Mega Sena\n");
  printf("09. Caixa Lotérica\n");
  printf("10. Forca\n");
  printf("00. Sair\n");
  printf("\n");
}

void clr() {
#ifdef __unix__
  system("clear");
#elif
  system("cls");
#endif
}