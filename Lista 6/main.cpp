#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "libs/Banco.hpp"
#include "libs/Evento.hpp"
#include "libs/Eleicao.hpp"
#include "libs/Biblioteca.hpp"
#include "libs/Funcionario.hpp"

using namespace std;

void employee(){
  Pessoa pessoa = Pessoa("Alvim", 18);
  Funcionario funcionario = Funcionario("Igor", 21, 3000);

  cout << "Pessoa: " << pessoa.getName() << ", " << pessoa.getAge() << endl;
  cout << "Funcionario: " << funcionario.getName() << ", " << funcionario.getAge() << ", " << funcionario.getBudget() << endl;
}

void bank(){
  ContaPoupanca poupanca = ContaPoupanca("Marcos", 1000);
  ContaCorrente corrente = ContaCorrente("Sharpay", 2000);
  
  cout << "Poupanca antes de sacar 30 pila: " << poupanca.getBalance() << endl;
  poupanca.sacar(30);
  cout << "Poupanca depois de sacar 30 pila: " << poupanca.getBalance() << endl;

  cout << endl;

  cout << "Corrente antes de sacar 10 pila: " << corrente.getBalance() << endl;
  corrente.sacar(10);
  cout << "Corrente depois de sacar 10 pila: " << corrente.getBalance() << endl;

  cout << endl;

  cout << "Corrente antes de depositar 60 pila: " << corrente.getBalance() << endl;
  corrente.depositar(60);
  cout << "Corrente depois de depositar 60 pila: " << corrente.getBalance() << endl;

  cout << endl;

  cout << "Poupanca antes de depositar 100 pila: " << poupanca.getBalance() << endl;
  poupanca.depositar(100);
  cout << "Poupanca depois de depositar 100 pila: " << poupanca.getBalance() << endl;

  cout << endl;

  cout << "Contas antes de transacionar 70 pila de poupanca para corrente:\n Poupanca: " << poupanca.getBalance() << "\n Corrente: " << corrente.getBalance() << endl;
  corrente.transferencia(poupanca, corrente, 70.00);
  cout << "Contas depois de transacionar 70 pila de poupanca para corrente:\n Poupanca: " << poupanca.getBalance() << "\n Corrente: " << corrente.getBalance() << endl;

  cout << endl;

  cout << "Contas antes de transacionar 70 pila de corrente para poupanca:\n Poupanca: " << poupanca.getBalance() << "\n Corrente: " << corrente.getBalance() << endl;
  poupanca.transferencia(corrente, poupanca, 70.00);
  cout << "Contas depois de transacionar 70 pila de corrente para poupanca:\n Poupanca: " << poupanca.getBalance() << "\n Corrente: " << corrente.getBalance() << endl;
}

void library(){
  vector<Livro> acervo;
  vector<Usuario> usuarios;

  cadastrarLivro(acervo, "O Senhor dos Anéis", "J.R.R. Tolkien");
  cadastrarLivro(acervo, "Harry Potter e a Pedra Filosofal", "J.K. Rowling");
  registrarUsuario(usuarios, "João", 25);
  registrarUsuario(usuarios, "Maria", 30);

  int opcao;
  do {
    cout << endl;
    cout << "Menu:" << endl;
    cout << "1. Gerenciar Emprestimo" << endl;
    cout << "2. Devolver Livro" << endl;
    cout << "3. Listar Emprestimos de um Usuario" << endl;
    cout << "4. Sair" << endl;
    cout << "Escolha uma opcao: ";
    cin >> opcao;
    cin.ignore();

    switch (opcao) {
      case 1:
        gerenciarEmprestimo(acervo, usuarios);
        break;
      case 2:
        devolverLivro(acervo, usuarios);
        break;
      case 3:
        listarEmprestimosUsuario(usuarios);
        break;
      case 4:
        cout << "Saindo..." << endl;
        break;
      default:
        cout << "Opção inválida." << endl;
        break;
    }
  } while (opcao != 4);
}

void events(){
  Organizador organizador = Organizador("Pedro 'Picles' Periceles");

  int choice;

  cout << endl << "-------------------" << endl;
  cout << "0. " << "Exit" << endl;
  cout << "1. " << "Marcar Evento" << endl;
  cout << "2. " << "Ver Eventos" << endl;
  cout << "Escolha: ";
  cin >> choice;
  cin.ignore();

  switch (choice) {
    case 1:
      organizador.marcarEvento();
      break;
    case 2:
      Evento::verEventos();
      break;
    default:
      break;
  }
}

void election() {
  Votacao votacao;

  votacao.registrarCandidato(Candidato("Lule"));
  votacao.registrarCandidato(Candidato("Bonoro"));
  votacao.registrarCandidato(Candidato("Cirio Gomas"));

  int numEleitores;
  cout << "Digite o número de eleitores: ";
  cin >> numEleitores;
  cin.ignore();

  for (int i = 0; i < numEleitores; ++i) {
    string nomeEleitor;
    int idadeEleitor;
    cout << endl << "Digite o nome do eleitor " << i + 1 << ": ";
    getline(cin, nomeEleitor);
    cout << "Digite a idade do eleitor " << i + 1 << ": ";
    cin >> idadeEleitor;
    cin.ignore();

    Eleitor eleitor(nomeEleitor, idadeEleitor);
    try {
      eleitor.verificarIdade(idadeEleitor);
      votacao.registrarEleitor(eleitor);
    } catch (invalid_argument &e) {
      cerr << e.what() << endl;
      i--;
    }
  }

  srand(time(0));

  vector<Candidato> candidatos = votacao.getCandidatos();
  for (const auto &eleitor : votacao.getEleitores()) {
    int indiceAleatorio = rand() % 3;
    votacao.processarVoto(eleitor.getNome(), candidatos[indiceAleatorio].getNome());
  }

  votacao.exibirResultados();

  votacao.salvarEmArquivo("files/election.txt");
}

int menu(){
  int choice;

  cout << endl << "-------------------" << endl;
  cout << "0. " << "Exit" << endl;
  cout << "1. " << "Funcionario" << endl;
  cout << "2. " << "Banco" << endl;
  cout << "3. " << "Biblioteca" << endl;
  cout << "4. " << "Evento" << endl;
  cout << "5. " << "Eleicao" << endl;
  cout << "Escolha uma opcao: ";
  cin >> choice;

  return choice;
}

int main(){
  int choice;
  do {
    choice = menu();
    switch (choice) {
      case 1:
        employee();
        break;
      case 2:
        bank();
        break;
      case 3:
        library();
        break;
      case 4:
        events();
        break;
      case 5:
        election();
        break;
      default:
        break;
    }
  }while (choice != 0);

  return EXIT_SUCCESS;
}