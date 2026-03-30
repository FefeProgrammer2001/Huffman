#include "FilaDinamica.hpp"
#include <iostream>

FilaDinamica::FilaDinamica() : cabeca(nullptr), tamanho(0) {}

FilaDinamica::~FilaDinamica() {
    while(cabeca != nullptr) {
        NoFila* temp = cabeca;
        cabeca = cabeca->getProximo();
        delete temp;
    }
}

int FilaDinamica::getTamanho() const { return tamanho; }
bool FilaDinamica::ehVazia() const { return cabeca == nullptr; }

void FilaDinamica::inserir(NoArvore* noArvore) {
    NoFila* novoNo = new NoFila(noArvore);

    if(ehVazia() || novoNo->getFrequencia() <= cabeca->getFrequencia()) {
        novoNo->setProximo(cabeca);
        cabeca = novoNo;
    } else {
        NoFila* atual = cabeca;
        while(atual->getProximo() != nullptr && atual->getProximo()->getFrequencia() < novoNo->getFrequencia()) {
            atual = atual->getProximo();
        }
        novoNo->setProximo(atual->getProximo());
        atual->setProximo(novoNo);
    }

    tamanho++;
}

NoArvore* FilaDinamica::removerMinimo() {
    if(ehVazia()) return nullptr;

    NoFila* removido = cabeca;
    cabeca = cabeca->getProximo();
    tamanho--;

    NoArvore* noArvore = removido->getNoArvore();
    delete removido;
    return noArvore;
}

void FilaDinamica::imprimirFila() const {
    std::cout << "[ ";
    NoFila* atual = cabeca;
    while(atual != nullptr) {
        NoArvore* na = atual->getNoArvore();
        if(na->ehFolha()) {
            std::cout << "No('" << na->getCaractere() << "'," << na->getFrequencia() << ")";
        } else {
            std::cout << "No(interno," << na->getFrequencia() << ")";
        }
        if(atual->getProximo() != nullptr) std::cout << ", ";
        atual = atual->getProximo();
    }
    std::cout << " ]" << std::endl;
}