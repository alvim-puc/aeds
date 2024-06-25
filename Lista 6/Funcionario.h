#include <cstring>
#include <iostream>
#include <string>
#include "Pessoa.h"

using namespace std;

class Funcionario : Pessoa{
private:
  double budget;

public:

  double getBudget(){
    return budget;
  }

  void setBudget(double value){
    budget = value;
  }



  
};