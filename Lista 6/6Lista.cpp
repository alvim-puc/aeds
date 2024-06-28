#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

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
    cout << "Pessoa destruida com sucesso!" << endl;
  }

};

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



class Participante {
private:
    string nome;
    int idade;

public:
    Participante(string n, int i) : nome(n), idade(i) {}

    string getNome() const {
        return nome;
    }

    int getIdade() const {
        return idade;
    }

    void setNome(string n) {
        nome = n;
    }

    void setIdade(int i) {
        idade = i;
    }

    void verificarIdade(int idade) {
        if (idade < 18)
            throw invalid_argument("Participante menor de idade");
    }
};

class Organizador {
private:
    string nome;

public:
    Organizador(string nome) : nome(nome) {}

    string getNome() const {
        return nome;
    }

    void setNome(string n) {
        nome = n;
    }

    void marcarEvento();
};

class Evento {
private:
    vector<Participante> participantes;
    int qtd_participantes;
    Organizador organizador;
    string data, nome;

public:
    Evento() : organizador(Organizador("")) {}
    Evento(int qp, string d, string nome, Organizador organizador) : qtd_participantes(qp), data(d), nome(nome), organizador(organizador) {}

    int getParticipantesQtd() const {
        return qtd_participantes;
    }

    string getData() const {
        return data;
    }

    string getNome() const {
        return nome;
    }

    void setParticipantesQtd(int qp) {
        qtd_participantes = qp;
    }

    void setData(string d) {
        data = d;
    }

    void setNome(string n) {
        nome = n;
    }

    void addParticipante(Participante participante) {
        participantes.push_back(participante);
    }

    vector<Participante> getParticipantes() const {
        return participantes;
    }

    static void verEventos() {
        FILE* inFile = fopen("files/events.txt", "r");
        if (inFile == NULL) {
            cerr << "Erro ao abrir o arquivo" << endl;
            return;
        }

        while (true) {
            Evento evento;
            char resp;

            char buffer[100];

            if (fgets(buffer, sizeof(buffer), inFile) == NULL) break;
            evento.organizador.setNome(buffer);
            evento.organizador.setNome(evento.organizador.getNome().substr(0, evento.organizador.getNome().length() - 1)); // Remove newline

            if (fgets(buffer, sizeof(buffer), inFile) == NULL) break;
            evento.setNome(buffer);
            evento.setNome(evento.getNome().substr(0, evento.getNome().length() - 1)); // Remove newline

            if (fgets(buffer, sizeof(buffer), inFile) == NULL) break;
            evento.setData(buffer);
            evento.setData(evento.getData().substr(0, evento.getData().length() - 1)); // Remove newline

            if (fscanf(inFile, "%d\n", &evento.qtd_participantes) != 1) break;

            for (int i = 0; i < evento.qtd_participantes; i++) {
                if (fgets(buffer, sizeof(buffer), inFile) == NULL) break;
                string nomeParticipante(buffer);
                nomeParticipante = nomeParticipante.substr(0, nomeParticipante.length() - 1); // Remove newline

                int idadeParticipante;
                if (fscanf(inFile, "%d\n", &idadeParticipante) != 1) break;

                Participante participante(nomeParticipante, idadeParticipante);
                evento.addParticipante(participante);
            }

            cout << endl << "-------------------" << endl;
            cout << "Organizador: " << evento.organizador.getNome() << endl;
            cout << "Nome do evento: " << evento.getNome() << endl;
            cout << "Data do evento: " << evento.getData() << endl;
            cout << "Quantidade de participantes: " << evento.getParticipantesQtd() << endl;
            cout << "Listar participantes? ";
            cin >> resp;
            cin.ignore();

            if (tolower(resp) == 's' || tolower(resp) == 'y') {
                cout << "Participantes: " << endl;
                for (const auto& participante : evento.getParticipantes()) {
                    cout << participante.getNome() << ", " << participante.getIdade() << endl;
                }
            }
        }

        fclose(inFile);
    }
};

