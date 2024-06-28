#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

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

#endif // EVENT_HPP
