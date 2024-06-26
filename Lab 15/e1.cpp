#include <iostream>
#include <locale.h>
using namespace std;

class ContaBancaria {
private:
  float saldoConta;

public:
  ContaBancaria() : saldoConta(50000){};
  ~ContaBancaria() { cout << "Executando destruidor\n"; }
  void setSaldo(float valor) { saldoConta = valor; }
  float getSaldo() { return saldoConta; }
  void creditar(float valor) {
    saldoConta += valor;
    cout << "O valor " << valor << "foi creditado\n";
  }
  void sacar(float valor) {
    if (saldoConta < valor) {
      cout << "Saldo insuficiente\n";
      return;
    }
    saldoConta -= valor;
    cout << "O valor " << valor << " foi sacado\n";
  }
};

ContaBancaria minhaConta;

int main() {
  int escolha;
  float valor;

  cout << "Digite:\n0 - Para sacar.\n1 - Para creditar.\n2 - Para ver o "
          "saldo.\nQualquer outra tecla para sair\n";
  cin >> escolha;
  if (escolha == 0) {
    cout << "Digite o valor a ser sacado: ";
    cin >> valor;
    cout << "\n";
    minhaConta.sacar(valor);
  } else if (escolha == 1) {
    cout << "Digite o valor a ser creditado: ";
    cin >> valor;
    cout << "\n";
    minhaConta.creditar(valor);
  } else if (escolha == 2) {
    float saldo = minhaConta.getSaldo();
    cout << "O saldo atual é: " << saldo;
    cout << "\n";
  }
  while (escolha != 3)
    ;
  cout << "Encerrando...\n";

  return 0;
}