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

void ex01() {
  int m[3][3];
  int soma_diag1 = 0, soma_diag2, soma_lin = 0, soma_col = 0, i, j;

  for(i = 0; i <3; i++){
    for(j = 0; j <3; j++)
      scanf("%d", &m[i][j]);
  }

  for(i = 0; i <3; i++){
    soma_lin = 0;
    soma_col = 0;

    for(j = 0; j <3; j++){
      if(i == j) soma_diag1 += m[i][j];
      if(i == 3-1-j) soma_diag2 += m[i][3-1-j];
      soma_lin += m[i][j];
      soma_col += m[j][i];
    }

    if(soma_lin != 15 || soma_col != 15){
      printf("Matriz diferente de 15\nParando o programa\n");  
      return;
    }
  }

  if(soma_diag1 != 15 || soma_diag2 != 15) {
    printf("Diagonal diferente de 15\nParando o programa\n");
    return;
  }

  printf("Soma linhas: %d\nSoma colunas: %d\nSoma diagonal I: %d\nSoma diagonal II: %d\n", soma_lin, soma_col, soma_diag1, soma_diag2);
}

void ex02() {
  char m[10][20], p[20];

  for(int i = 0; i < 10; i++){
    fgets(p, 20, stdin);
    for(int j = 0; j < 20; j++)
      m[i][j] = p[j];
  }

  for (int i = 1; i < 10; i++) {
    for (int j = 1; j < 10; j++) {
        if(strcmp(m[j - 1], m[j]) > 0) {
          strcpy(p, m[j - 1]);
          strcpy(m[j - 1], m[j]);
          strcpy(m[j], p);
        }
    }
  }

  printf("\nLista ordenada alfabeticamente: \n");
  for(int i = 0; i < 10; i++) printf("%s", m[i]);

}

void ex03(){
  int ** m;
  m = (int **) malloc(sizeof(int) * 2);
  for (int i = 0; i < 2; i++) {
    m[i] = (int*)malloc(sizeof(int) * 2);
    for (int j = 0; j < 2; j++) {
      m[i][j] = (i + 1) + (j + 1);
    }
  }
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 2; j++)
      printf("%d ", m[i][j]);
    printf("\n");
  }

}

bool isPrime(int n) {
  if (n <= 1) return false;

  for(int i = 0; i < n; i++){
    if(n % i == 0) return false;
  }
  
  return true;
}

void ex04(){
  int * v;
  int tam, primes = 0;

  printf("Tamanho do vetor: ");
  scanf("%d", &tam);

  v = (int*) malloc(sizeof(int) * tam);

  for(int i = 2; primes < tam; i++){
    if(isPrime(i)){
      v[primes] = i;
      primes++;
    }
  }

  for(int i = 0; i < tam; i++)
    printf("%d ", v[i]);
  
  free(v);
}

int main(int argc, char ** argv) {
    int choice;
    
    do{
        menu();
        scanf("%i%*c", &choice);
        clr();
        switch(choice){
            case 1: 
                ex01();
                break;
            case 2:
                ex02();
                break;
            case 3:
                ex03();
                break;
            case 4:
            ex04();
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
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
    printf("01. Matriz 15\n");
    printf("02. Lista alfabetica\n");
    printf("03. Matriz Dinamica\n");
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