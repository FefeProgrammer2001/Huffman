#pragma once
#include "No.hpp"
#include "NoArvore.hpp"

class NoFila : public No {
private:
    NoArvore* noArvore;
    NoFila* proximo;

public:
    explicit NoFila(NoArvore* noArvore);
    ~NoFila() override = default;

    NoArvore* getNoArvore() const;
    void setNoArvore(NoArvore* noArvore);

    NoFila* getProximo() const;
    void setProximo(NoFila* proximo);
};