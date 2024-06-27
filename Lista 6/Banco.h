#ifndef BANK_H
#define BANK_H

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>

using namespace std;

class ContaBancaria {
private:
  string owner;
  double balance;
  float tax;

public:

  ContaBancaria(string titular, double saldo) : owner(titular), balance(saldo) {}

  string getOwner(){
    return owner;
  }

  double getBalance(){
    return balance;
  }

  void setOwner(string value){
    owner = value;
  }

  void setBalance(double value){
    balance = value;
  }

  void verificaValor(double value){
    if(value < 0 || value > balance)
      throw invalid_argument("Valor invalido");
  }

  void depositar(double value){
    try {
      verificaValor(value);
      setBalance(value + balance);
    } catch (::invalid_argument err) {
      cerr << "Excecao encontrada: " << err.what();
    }

  }

  virtual void sacar(double value){}

  void transferencia(ContaBancaria c1, ContaBancaria c2, double value){
    try {
      verificaValor(value);
      c1.balance += value;
      c2.balance -= value;
    } catch (invalid_argument err) {
      cerr << "Excecao encontrada: " << err.what();
    }
    
  }

};

class ContaPoupanca : ContaBancaria {
  void sacar(double value) override{
    try {
      verificaValor(value);
      value = getBalance() - value;
      setBalance(value - value / 100); // remove a taxa
    } catch (invalid_argument err) {
      cerr << "Excecao encontrada: " << err.what();
    }

  }
};

class ContaCorrente : ContaBancaria {

  void sacar(double value) override{
    try {
      verificaValor(value);
      setBalance(getBalance() - value);
    }
    catch (invalid_argument err) {
      cerr << "Excecao encontrada: " << err.what();
    }

  }
};

#endif