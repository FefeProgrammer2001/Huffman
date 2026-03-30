#pragma once
#include "NoFila.hpp"
#include "NoArvore.hpp"

class FilaDinamica {
private:
    NoFila* cabeca;
    int tamanho;

public:
    FilaDinamica();
    ~FilaDinamica();

    int getTamanho() const;
    bool ehVazia() const;

    void inserir(NoArvore* noArvore);
    NoArvore* removerMinimo();
    void imprimirFila() const;
};