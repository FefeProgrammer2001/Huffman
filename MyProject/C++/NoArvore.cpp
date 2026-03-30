#include "NoArvore.hpp"

NoArvore::NoArvore(char caractere, int frequencia)
    : No(frequencia), caractere(caractere), esquerda(nullptr), direita(nullptr) {}

NoArvore::NoArvore(int frequencia, NoArvore* esquerda, NoArvore* direita)
    : No(frequencia), caractere('\0'), esquerda(esquerda), direita(direita) {}

NoArvore::~NoArvore() {
    delete esquerda;
    delete direita;
}

char NoArvore::getCaractere() const { return caractere; }
void NoArvore::setCaractere(char c) { this->caractere = c; }

NoArvore* NoArvore::getEsquerda() const { return esquerda; }
void NoArvore::setEsquerda(NoArvore* esq) { this->esquerda = esq; }

NoArvore* NoArvore::getDireita() const { return direita; }
void NoArvore::setDireita(NoArvore* dir) { this->direita = dir; }

bool NoArvore::ehFolha() const {
    return esquerda == nullptr && direita == nullptr;
}