void Organizador::marcarEvento() {
    try {
        string data, nomeEvento, nomeParticipante;
        int qtd_participantes, idadeParticipante;

        cout << "Nome do evento: ";
        getline(cin, nomeEvento);

        cout << "Data do evento: ";
        getline(cin, data);

        cout << "Quantidade de participantes: ";
        cin >> qtd_participantes;
        cin.ignore();

        Evento evento = Evento(qtd_participantes, data, nomeEvento, *this);

        for (int i = 0; i < qtd_participantes; i++) {
            try {
                cout << endl << "Nome do participante " << i + 1 << ": ";
                getline(cin, nomeParticipante);

                cout << "Idade do participante: ";
                cin >> idadeParticipante;
                cin.ignore();

                Participante participante(nomeParticipante, idadeParticipante);

                participante.verificarIdade(idadeParticipante);

                evento.addParticipante(participante);
            } catch (invalid_argument& e) {
                cerr << e.what() << endl;
                i -= 1;
            }
        }

        cout << endl;

        FILE* outFile = fopen("files/events.txt", "a");
        if (!outFile) {
            cerr << "Erro ao abrir o arquivo" << endl;
            return;
        }

        fprintf(outFile, "%s\n", this->getNome().c_str());
        fprintf(outFile, "%s\n", evento.getNome().c_str());
        fprintf(outFile, "%s\n", evento.getData().c_str());
        fprintf(outFile, "%d\n", evento.getParticipantesQtd());

        for (const auto& participante : evento.getParticipantes()) {
            fprintf(outFile, "%s\n", participante.getNome().c_str());
            fprintf(outFile, "%d\n", participante.getIdade());
        }

        fclose(outFile);

        cout << "Evento marcado com sucesso!" << endl;
        cout << "Organizador: " << this->getNome() << endl;
        cout << "Nome do evento: " << evento.getNome() << endl;
        cout << "Data do evento: " << evento.getData() << endl;
        cout << "Quantidade de participantes: " << evento.getParticipantesQtd() << endl;

    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
}

class Eleitor {
private:
    string nome;
    int idade;

public:
    Eleitor(string n, int i) : nome(n), idade(i) {}

    string getNome() const {
        return nome;
    }

    int getIdade() const {
        return idade;
    }

    void setNome(string n) {
        nome = n;
    }

    void setIdade(int i) {
        idade = i;
    }

    void verificarIdade(int idade) {
        if (idade < 18)
            throw invalid_argument("Eleitor menor de idade");
    }
};

class Candidato {
private:
    string nome;
    int votos;

public:
    Candidato(string n) : nome(n), votos(0) {}

    string getNome() const {
        return nome;
    }

    int getVotos() const {
        return votos;
    }

    void adicionarVoto() {
        votos++;
    }
};

class Votacao {
private:
    vector<Eleitor> eleitores;
    vector<Candidato> candidatos;

public:
    void registrarEleitor(Eleitor eleitor) {
        eleitores.push_back(eleitor);
    }

    void registrarCandidato(Candidato candidato) {
        candidatos.push_back(candidato);
    }

    vector<Eleitor> getEleitores() const {
        return eleitores;
    }

    vector<Candidato> getCandidatos() const {
        return candidatos;
    }

    void processarVoto(string nomeEleitor, string nomeCandidato) {
        bool eleitorEncontrado = false;
        for (auto &eleitor : eleitores) {
            if (eleitor.getNome() == nomeEleitor) {
                eleitorEncontrado = true;
                break;
            }
        }

        if (!eleitorEncontrado) {
            cerr << "Eleitor nao registrado." << endl;
            return;
        }

        bool candidatoEncontrado = false;
        for (auto &candidato : candidatos) {
            if (candidato.getNome() == nomeCandidato) {
                candidato.adicionarVoto();
                candidatoEncontrado = true;
                break;
            }
        }

        if (!candidatoEncontrado) {
            cerr << "Candidato nao registrado." << endl;
        }
    }

    void exibirResultados() const {
        cout << "Resultados da Votacao:" << endl;
        for (const auto &candidato : candidatos) {
            cout << "Candidato " << candidato.getNome() << " recebeu " << candidato.getVotos() << " votos." << endl;
        }
    }

    void salvarEmArquivo(const char* filename) const {
        FILE* outFile = fopen(filename, "w");
        if (!outFile) {
            cerr << "Erro ao abrir o arquivo para escrita." << endl;
            return;
        }

        fprintf(outFile, "Eleitores:\n");
        for (const auto &eleitor : eleitores) {
            fprintf(outFile, "%s %d\n", eleitor.getNome().c_str(), eleitor.getIdade());
        }

        fprintf(outFile, "Candidatos:\n");
        for (const auto &candidato : candidatos) {
            fprintf(outFile, "%s %d\n", candidato.getNome().c_str(), candidato.getVotos());
        }

        fclose(outFile);
    }
};

class ContaBancaria { public:
private:
  string owner;
  double balance;
  float tax;

public:
  ContaBancaria(){}
  ContaBancaria(string titular, double saldo) : owner(titular), balance(saldo) {}

  string getOwner(){
    return owner;
  }

  double getBalance(){
    return balance;
  }

  void setOwner(string value){
    owner = value;
  }

  void setBalance(double value){
    balance = value;
  }

  void verificaValor(double value){
    if(value < 0 || value > balance)
      throw invalid_argument("Valor invalido");
  }

  void depositar(double value){
    try {
      verificaValor(value);
      setBalance(value + balance);
    } catch (invalid_argument err) {
      cerr << "Excecao encontrada: " << err.what();
    }

  }

  virtual void sacar(double value){}

  void transferencia(ContaBancaria& c1, ContaBancaria& c2, double value) {
    try {
      verificaValor(value);
      c1.setBalance(c1.getBalance() - value);
      c2.setBalance(c2.getBalance() + value);
    } catch (invalid_argument& err) {
      cerr << "Excecao encontrada: " << err.what() << endl;
    }
  }

  ~ContaBancaria(){
    cout << "Conta bancaria totalmente acabada" << endl;
  }  

};

class ContaPoupanca : public ContaBancaria { public:
  ContaPoupanca(){}
  ContaPoupanca(string titular, double saldo) : ContaBancaria(titular, saldo) {}

  void sacar(double value) override{
    try {
      verificaValor(value);
      value = getBalance() - value;
      setBalance(value - value / 100); // remove a taxa
    } catch (invalid_argument err) {
      cerr << "Excecao encontrada: " << err.what();
    }

  }
};

class ContaCorrente : public ContaBancaria { public:
  ContaCorrente(){}
  ContaCorrente(string titular, double saldo) : ContaBancaria(titular, saldo) {}

  void sacar(double value) override{
    try {
      verificaValor(value);
      setBalance(getBalance() - value);
    }
    catch (invalid_argument err) {
      cerr << "Excecao encontrada: " << err.what();
    }

  }
};

class Livro {
private:
    string titulo;
    string autor;
    bool disponivel;

public:
    Livro(string titulo, string autor) : titulo(titulo), autor(autor), disponivel(true) {}

    string getTitulo() const {
        return titulo;
    }

    string getAutor() const {
        return autor;
    }

    bool estaDisponivel() const {
        return disponivel;
    }

    void emprestarLivro() {
        disponivel = false;
    }

    void devolverLivro() {
        disponivel = true;
    }
};

class Usuario {
private:
    string nome;
    int idade;
    vector<Livro*> emprestimos;

public:
    Usuario(string nome, int idade) : nome(nome), idade(idade) {}

    string getNome() const {
        return nome;
    }

    int getIdade() const {
        return idade;
    }

    void adicionarEmprestimo(Livro* livro) {
        emprestimos.push_back(livro);
    }

    void listarEmprestimos() const {
        if (emprestimos.empty()) {
            cout << "Este usuario nao possui emprestimos." << endl;
        } else {
            cout << "Emprestimos de " << nome << ":" << endl;
            for (size_t i = 0; i < emprestimos.size(); ++i) {
                cout << i + 1 << ". " << emprestimos[i]->getTitulo() << " por " << emprestimos[i]->getAutor() << endl;
            }
        }
    }

    vector<Livro*> getEmprestimos() const {
        return emprestimos;
    }
};

class Emprestimo {
private:
    Usuario* usuario;
    Livro* livro;
    time_t dataEmprestimo;
    time_t dataDevolucao;

public:
    Emprestimo(Usuario* usuario, Livro* livro) : usuario(usuario), livro(livro) {
        dataEmprestimo = time(nullptr); 
        dataDevolucao = 0;
    }

    Usuario* getUsuario() const {
        return usuario;
    }

    Livro* getLivro() const {
        return livro;
    }

    void setDevolucao() {
        dataDevolucao = time(nullptr);
    }

    time_t getDataEmprestimo() const {
        return dataEmprestimo;
    }

    time_t getDataDevolucao() const {
        return dataDevolucao;
    }
};

void cadastrarLivro(vector<Livro>& acervo, string titulo, string autor) {
    Livro novoLivro(titulo, autor);
    acervo.push_back(novoLivro);
    cout << "Livro cadastrado com sucesso: " << titulo << " por " << autor << endl;
}

void registrarUsuario(vector<Usuario>& usuarios, string nome, int idade) {
    Usuario novoUsuario(nome, idade);
    usuarios.push_back(novoUsuario);
    cout << "Usuario registrado com sucesso: " << nome << ", " << idade << " anos" << endl;
}

void listarEmprestimosUsuario(vector<Usuario>& usuarios) {
    if (usuarios.empty()) {
        cout << "Nao ha usuarios registrados." << endl;
        return;
    }

    cout << "Escolha um usuario para ver seus emprestimos (digite o numero correspondente):" << endl;
    for (size_t i = 0; i < usuarios.size(); ++i) {
        cout << i + 1 << ". " << usuarios[i].getNome() << ", " << usuarios[i].getIdade() << " anos" << endl;
    }

    int escolhaUsuario;
    cin >> escolhaUsuario;
    cin.ignore();

    if (escolhaUsuario < 1 || escolhaUsuario > static_cast<int>(usuarios.size())) {
        cout << "Opcao invalida." << endl;
        return;
    }

    Usuario& usuario = usuarios[escolhaUsuario - 1];
    usuario.listarEmprestimos();
}

void gerenciarEmprestimo(vector<Livro>& acervo, vector<Usuario>& usuarios) {
    if (acervo.empty() || usuarios.empty()) {
        cout << "Nao ha livros ou usuarios registrados para realizar emprestimo." << endl;
        return;
    }

    cout << "Escolha um usuario para realizar emprestimo (digite o numero correspondente):" << endl;
    for (size_t i = 0; i < usuarios.size(); ++i) {
        cout << i + 1 << ". " << usuarios[i].getNome() << ", " << usuarios[i].getIdade() << " anos" << endl;
    }

    int escolhaUsuario;
    cin >> escolhaUsuario;
    cin.ignore();

    if (escolhaUsuario < 1 || escolhaUsuario > static_cast<int>(usuarios.size())) {
        cout << "Opcao invalida." << endl;
        return;
    }

    Usuario& usuario = usuarios[escolhaUsuario - 1];

    cout << "Escolha um livro para emprestimo (digite o numero correspondente):" << endl;
    for (size_t i = 0; i < acervo.size(); ++i) {
        if (acervo[i].estaDisponivel()) {
            cout << i + 1 << ". " << acervo[i].getTitulo() << " por " << acervo[i].getAutor() << endl;
        }
    }

    int escolhaLivro;
    cin >> escolhaLivro;
    cin.ignore();

    if (escolhaLivro < 1 || escolhaLivro > static_cast<int>(acervo.size())) {
        cout << "Opcao invalida." << endl;
        return;
    }

    Livro& livro = acervo[escolhaLivro - 1];

    if (!livro.estaDisponivel()) {
        cout << "Livro indisponivel para emprestimo." << endl;
        return;
    }

    livro.emprestarLivro();
    usuario.adicionarEmprestimo(&livro);
    cout << "Livro emprestado com sucesso para " << usuario.getNome() << "." << endl;
}

void devolverLivro(vector<Livro>& acervo, vector<Usuario>& usuarios) {
    if (acervo.empty() || usuarios.empty()) {
        cout << "Nao ha livros ou usuarios registrados para devolucao." << endl;
        return;
    }

    cout << "Escolha um usuario para devolucao (digite o numero correspondente):" << endl;
    for (size_t i = 0; i < usuarios.size(); ++i) {
        cout << i + 1 << ". " << usuarios[i].getNome() << ", " << usuarios[i].getIdade() << " anos" << endl;
    }

    int escolhaUsuario;
    cin >> escolhaUsuario;
    cin.ignore();

    if (escolhaUsuario < 1 || escolhaUsuario > static_cast<int>(usuarios.size())) {
        cout << "Opcao invalida." << endl;
        return;
    }

    Usuario usuario = usuarios[escolhaUsuario - 1];

    if (usuario.getEmprestimos().empty()) {
        cout << "Este usuario nao possui emprestimos." << endl;
        return;
    }

    cout << "Escolha um livro para devolucao (digite o numero correspondente):" << endl;
    for (size_t i = 0; i < usuario.getEmprestimos().size(); ++i) {
        cout << i + 1 << ". " << usuario.getEmprestimos()[i]->getTitulo() << " por " 
             << usuario.getEmprestimos()[i]->getAutor() << endl;
    }

    int escolhaLivro;
    cin >> escolhaLivro;
    cin.ignore();

    if (escolhaLivro < 1 || escolhaLivro > static_cast<int>(usuario.getEmprestimos().size())) {
        cout << "Opcao invalida." << endl;
        return;
    }

    Livro& livro = *usuario.getEmprestimos()[escolhaLivro - 1];

    if (livro.estaDisponivel()) {
        cout << "Este livro ja foi devolvido." << endl;
        return;
    }

    livro.devolverLivro();
    usuario.getEmprestimos().erase(usuario.getEmprestimos().begin() + escolhaLivro - 1);
    cout << "Livro devolvido com sucesso." << endl;
}

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

  // Exemplo de uso
  cadastrarLivro(acervo, "O Senhor dos Aneis", "J.R.R. Tolkien");
  cadastrarLivro(acervo, "Harry Potter e a Pedra Filosofal", "J.K. Rowling");
  registrarUsuario(usuarios, "Joao", 25);
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
              cout << "Opcao invalida." << endl;
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
  cout << "Digite o numero de eleitores: ";
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