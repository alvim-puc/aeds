#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <stdexcept>

using namespace std;

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
            cerr << "Eleitor não registrado." << endl;
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
            cerr << "Candidato não registrado." << endl;
        }
    }

    void exibirResultados() const {
        cout << "Resultados da Votação:" << endl;
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