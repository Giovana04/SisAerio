#include <iostream>
using namespace std;

struct aviao {
    int num;
    int prior;
    int tempOcupacao;
    int tempoChegada;
    aviao *link;
};

struct pista {
    int nome;
    bool ocupada;
    int tempoOcupacao;
    aviao* filaEspera;
    aviao* aviaoAtual; 
};

void inicializapista(pista p[]) {
    for (int i = 0; i < 3; ++i) {
        p[i].nome = i + 1;
        p[i].ocupada = false;
        p[i].tempoOcupacao = 0;
        p[i].filaEspera = NULL;
        p[i].aviaoAtual = NULL;
    }
}

aviao* inicializaaviao(aviao* a) {
    return NULL;
}

aviao* arrumaFilaEspera(aviao* A, int valor, int prior, int tempoOcupacao, int tempoChegada) {
    aviao* a2 = new aviao;
    a2->num = valor;
    a2->prior = prior;
    a2->tempOcupacao = tempoOcupacao;
    a2->tempoChegada = tempoChegada;
    a2->link = NULL;

    int pistaIndex;

    pistaIndex = (prior == 1) ? 0 : ((prior == 2) ? 1 : 2); // Determina o índice da pista baseado na prioridade

    if (A == NULL) {
        return a2;
    } else {
        aviao* P = A;
        aviao* ant = NULL;

        while (P != NULL && (prior > P->prior || (prior == P->prior && (tempoChegada > P->tempoChegada || (tempoChegada == P->tempoChegada && tempoOcupacao > P->tempOcupacao))))) {
            ant = P;
            P = P->link;
        }

        if (P == A) {
            a2->link = A;
            return a2;
        } else {
            ant->link = a2;
            a2->link = P;
            return A;
        }
    }
}

aviao* removeFE(aviao* L, int* n, int* prior, int* tempoOcupacao, int* tempoChegada) {
    if (L != NULL) {
        *n = L->num;
        *prior = L->prior;
        *tempoOcupacao = L->tempOcupacao;
        *tempoChegada = L->tempoChegada;
        aviao* AUX = L;
        L = L->link;
        delete AUX;
    }
    return L;
}

void processarEntrada(aviao*& filaEntrada, pista pistas[], int tempoAtual) {
    int pistasF;
    while (filaEntrada != NULL) {
        int num, prior, tempoOcupacao, tempoChegada;
        filaEntrada = removeFE(filaEntrada, &num, &prior, &tempoOcupacao, &tempoChegada);
        pistasF = (prior == 1) ? 0 : (prior == 2) ? 1 : 2;
        pistas[pistasF].filaEspera = arrumaFilaEspera(pistas[pistasF].filaEspera, num, prior, tempoOcupacao, tempoChegada);
    }
}
