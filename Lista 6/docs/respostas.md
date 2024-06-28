# Lista 6 AEDs

## Questões

### 1. Explique o conceito de polimorfismo e como ele é implementado em C++

Polimorfismo, é, basicamente, a possibilidade de reestruturação de métodos de uma classe herdada.

Ou seja, supondo que tenhamos uma classe Mulher que é mãe da classe Filha e possui um método chamado `tomarCafé()`, mas a filha não gosta de café. Portanto, usando `override` na funcao `tomarCafé()` dentro da classe filha, é possível modificar o método. Exemplo:

```cpp
#include <iostream>
#include <string>

using namespace std;

class Mulher { public:
    virtual void tomarCafe() {
        cout << "A mulher está tomando café." << endl;
    }

    ~Mulher() {}
};

class Filha : public Mulher { public:
    void tomarCafe() override {
        cout << "A filha não gosta de café e está tomando suco." << endl;
    }
};
```

### 2. Descreva a estrutura básica de uma classe e a diferença entre classe e objeto

POO nada mais é do que uma boa prática de programação onde encapsulamos vários métodos e atributos em um contexto, ou seja, uma classe. A diferença entre classe e objetos é que, a classe é o contexto em que o objeto é instanciado. Portanto, um objeto é um meio de trabalhar com um contexto.

### As questões de 3 a 10 são codificações, portanto estão em arquivos separados e serão testados na `main.cpp` | `6Lista.cpp`.

--------------

