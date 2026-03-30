#pragma once
#include "NoArvore.hpp"
#include <string>

class Arvore {
private:
    NoArvore* raiz;

    void gerarCodigos(NoArvore* no, const std::string& codigo, std::string tabela[]) const;
    void imprimirPreOrdem(NoArvore* no, bool ehRaiz) const;

public:
    explicit Arvore(NoArvore* raiz);
    ~Arvore();

    NoArvore* getRaiz() const;
    void gerarTabela(std::string tabela[]) const;
    void imprimirArvore() const;
};