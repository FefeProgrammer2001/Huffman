#include "NoFila.hpp"

NoFila::NoFila(NoArvore* noArvore)
    : No(noArvore->getFrequencia()), noArvore(noArvore), proximo(nullptr) {}

NoArvore* NoFila::getNoArvore() const { return noArvore; }
void NoFila::setNoArvore(NoArvore* na) { this->noArvore = na; }

NoFila* NoFila::getProximo() const { return proximo; }
void NoFila::setProximo(NoFila* prox) { this->proximo = prox; }