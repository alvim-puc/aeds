#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

#define NONE 0

class FormaGeometrica{
  virtual float calcularArea(){
    return NONE;
  }
};

class Inhonho : FormaGeometrica{
  float calcularArea() override {
    float r;

    cout << "Digite o valor do raio: ";
    cin >> r;

    return 3.14 * pow(r, 2);
  }
};

class BobEsponja : FormaGeometrica{
  float calcularArea() override{
    float base, altura;

    cout << "Digite a base: ";
    cin >> base;

    cout << "Digite a altura: ";
    cin >> altura;

    return base * altura;
  }
};

class BillCipher : FormaGeometrica {
  float calcularArea() override {
    float base, altura;

    cout << "Digite a base: ";
    cin >> base;

    cout << "Digite a altura: ";
    cin >> altura;

    return (base * altura) / 2;
  }
};

int main() {



  return EXIT_SUCCESS;
}