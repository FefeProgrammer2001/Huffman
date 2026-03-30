#include "Descompressor.hpp"
#include "MinHeap.hpp"
#include "Arvore.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cstring>

static const char MAGIC[4] = { 'H', 'U', 'F', 'F' };

static int readInt(std::ifstream& in) {
    unsigned char bytes[4];
    in.read(reinterpret_cast<char*>(bytes), 4);
    return (bytes[0] << 24)| (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

void Descompressor::descomprimir(const std::string& caminhoEntrada, const std::string& caminhoSaida) {
    auto tempoInicio = std::chrono::high_resolution_clock::now();

    std::ifstream in(caminhoEntrada, std::ios::binary);
    if(!in) throw std::runtime_error("Nao foi possivel abrir: " + caminhoEntrada);

    char magicLido[4];
    in.read(magicLido, 4);
    if(std::memcmp(magicLido, MAGIC, 4) != 0)
        throw std::runtime_error("Formato invalido: cabecalho HUFF nao encontrado");
    
    int versao = readInt(in);
    if(versao != 1)
        throw std::runtime_error("Versao do formato nao suportada");
        
    int padding = readInt(in);

    int frequencias[256] = {};
    for(int i = 0; i < 256; i++) frequencias[i] = readInt(in);

    int cabecalhosBytes = 4 + 4 + 4 + (256 * 4);
    in.seekg(0, std::ios::end);
    int tamTotal = (int) in.tellg();
    int tamDados = tamTotal - cabecalhosBytes;
    in.seekg(cabecalhosBytes, std::ios::beg);

    unsigned char* dadosComprimidos = new unsigned char[tamDados];
    in.read(reinterpret_cast<char*>(dadosComprimidos), tamDados);
    in.close();

    MinHeap heap;
    for(int i = 0; i < 256; i++) {
        if(frequencias[i] > 0)
            heap.inserir(new NoArvore((char)i, frequencias[i]));
    }
    while(heap.tamanho() > 1) {
        NoArvore* esq = heap.removerMinimo();
        NoArvore* dir = heap.removerMinimo();
        heap.inserir(new NoArvore(esq->getFrequencia() + dir->getFrequencia(), esq, dir));
    }

    Arvore arvore(heap.removerMinimo());

    int totalBitsBrutos = tamDados * 8;
    char* bitString = new char[totalBitsBrutos + 1];

    for(int i = 0; i < tamDados; i++) {
        for(int b = 7; b >= 0; b--)
            bitString[i * 8 + (7 - b)] = ((dadosComprimidos[i] >> b) & 1) ? '1' : '0';  
    }
    bitString[totalBitsBrutos] = '\0';

    int totalBits = totalBitsBrutos - padding;

    unsigned char* saida = new unsigned char[totalBits];
    int tamSaida = 0;

    NoArvore* atual = arvore.getRaiz();
    for(int i = 0; i < totalBits; i++) {
        atual = (bitString[i] == '0') ? atual->getEsquerda() : atual->getDireita();
        if(atual->ehFolha()) {
            saida[tamSaida++] = (unsigned char) atual->getCaractere();
            atual = arvore.getRaiz();
        }
    }

    std::ofstream arqSaida(caminhoSaida, std::ios::binary);
    if(!arqSaida) {
        delete[] dadosComprimidos;
        delete[] bitString;
        delete[] saida;
        throw std::runtime_error("Nao foi possivel criar: " + caminhoSaida);
    }
    arqSaida.write(reinterpret_cast<char*>(saida), tamSaida);
    arqSaida.close();

    delete[] dadosComprimidos;
    delete[] bitString;
    delete[] saida;

    auto tempoFim = std::chrono::high_resolution_clock::now();
    long long tempoMs = std::chrono::duration_cast<std::chrono::milliseconds>(tempoFim - tempoInicio).count();
    std::cout << "Descompressao concluida em " << tempoMs << " ms -> " << caminhoSaida << std::endl;
}