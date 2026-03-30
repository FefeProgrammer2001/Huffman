#include "Compressor.hpp"
#include "MinHeap.hpp"
#include "Arvore.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <stdexcept>

static const char MAGIC[4] = { 'H', 'U', 'F', 'F' };
static const int VERSAO_FORMATO = 1;

static void writeInt(std::ofstream& out, int value) {
    unsigned char bytes[4];
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8)  & 0xFF;
    bytes[3] = value         & 0xFF;
    out.write(reinterpret_cast<char*>(bytes), 4);
}

void Compressor::comprimir(const std::string& caminhoEntrada, const std::string& caminhoSaida) {
    auto tempoInicio = std::chrono::high_resolution_clock::now();

    std::ifstream arqEntrada(caminhoEntrada, std::ios::binary);
    if(!arqEntrada) throw std::runtime_error("Nao foi possivel abrir: " + caminhoEntrada);

    arqEntrada.seekg(0, std::ios::end);
    int tamanhoArquivo = (int) arqEntrada.tellg();
    arqEntrada.seekg(0, std::ios::beg);

    unsigned char* bytes = new unsigned char[tamanhoArquivo];
    arqEntrada.read(reinterpret_cast<char*>(bytes), tamanhoArquivo);
    arqEntrada.close();

    int frequencias[256] = {};
    for(int i = 0; i < tamanhoArquivo; i++) frequencias[bytes[i]]++;

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "ETAPA 1: Tabela de Frequencia de Caracteres" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    for(int i = 0; i < 256; i++) {
        if(frequencias[i] > 0)
            printf("Caractere '%c' (ASCII: %d): %d\n", (char)i, i, frequencias[i]);
    }

    MinHeap heap;
    for(int i = 0; i < 256; i++) {
        if(frequencias[i] > 0)
            heap.inserir(new NoArvore((char)i, frequencias[i]));
    }

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "ETAPA 2: Min-Heap Inicial (Fila Dinamica)" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    heap.imprimirMinHeap();

    while(heap.tamanho() > 1) {
        NoArvore* esq = heap.removerMinimo();
        NoArvore* dir = heap.removerMinimo();
        heap.inserir(new NoArvore(esq->getFrequencia() + dir->getFrequencia(), esq, dir));
    }

    Arvore arvore(heap.removerMinimo());

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "ETAPA 3: Arvore de Huffman" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    arvore.imprimirArvore();

    std::string tabela[256];
    arvore.gerarTabela(tabela);

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "ETAPA 4: Tabela de Codigos de Huffman" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    for(int i = 0; i < 256; i++) {
        if(!tabela[i].empty())
            printf("Caractere '%c': %s\n", (char)i, tabela[i].c_str());
    }

    std::string bitString;
    for(int i = 0; i < tamanhoArquivo; i++) bitString += tabela[bytes[i]];

    int padding = 8 - (bitString.size() % 8);
    if(padding == 8) padding = 0;
    for(int i = 0; i < padding; i++) bitString += '0';

    int tamComprimido = (int)bitString.size() / 8;
    unsigned char* dadosComprimidos = new unsigned char[tamComprimido];

    for(int i = 0; i < tamComprimido; i++) {
        unsigned char byte = 0;
        for(int b = 0; b < 8; b++)
            if(bitString[i * 8 + b] == '1') byte |= (1 << (7 - b));
        dadosComprimidos[i] = byte;
    }

    std::ofstream arqSaida(caminhoSaida, std::ios::binary);
    if(!arqSaida) {
        delete[] bytes;
        delete[] dadosComprimidos;
        throw std::runtime_error("Nao foi possivel criar: " + caminhoSaida);
    }

    arqSaida.write(MAGIC, 4);
    writeInt(arqSaida, VERSAO_FORMATO);
    writeInt(arqSaida, padding);
    for(int i = 0; i < 256; i++) writeInt(arqSaida, frequencias[i]);
    arqSaida.write(reinterpret_cast<char*>(dadosComprimidos), tamComprimido);
    arqSaida.close();

    delete[] bytes;
    delete[] dadosComprimidos;

    auto tempoFim = std::chrono::high_resolution_clock::now();
    long long tempoMs = std::chrono::duration_cast<std::chrono::milliseconds>(tempoFim - tempoInicio).count();

    int bitsOriginais = tamanhoArquivo * 8;
    int bitsComprimidos = (int)bitString.size() - padding;
    double taxa = 100.0 * (1.0 - (double) bitsComprimidos / bitsOriginais);

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "ETAPA 5: Remuso da Compressao" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    printf("Tamanho original....: %d bits (%d bytes)\n", bitsOriginais, tamanhoArquivo);
    printf("Tamanho comprimido..: %d bits (%d bytes)\n", bitsComprimidos, (bitsComprimidos + 7) / 8);
    printf("Taxa de compressao..: %.2f%%\n", taxa);
    printf("Tempo de execucao...: %lld ms\n", tempoMs);
    std::cout << "--------------------------------------------------" << std::endl;
}