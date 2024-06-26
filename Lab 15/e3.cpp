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

class Inhonho : FormaGeometrica{ public:
  float calcularArea() override {
    float r;

    cout << "Digite o valor do raio: ";
    cin >> r;

    return 3.14159265359 * pow(r, 2);
  }
};

class BobEsponja : FormaGeometrica{ public:
  float calcularArea() override{
    float base, altura;

    cout << "Digite a base: ";
    cin >> base;

    cout << "Digite a altura: ";
    cin >> altura;

    return base * altura;
  }
};

class BillCipher : FormaGeometrica { public:
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
  BillCipher triangulo;
  Inhonho bola;
  BobEsponja quadrado;

  cout << "Area do triangulo: " << triangulo.calcularArea() << endl << endl;
  cout << "Area do quadrado: " << quadrado.calcularArea() << endl << endl;
  cout << "Area da bola: " << bola.calcularArea() << endl << endl;

  return EXIT_SUCCESS;
}