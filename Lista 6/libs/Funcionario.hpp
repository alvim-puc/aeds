#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <cstring>
#include <iostream>
#include <string>
#include "Pessoa.hpp"

using namespace std;

class Funcionario : public Pessoa{
private:
  double budget;

public:
  Funcionario() : budget(0){}
  Funcionario(string nome, int idade, double budget) : Pessoa(nome, idade), budget(budget){}

  double getBudget(){
    return budget;
  }

  void setBudget(double value){
    budget = value;
  }



  
};

#endif