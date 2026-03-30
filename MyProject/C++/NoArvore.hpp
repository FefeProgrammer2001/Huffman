#pragma once
#include "No.hpp"

class NoArvore : public No {
private:
    char caractere;
    NoArvore* esquerda;
    NoArvore* direita;

public:
    NoArvore(char caractere, int frequencia);

    NoArvore(int frequencia, NoArvore* esquerda, NoArvore* direita);
    ~NoArvore() override;

    char getCaractere() const;
    void setCaractere(char caractere);

    NoArvore* getEsquerda() const;
    void setEsquerda(NoArvore* esquerda);

    NoArvore* getDireita() const;
    void setDireita(NoArvore* direita);

    bool ehFolha() const;
};