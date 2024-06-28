#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class Pessoa{
private:
  int age;
  string name;

public:
  Pessoa() : age(0), name("") {}
  Pessoa(string nome, int idade) : name(nome), age(idade) {}

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

#endif