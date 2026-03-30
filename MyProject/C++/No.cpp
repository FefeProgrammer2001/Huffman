#include "No.hpp"

No::No(int frequencia) : frequencia(frequencia) {}

int No::getFrequencia() const {
    return frequencia;
}

void No::setFrequencia(int frequencia) {
    this->frequencia = frequencia;
}