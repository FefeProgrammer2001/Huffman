#include "Compressor.hpp"
#include "Descompressor.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char **argv) {
    if(argc != 4) {
        std::cout << "Uso:" << std::endl;
        std::cout << "  Comprimir:     " << argv[0] << " -c <entrada> <saida.huff>" << std::endl;
        std::cout << "  Descomprimir:  " << argv[0] << " -d <entrada.huff> <saida>" << std::endl;
        return 1;
    }

    std::string operacao = argv[1];
    std::string arqEntrada = argv[2];
    std::string arqSaida = argv[3];

    try {
        if(operacao == "-c") {
            Compressor compressor;
            compressor.comprimir(arqEntrada, arqSaida);
    
        } else if(operacao == "-d") {
            Descompressor descompressor;
            descompressor.descomprimir(arqEntrada, arqSaida);
        } else {
            std::cerr << "Operacao invalida. Use -c para comprimir ou -d para descomprimir" << std::endl;
            return 1;
        }
    } catch(const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}