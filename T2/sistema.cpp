#include <iostream>
#include <ctime>
#include <cstdlib>
#include "estrutura.h"
using namespace std;

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
    pista pistas[3];
    int Tempo = 0, num, prior, tempoOcupacao, tempoChegada;
    inicializapista(pistas);
    aviao* avioes = inicializaaviao(avioes);
    aviao* a;
    inicializarVoos(avioes);
    processarEntrada(avioes, pistas, Tempo);

    while (pistas[0].filaEspera != NULL || pistas[1].filaEspera != NULL || pistas[2].filaEspera != NULL) {
        cout << "\nTempo: " << Tempo << "\n";
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
                cout << "\nPista " << pistas[i].nome << " ocupada pelo aviao com num: " << pistas[i].aviaoAtual->num << ", prioridade: " << pistas[i].aviaoAtual->prior << ", faltam " << pistas[i].tempoOcupacao << " tempos.\n";
            } else {
                cout << "\nPista " << pistas[i].nome << " esta livre.\n";
            }

            if (pistas[i].filaEspera != NULL) {
                a = pistas[i].filaEspera;
                cout << "Lista de espera completa: \n"; 
                while (pistas[i].filaEspera != NULL)
                {
                    cout << "Numero do aviao: " << pistas[i].filaEspera->num << ", prioridade: "<< pistas[i].filaEspera->prior << ", tempo de chegada: "<< pistas[i].filaEspera->tempoChegada << ", tempo que ocupara a pista: " << pistas[i].filaEspera->tempOcupacao << "\n";
                    pistas[i].filaEspera = pistas[i].filaEspera->link;
                }
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
