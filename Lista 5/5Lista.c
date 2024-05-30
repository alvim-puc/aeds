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

#define TAMM6 (3)
#define MAX_CLIENTES (50)
#define SIZE (3)

bool isPrime(int n);
void draw(int spaces, char symbol);
void losango(int n, int row);
void matrixSum(int l, int c, int *sum, int m[TAMM6][TAMM6]);
typedef struct {
  char nome[30], email[30];
  int cpf, tel;
} Cliente;
void printTable(int m[4][4], bool revealed[4][4], int l1, int c1, int l2, int c2);
bool palindromo(char * str, int y, int aux);
void printBoard(char board[SIZE][SIZE]);
bool checkWin(char board[SIZE][SIZE], char player);
void makeMove(char board[SIZE][SIZE], char player);

void ex01() {
  int m[3][3];
  int soma_diag1 = 0, soma_diag2 = 0, soma_lin = 0, soma_col = 0, i, j;

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
      printf("Linha/Coluna diferente de 15\n");
    }
  }

  if(soma_diag1 != 15 || soma_diag2 != 15) {
    printf("Diagonal diferente de 15\n");
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
  m = (int **) malloc(sizeof(int) * 6);
  for (int i = 0; i < 6; i++) {
    m[i] = (int*)malloc(sizeof(int) * 6);
    for (int j = 0; j < 6; j++) {
      m[i][j] = (i + 1) + (j + 1);
    }
  }
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++)
      printf("%d\t", m[i][j]);
    printf("\n\n");
  }

  free(m);
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
    printf("1. Ver clientes\n");
    printf("2. Adicionar cliente\n");
    printf("3. Remover cliente\n");
    printf("4. Buscar cliente\n");
    printf("5. sair\n");
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
      case 5:
        free(clientes);
        return;
      default:
        printf("ops. errado, amigo\n");
        break;
    }
  } while (escolha != 0);

  free(clientes);
}

void ex08(){
  int i, j, k, temp, l1, c1, l2, c2, matchedPairs = 0;
  int m[4][4], nums[16];
  bool revealed[4][4] = {false};
  bool finish;

  for (i = 0; i < 8; i++) {
    nums[2 * i] = i + 1;
    nums[2 * i + 1] = i + 1;
  }

  srand(time(NULL));
  for (i = 15; i > 0; i--) {
    j = rand() % (i + 1);
    temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
  }

  k = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++)
      m[i][j] = nums[k++];
  }

  finish = false;
  do {
    printTable(m, revealed, -1, -1, -1, -1);
    printf("Escolha linha e coluna das peças que deseja mostrar (ex: 1 3): \n");
    scanf("%d %d", &l1, &c1);
    scanf("%d %d", &l2, &c2);
    clr();
    
    if (m[l1-1][c1-1] == m[l2-1][c2-1] && (l1 != l2 || c1 != c2)) {
      revealed[l1-1][c1-1] = true;
      revealed[l2-1][c2-1] = true;
      matchedPairs++;
      if (matchedPairs == 8) finish = true;
    } else {
      printTable(m, revealed, l1-1, c1-1, l2-1, c2-1);
      printf("Peças diferentes.\n");
    }

  } while (!finish);

  printf("Parabéns! Você encontrou todos os pares.\n");
}

void ex09(){
  char str[100];

  FILE * fin = fopen("./files/strings.txt", "r");
  if(!fin) return;
  FILE * fout = fopen("./files/palindromos.txt", "a");
  if(!fout) return;

  while (!feof(fin))
  {
    fgets(str, 100, fin);
    str[strcspn(str, "\n")] = '\0'; //tira o \n
    if(palindromo(str, strlen(str) - 1, 0)) 
      fprintf(fout, "%s é palindromo\n", str);
    else fprintf(fout, "%s não é palindromo\n", str);
  }

  fclose(fin);
  fclose(fout);
}

void ex10(){
  char board[SIZE][SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
  };

  int turns = 0;
  bool gameOver = false;

  while (turns < 5 && !gameOver) {
    printf("Turn %d:\n", turns + 1);

    makeMove(board, 'x');
    printBoard(board);
    if (turns >= 2 && checkWin(board, 'x')) {
      printf("Jogador x venceu!\n");
      gameOver = true;
      break;
    }

    if (!gameOver && turns < 4) {
      makeMove(board, 'o');
      printBoard(board);
      if (turns >= 2 && checkWin(board, 'o')) {
        printf("Jogador o venceu!\n");
        gameOver = true;
        break;
      }
    }

    turns++;
  }

  if (!gameOver && turns == 5)
    printf("Velha!!\n");
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
          ex08();
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
    printf("07. Clientes\n");
    printf("08. Memory Game\n");
    printf("09. Palindromos\n");
    printf("10. Tic-tac-toe\n");
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

void printTable(int m[4][4], bool revealed[4][4], int l1, int c1, int l2, int c2) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
        if (revealed[i][j] || (i == l1 && j == c1) || (i == l2 && j == c2)) {
            printf("%2d ", m[i][j]);
        } else {
            printf(" # ");
        }
    }
    printf("\n");
  }
}

bool palindromo(char * str, int y, int aux){
  if (y <= aux) return true;

  else {
    if (str[y] != str[aux]) return false;
    palindromo(str, y-1, aux+1);
  }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

bool checkWin(char board[SIZE][SIZE], char player) {
  for (int i = 0; i < SIZE; i++) {
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
  }
  if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
  if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
  return false;
}

void makeMove(char board[SIZE][SIZE], char player) {
  int row, col;
  do {
    printf("Jogador %c, entre com sua jogada (linha e coluna): ", player);
    scanf("%d %d", &row, &col);
    row--;
    col--;
  } while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ');

  board[row][col] = player;
}