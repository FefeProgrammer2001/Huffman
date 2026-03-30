#pragma once
#include "FilaDinamica.hpp"

class MinHeap {
private:
    FilaDinamica fila;

public:
    MinHeap();

    int tamanho() const;
    void inserir(NoArvore* noArvore);
    NoArvore* removerMinimo();
    void imprimirMinHeap() const;
};