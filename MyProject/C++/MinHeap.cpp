#include "MinHeap.hpp"

MinHeap::MinHeap() {}

int MinHeap::tamanho() const { return fila.getTamanho(); }

void MinHeap::inserir(NoArvore* noArvore) { fila.inserir(noArvore); }

NoArvore* MinHeap::removerMinimo() { return fila.removerMinimo(); }

void MinHeap::imprimirMinHeap() const { fila.imprimirFila(); }