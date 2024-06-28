#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

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
            cout << "Este usuário não possui empréstimos." << endl;
        } else {
            cout << "Empréstimos de " << nome << ":" << endl;
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
    cout << "Usuário registrado com sucesso: " << nome << ", " << idade << " anos" << endl;
}

void listarEmprestimosUsuario(vector<Usuario>& usuarios) {
    if (usuarios.empty()) {
        cout << "Não há usuários registrados." << endl;
        return;
    }

    cout << "Escolha um usuário para ver seus empréstimos (digite o número correspondente):" << endl;
    for (size_t i = 0; i < usuarios.size(); ++i) {
        cout << i + 1 << ". " << usuarios[i].getNome() << ", " << usuarios[i].getIdade() << " anos" << endl;
    }

    int escolhaUsuario;
    cin >> escolhaUsuario;
    cin.ignore();

    if (escolhaUsuario < 1 || escolhaUsuario > static_cast<int>(usuarios.size())) {
        cout << "Opção inválida." << endl;
        return;
    }

    Usuario& usuario = usuarios[escolhaUsuario - 1];
    usuario.listarEmprestimos();
}

void gerenciarEmprestimo(vector<Livro>& acervo, vector<Usuario>& usuarios) {
    if (acervo.empty() || usuarios.empty()) {
        cout << "Não há livros ou usuários registrados para realizar empréstimo." << endl;
        return;
    }

    cout << "Escolha um usuário para realizar empréstimo (digite o número correspondente):" << endl;
    for (size_t i = 0; i < usuarios.size(); ++i) {
        cout << i + 1 << ". " << usuarios[i].getNome() << ", " << usuarios[i].getIdade() << " anos" << endl;
    }

    int escolhaUsuario;
    cin >> escolhaUsuario;
    cin.ignore();

    if (escolhaUsuario < 1 || escolhaUsuario > static_cast<int>(usuarios.size())) {
        cout << "Opção inválida." << endl;
        return;
    }

    Usuario& usuario = usuarios[escolhaUsuario - 1];

    cout << "Escolha um livro para empréstimo (digite o número correspondente):" << endl;
    for (size_t i = 0; i < acervo.size(); ++i) {
        if (acervo[i].estaDisponivel()) {
            cout << i + 1 << ". " << acervo[i].getTitulo() << " por " << acervo[i].getAutor() << endl;
        }
    }

    int escolhaLivro;
    cin >> escolhaLivro;
    cin.ignore();

    if (escolhaLivro < 1 || escolhaLivro > static_cast<int>(acervo.size())) {
        cout << "Opção inválida." << endl;
        return;
    }

    Livro& livro = acervo[escolhaLivro - 1];

    if (!livro.estaDisponivel()) {
        cout << "Livro indisponível para empréstimo." << endl;
        return;
    }

    livro.emprestarLivro();
    usuario.adicionarEmprestimo(&livro);
    cout << "Livro emprestado com sucesso para " << usuario.getNome() << "." << endl;
}

void devolverLivro(vector<Livro>& acervo, vector<Usuario>& usuarios) {
    if (acervo.empty() || usuarios.empty()) {
        cout << "Não há livros ou usuários registrados para devolução." << endl;
        return;
    }

    cout << "Escolha um usuário para devolução (digite o número correspondente):" << endl;
    for (size_t i = 0; i < usuarios.size(); ++i) {
        cout << i + 1 << ". " << usuarios[i].getNome() << ", " << usuarios[i].getIdade() << " anos" << endl;
    }

    int escolhaUsuario;
    cin >> escolhaUsuario;
    cin.ignore();

    if (escolhaUsuario < 1 || escolhaUsuario > static_cast<int>(usuarios.size())) {
        cout << "Opção inválida." << endl;
        return;
    }

    Usuario usuario = usuarios[escolhaUsuario - 1];

    if (usuario.getEmprestimos().empty()) {
        cout << "Este usuário não possui empréstimos." << endl;
        return;
    }

    cout << "Escolha um livro para devolução (digite o número correspondente):" << endl;
    for (size_t i = 0; i < usuario.getEmprestimos().size(); ++i) {
        cout << i + 1 << ". " << usuario.getEmprestimos()[i]->getTitulo() << " por " 
             << usuario.getEmprestimos()[i]->getAutor() << endl;
    }

    int escolhaLivro;
    cin >> escolhaLivro;
    cin.ignore();

    if (escolhaLivro < 1 || escolhaLivro > static_cast<int>(usuario.getEmprestimos().size())) {
        cout << "Opção inválida." << endl;
        return;
    }

    Livro& livro = *usuario.getEmprestimos()[escolhaLivro - 1];

    if (livro.estaDisponivel()) {
        cout << "Este livro já foi devolvido." << endl;
        return;
    }

    livro.devolverLivro();
    usuario.getEmprestimos().erase(usuario.getEmprestimos().begin() + escolhaLivro - 1);
    cout << "Livro devolvido com sucesso." << endl;
}
