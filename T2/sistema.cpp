#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "estrutura.h"
using namespace std;
using std::setw;

void inicializarVoos(aviao*& filaEntrada) {
    int num, prior, tempOcupacao, tempChegada;
    srand(time(0));
    for (int i = 0; i < 50; ++i) {
        num = i + rand() % 500;
        prior = rand() % 3 + 1;
        tempOcupacao = rand() % 10 + 1;
        tempChegada = rand() % 50;
        filaEntrada = arrumaFilaEspera(filaEntrada, num, prior, tempOcupacao, tempChegada);
    }
}

int main() {
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier blue(Color::FG_BLUE);


    pista pistas[3];
    int Tempo = 0, num, prior, tempoOcupacao, tempoChegada;
    inicializapista(pistas);
    aviao* avioes = inicializaaviao(avioes);
    aviao* a;
    inicializarVoos(avioes);
    processarEntrada(avioes, pistas, Tempo);

    while (pistas[0].filaEspera != NULL || pistas[1].filaEspera != NULL || pistas[2].filaEspera != NULL) {
        cout << red <<"\nTempo: " << Tempo << "\n \n"<< def;
        for (int i = 0; i < 3; ++i) {
            int num, prior, tempoOcupacao, tempoChegada;

            if (!pistas[i].ocupada && pistas[i].filaEspera != NULL) {
                pistas[i].filaEspera = removeFE(pistas[i].filaEspera, &num, &prior, &tempoOcupacao, &tempoChegada);
                pistas[i].ocupada = true;
                pistas[i].tempoOcupacao = tempoOcupacao;
                pistas[i].aviaoAtual = new aviao{num, prior, tempoOcupacao, tempoChegada, NULL};
            } else if (pistas[i].ocupada) {
                pistas[i].tempoOcupacao -= 4;
                if (pistas[i].tempoOcupacao <= 0) {
                    pistas[i].ocupada = false;
                    delete pistas[i].aviaoAtual; // Liberar memória do avião que estava ocupando a pista
                    pistas[i].aviaoAtual = NULL;
                }
            }

            if (pistas[i].ocupada && pistas[i].aviaoAtual != NULL) {
                cout << green << setw(5) << "Pista" << pistas[i].nome << def << setw(15) << "Numero" << setw(15) << "Prioridade" << setw(15) << "T. Chegada" << setw(15) << "T. Ocupacao"
                     <<"\nAviao atual"<< setw(8) <<pistas[i].aviaoAtual->num << setw(13)<< pistas[i].aviaoAtual->prior << setw(15) << pistas[i].aviaoAtual->tempoChegada<< setw(15) <<pistas[i].tempoOcupacao << endl;
            } else {
                cout << green << setw(5) << "Pista" << pistas[i].nome << def << setw(15) << "Numero" << setw(15) << "Prioridade" << setw(15) << "T. Chegada" << setw(15) << "T. Ocupacao"
                     <<"\nAviao atual"<< setw(8) << "-" << setw(13)<< "-" << setw(15) << "-"<< setw(15) <<"-" << endl;

                    }

            if (pistas[i].filaEspera != NULL) {
                a = pistas[i].filaEspera;
                cout << blue << "\nLista de espera completa: \n" <<def; 
                while (pistas[i].filaEspera != NULL)
                {
                    cout << "\nAviao atual"<< setw(8)  << pistas[i].filaEspera->num << setw(13) << pistas[i].filaEspera->prior << setw(15) << pistas[i].filaEspera->tempoChegada << setw(15) << pistas[i].filaEspera->tempOcupacao << "\n";
                    pistas[i].filaEspera = pistas[i].filaEspera->link;
                }
                cout << endl;
                pistas[i].filaEspera = a;
                
            } else {
                cout << "Nenhum aviao esperando na fila da pista " << pistas[i].nome << ".\n\n";
            }
        }

        cout << "------------------------------------------------------------------------" << "\n";

        Tempo += 4;
    }

    return 0;
}
