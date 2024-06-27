#include <cstdlib>
#include <iostream>
#include "Funcionario.h"
#include "Banco.h"

int menu(){
  int choice;

  cout << "0. " << "Exit" << endl;
  cout << "1. " << "Funcionario" << endl;
  cout << "2. " << "Banco" << endl;
  cout << "3. " << "Biblioteca" << endl;
  cout << "4. " << "Evento" << endl;
  cout << "5. " << "Eleicao" << endl;
  cin >> choice;

  return choice;
}

int main(){
  int choice;
  do {
    choice = menu();
    switch (choice) {
      case 1:
      //hajsdasjdhj
        break;
    }
  }while (choice != 0);

  return EXIT_SUCCESS;
}