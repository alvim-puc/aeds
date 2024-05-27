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

int dph(int dias);
int dpm(int dias);
int dps(int dias);

void swap(int *a, int *b);
void ordenaCaixas(int *caixa1, int *caixa2, int *caixa3);
void calcViagens(int caixa1, int caixa2, int caixa3);

char grupo(int jgs);

void ex01(int n){
    int soma = 0, v = 1;
    for(int i = 1; i <= n; i++){
        if(i % 2 == 0)
            soma -= pow(v, 2);
        else soma += pow(v, 2);
        v += 2;
    }

    printf("Soma: %d\n", soma);
}

void ex02(int idade){
    int anoLetivo = idade - 6;

    if (idade < 6)
        printf("Idade inválida (menor que 6 anos).\n");
    else if (anoLetivo > 9)
        anoLetivo = 9;
    else if (anoLetivo < 1)
        printf("Idade inválida (não está na faixa esperada).\n");
    else
        printf("O aluno deveria estar no %dº ano letivo.\n", anoLetivo);
}

void ex03(int n){
    int s, soma = 0;
    
    for(int i = 0; i < n; i++){
        printf("%d: ", i+1);
        scanf("%d", &s);

        soma += s;
    }
    printf("Media: %.2f\n", (float)soma/n);
}

void ex04() {
    int choice;
    float lado1, lado2, lado3;

  do {
    printf("\nCalculadora de Triângulos\n");
    printf("1. Calcular área do triângulo\n");
    printf("2. Identificar tipo de triângulo\n");
    printf("3. Calcular perímetro do triângulo\n");
    printf("0. Sair\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        printf("Insira a base e a altura do triângulo: ");
        scanf("%f %f", &lado1, &lado2);
        printf("A área do triângulo é: %.2f \n", lado1 * lado2 / 2);
        break;

      case 2:
        printf("Insira os lados do triângulo: ");
        scanf("%f %f %f", &lado1, &lado2, &lado3);

        if (lado1 == lado2 && lado2 == lado3) {
          printf("É um triângulo equilátero.\n");
        } else if (lado1 == lado2 || lado1 == lado3 || lado2 == lado3) {
          printf("É um triângulo isósceles.\n");
        } else {
          printf("É um triângulo escaleno.\n");
        }
        break;
      case 3:
        printf("Insira os lados do triângulo: ");
        scanf("%f %f %f", &lado1, &lado2, &lado3);

        printf("O perímetro do triângulo é: %.2f.\n", lado1 + lado2 + lado3);
        break;
      case 0:
        printf("\nSaindo da calculadora de triângulos.\n");
        break;
      default:
        printf("Opção inválida. Tente novamente.\n");
        break;
    }
  } while (choice != 0);
}

void ex05(int dias){
    printf("%d dias em horas: %d\n", dias, dph(dias));
    printf("%d dias em minutos: %d\n", dias, dpm(dias));
    printf("%d dias em segundos: %d\n", dias, dps(dias));
}

void ex06(int num){
    int soma = 0;
    
    for(int i = 1; i < num; i++){
        if(num % i == 0)
            soma += i;
    }

    printf("%d %s um numero perfeito", num, soma == num ? "é" : "não é");
}

void ex07(){
    int count = 0;
    float salario = 0.0, soma = 0.0;
    
    printf("Para parar, digite algum numero negativo.\n");
    while(!0){
        printf("Digite o salario: ");
        scanf("%f", &salario);
        if(salario < 0) break;
        else if(salario > 0){
            soma += salario;
            ++count;
        }
    }
    printf("Media salarial: %.2f\n", soma/(float)count);
}

void ex08(){
    int caixa1, caixa2, caixa3;

    printf("Digite os tamanhos das tres caixas: ");
    scanf("%d %d %d", &caixa1, &caixa2, &caixa3);

    ordenaCaixas(&caixa1, &caixa2, &caixa3);
    calcViagens(caixa1, caixa2, caixa3);
}

void ex09(){
    int X, N, M, i;

    printf("Digite a quota mensal de bytes de sua operadora: ");
    scanf("%d", &X);
    int quota = X;
    printf("Digite o numero de meses em que usou seu plano ate agora: ");
    scanf("%d", &N);
    printf("Gasto mensal: \n");
    for(i = 0; i < N; i++){
        printf("Mes %d: ", i+1);
        scanf("%d", &M);
        if(M < quota) quota = X + (quota - M);
        else if(M > quota) quota = X - (M - quota);
        else quota = X;
    }
    printf("Bytes disponiveis no mes %d: %d\n", i, quota);
}

void ex10(){
    int jgs;

    printf("Quantos jogos você ganhou? ");
    scanf("%d", &jgs);

    if(grupo(jgs) == ' ')
        printf("Voce nao pode participar de nenhum grupo.\n");
    else
        printf("Voce está no grupo %c", grupo(jgs));
}

int main(int argc, char ** argv) {
    int choice, n, num, idade, dias;
    
    do{
        menu();
        scanf("%i%*c", &choice);
        clr();
        switch(choice){
            case 1: 
                printf("Digite n: ");
                scanf("%d", &n);
                ex01(n);
                break;
            case 2:
                printf("Insira a idade: ");
                scanf("%d", &idade);
                ex02(idade);
                break;
            case 3:
                printf("Digite n: ");
                scanf("%d", &n);
                ex03(n);
                break;
            case 4:
                ex04();
                break;
            case 5:
                printf("Digite o numero de dias: ");
                scanf("%d", &dias);
                ex05(dias);
                break;
            case 6:
                printf("Entre com um numero: ");
                scanf("%d", &num);
                ex06(num);
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

int dph(int dias){
    return dias * 24;
}
int dpm(int dias){
    return dph(dias) * 60;
}
int dps(int dias){
    return dpm(dias) * 60;
}

void swap(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}
void ordenaCaixas(int *caixa1, int *caixa2, int *caixa3) {
    if (*caixa1 > *caixa2)
        swap(caixa1, caixa2);
    if (*caixa1 > *caixa3)
        swap(caixa1, caixa3);
    if (*caixa2 > *caixa3)
        swap(caixa2, caixa3);
}
void calcViagens(int caixa1, int caixa2, int caixa3) {
    int viagens = 0;

    if (caixa1 + caixa2 < caixa3)
        viagens = 1;
    else if(caixa1 < caixa2){
        if(caixa2 < caixa3)
            viagens = 1;
        else viagens = 2;
    }
    else viagens = 3;

    printf("O numero minimo de viagens é %d\n", viagens);
}

char grupo(int jgs){
    if(jgs >= 5)
        return 'A';
    else if (jgs == 3 || jgs == 4)
        return 'B';
    else if (jgs == 1 || jgs == 2)
        return 'C';
    else
        return ' ';
}

void menu(){
    printf("\n");
    printf("Escolha um exercicio: \n");
    printf("01. Soma n\n");
    printf("02. Ano Letivo\n");
    printf("03. Media n\n");
    printf("04. Triangulos\n");
    printf("05. Dias\n");
    printf("06. Perfeito?\n");
    printf("07. Media sal\n");
    printf("08. Drone\n");
    printf("09. Net\n");
    printf("10. Grupos\n");
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