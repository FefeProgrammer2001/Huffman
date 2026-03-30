#include "Arvore.hpp"
#include <iostream>

Arvore::Arvore(NoArvore* raiz) : raiz(raiz) {}

Arvore::~Arvore() {
    delete raiz;
}

NoArvore* Arvore::getRaiz() const { return raiz; }

void Arvore::gerarTabela(std::string tabela[]) const {
    gerarCodigos(raiz, "", tabela);
}

void Arvore::gerarCodigos(NoArvore* no, const std::string& codigo, std::string tabela[]) const {
    if(no == nullptr) return;

    if(no->ehFolha()) {
        tabela[(unsigned char) no->getCaractere()] = codigo.empty() ? "0" : codigo;
        return;
    }

    gerarCodigos(no->getEsquerda(), codigo + "0", tabela);
    gerarCodigos(no->getDireita(), codigo + "1", tabela);
}

void Arvore::imprimirArvore() const {
    imprimirPreOrdem(raiz, true);
}

void Arvore::imprimirPreOrdem(NoArvore* no, bool ehRaiz) const {
    if(no == nullptr) return;

    if(ehRaiz) {
        std::cout << "- (RAIZ, " << no->getFrequencia() << ")" << std::endl;
    } else if(no->ehFolha()) {
        std::cout << "- ('" << no->getCaractere() << "', " << no->getFrequencia() << ")" << std::endl;
    } else {
        std::cout << "- (interno, " << no->getFrequencia() << ")" << std::endl;
    }

    imprimirPreOrdem(no->getEsquerda(), false);
    imprimirPreOrdem(no->getDireita(), false);
}