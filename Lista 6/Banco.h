#include <iostream>
#include <string>

using namespace std;

class ContaBancaria {
private:
  string owner;
  int balance;

public:

  ContaBancaria(string titular, int saldo) : owner(titular), balance(saldo) {}

  string getOwner(){
    return owner;
  }

  int getBalance(){
    return balance;
  }

  void setOwner(string value){
    owner = value;
  }

  void setBalance(int value){
    balance = value;
  }

  bool verificaValor(double value){
    return (value < 0 || value > balance) ? false : true;
  }

};

class ContaPoupanca : ContaBancaria {
public:
  //       Conta a receber  | Conta a pagar  
  void p2p(ContaPoupanca p1, ContaPoupanca p2, double valor){
    if (!verificaValor(valor)) return;
    p1.setBalance(p1.getBalance() + valor);
    p2.setBalance(p2.getBalance() - valor);
  }

};

class ContaCorrente : ContaBancaria {

};