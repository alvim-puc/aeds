#include <cstdlib>
#include <iostream>

using namespace std;

class Animal{
  virtual void emitirSom(){}

  virtual void mover(){}
};

class Cachoro : Animal{ public:
  void emitirSom() override {
    cout << "roof roof" << endl;
  }

  void mover() override {
    cout << "correndo como um Athos" << endl;
  }
};

class Gato : Animal { public:
  void emitirSom() override {
    cout << "meoww" << endl;
  }

  void mover() override {
    cout << "correndo estilosamente como um Alvim" << endl;
  }
};


int main() {
  
  Gato alvim;
  Cachoro athos;

  athos.emitirSom();
  alvim.emitirSom();

  athos.mover();
  alvim.mover();

  return EXIT_SUCCESS;
}