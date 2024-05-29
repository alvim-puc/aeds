#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DONE (0)
#define TAMM6 (3)
#define MAX_CLIENTES (50)
void menu();
void clr();
bool isPrime(int n);
void draw(int spaces, char symbol);
void losango(int n, int row);
void matrixSum(int l, int c, int *sum, int m[TAMM6][TAMM6]);
typedef struct {
  char nome[30], email[30];
  int cpf, tel;
} Cliente;


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

void ex05(){
  int n;

  printf("Digite o tamanho do losangulo: ");
  scanf("%d", &n);
  losango((n * 2 - 1), 1);

}

void ex06(){
  int m[TAMM6][TAMM6];
  int sum = 0;

  FILE * f = fopen("./files/arq_matrix.txt", "w");
  if (!f) return;

  for (int i = 0; i < TAMM6; i++){
    for (int j = 0; j < TAMM6; j++){
      scanf("%d", &m[i][j]);
      fprintf(f, "%d ", m[i][j]);
      m[i][j] = 0;
    }
    fprintf(f, "\n");
  }

  fclose(f);

  matrixSum(-1, 0, &sum, m);

  printf("Soma das celulas da matriz: %d", sum);
}

void ex07() {
  int escolha, tamanho = 0;
  Cliente *clientes = (Cliente*) malloc(sizeof(Cliente) * MAX_CLIENTES);
  int cpf, tel;
  char nome[30], email[30];

  do {
    printf("\n");
    printf("Loja do seu Souza: \nOpcoes:\n");
    printf("01. Ver clientes\n");
    printf("02. Adicionar cliente\n");
    printf("03. Remover cliente\n");
    printf("04. Buscar cliente\n");
    printf("00. sair\n");
    printf("\n");
    scanf("%d%*c", &escolha);
    clr();
    switch (escolha) {
      case 1:
        for (int i = 0; i < tamanho; i++) {
          printf("\nCliente %d\n", i+1);
          printf("\nNome: %s\nCPF: %i\nTelefone: %i\nEmail: %s\n\n", clientes[i].nome, clientes[i].cpf, clientes[i].tel, clientes[i].email);
        }
        break;   
      case 2:
        if (tamanho < MAX_CLIENTES) {
          printf("Nome: ");
          fgets(nome, 30, stdin);
          nome[strcspn(nome, "\n")] = '\0';

          printf("CPF: ");
          scanf("%i%*c", &cpf);

          printf("Email: ");
          fgets(email, 30, stdin);
          email[strcspn(email, "\n")] = '\0';

          printf("Telefone: ");
          scanf("%i%*c", &tel);

          clientes[tamanho].cpf = cpf;
          clientes[tamanho].tel = tel;
          strncpy(clientes[tamanho].nome, nome, 30);
          strncpy(clientes[tamanho].email, email, 30);
          tamanho++;

        } else printf("Máximo de clientes alcançado.\n");
        break;
      case 3:
        printf("CPF do cliente a ser removido: ");
        scanf("%i%*c", &cpf);
        bool found = false;
        for (int i = 0; i < tamanho; i++) {
          if (clientes[i].cpf == cpf) {
            found = true;
            for (int j = i; j < tamanho - 1; j++) {
              clientes[j] = clientes[j + 1];
            }
            tamanho--;
            clientes = (Cliente*) realloc(clientes, sizeof(Cliente) * tamanho);
            printf("Cliente removido com sucesso.\n");
            break;
          }
        }
        if (!found)printf("Cliente não encontrado.\n");
        break;
      case 4:
        printf("CPF do cliente para busca-lo: ");
        scanf("%i%*c", &cpf);
        found = false;
        for (int i = 0; i < tamanho; i++) {
          if (clientes[i].cpf == cpf) {
            found = true;
            printf("Nome: %s\nCPF: %i\nTelefone: %i\nEmail: %s\n", clientes[i].nome, clientes[i].cpf, clientes[i].tel, clientes[i].email);
            break;
          }
        }
        if (!found) printf("Cliente não encontrado.\n");
        break;
      case 0:
        free(clientes);
        return;
      default:
        printf("Opção inválida.\n");
        break;
    }
  } while (escolha != 0);

  free(clientes);
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
          ex05();
          break;
        case 6:
          ex06();
          break;
        case 7:
          ex07();
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
    printf("03. Matrix Dinamica\n");
    printf("04. Primos dinamicos\n");
    printf("05. Losango\n");
    printf("06. Matrix File\n");
    printf("07. Soma\n");
    printf("08. toUpper\n");
    printf("09. Caça\n");
    printf("10. Grupos\n");
    printf("00. Sair\n");
    printf("\n");
}

void clr() {
  #ifdef __unix__
    system("clear");
  #else
    system("cls");
  #endif
}

bool isPrime(int n) {
  if (n <= 1) return false;

  for(int i = 2; i < n; i++){
    if(n % i == 0) return false;
  }

  return true;
}

void draw(int spaces, char symbol) {
  if(spaces <= 0) return;
  else {
    printf("%c", symbol);
    draw(spaces - 1, symbol);
  }
}

void losango(int n, int row) {
  if (row <= 0 || row > n) {
    return;
  }

  if(row == 1 || row == n){
    draw(n - 1, ' ');
    printf("*\n");
    losango(n, row + 1);
  }

  else if(row > 1 && row <= n / 2 + 1){
    draw(n - row, ' ');
    draw(row * 2 - 1, '*');
    printf("\n");
    losango(n, row + 1);
  }

  else if(row > n / 2 && row <= n){
    draw(row - 1, ' ');
    draw((n - row) * 2 + 1, '*');
    printf("\n");
    losango(n, row + 1);
  }
}

void matrixSum(int l, int c, int *sum, int m[TAMM6][TAMM6]) {
  if (l == -1) {
    FILE *f = fopen("./files/arq_matrix.txt", "r");
    if (!f) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    clr();
    for (int i = 0; i < TAMM6; i++) {
        for (int j = 0; j < TAMM6; j++) {
            fscanf(f, "%d", &m[i][j]);
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    fclose(f);

    matrixSum(0, c, sum, m);
    return; // por algum motivo aleatório esse return evita da recursão ocorrer mais doq o necessário (vlw gepeto)
  }

  if (l >= TAMM6) return;

  if (c == TAMM6) {
    c = 0;
    l += 1;

    matrixSum(l, c, sum, m);
  } 
  
  else {
    *sum += m[l][c];
    matrixSum(l, c + 1, sum, m);
  }
}
