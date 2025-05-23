#include <iostream>
#include "HuffmanCoding.hpp"

int main() {
    char continueChoice;
    std::string operation, input, output, codeTable;

    do {
        output.clear();

        std::cout << "Do you want to encode or decode? ('encode'/'decode'): ";
        std::getline(std::cin, operation);

        if(operation == "encode") {
            std::cout << "Enter the text to encode: ";
            std::getline(std::cin, input);
            if(input.empty()) {
                std::cerr << "Input text is empty. Exiting..." << std::endl;
                return 1;
            }
            HuffmanCoding huffmanCoding;
            huffmanCoding.encode(input, output, codeTable);
            std::cout << "\nOriginal text: " << input << std::endl;
            std::cout << "Encoded text: " << output << std::endl;
            std::cout << "Code table: " << codeTable << std::endl;
            std::cout << std::endl;
        } else if(operation == "decode") {
            std::cout << "Enter the code table: ";
            std::getline(std::cin, codeTable);
            std::cout << "Enter the encoded text (binary string): ";
            std::getline(std::cin, input);
            if(input.empty()) {
                std::cerr << "Input text is empty. Exiting..." << std::endl;
                return 1;
            }
            for(char c : input) {
                if(c != '0' && c != '1') {
                    std::cerr << "Invalid encoded text. Must contains only 0s and 1s. Exiting..." << std::endl;
                    return 1;
                }
            }
            HuffmanCoding huffmanCoding;
            huffmanCoding.decode(codeTable, input, output);
            std::cout << "\nEncoded text: " << input << std::endl;
            std::cout << "Decoded text: " << output << std::endl;
            std::cout << std::endl;
        } else {
            std::cerr << "Invalid operation. Please enter 'encode' or 'decode'. Exiting..." << std::endl;
            return 1;
        }
        std::cout << "Do you want to continue? y/n: ";
        std::cin >> continueChoice;
        std::cin.ignore();

    } while (continueChoice == 'y');

    return 0;
}
