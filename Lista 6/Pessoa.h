#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class Pessoa{
private:
  int age;
  string name;

public:
  Pessoa(int idade, string nome) : age(idade), name(nome) {}

  string getName(){
    return name;
  }

  int getAge(){
    return age;
  }

  void setName(string value) {
    name = value;
  }

  void setAge(int value){
    age = value;
  }

  ~Pessoa(){
    cout << "Pessoa destruída com sucesso!" << endl;
  }

};