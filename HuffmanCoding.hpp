#include <unordered_map>
#include "HuffmanNode.hpp"
#include "MinHeap.hpp"
#include <string>
#include <sstream>

class HuffmanCoding {
private:
    HuffmanNode* root;
    std::unordered_map<char, std::string> codes;

    void buildTree(const std::unordered_map<char, int>& frequencyMap) {
        MinHeap minHeap;

        for(const auto& entry : frequencyMap) {
            minHeap.insert(new HuffmanNode(entry.first, entry.second));
        }

        while(minHeap.size() > 1) {
            HuffmanNode* left = minHeap.extractMin();
            HuffmanNode* right = minHeap.extractMin();
            HuffmanNode* parent = new HuffmanNode(left->frequency + right->frequency, left, right);
            minHeap.insert(parent);
        }

        root = minHeap.extractMin();
    }

    void generateCodes(HuffmanNode* node, const std::string& code) {
        if(node->isLeaf()) {
            codes[node->character] = code;
            return;
        }
        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }

    void serializeCodes(std::string& output) {
        for(const auto& pair : codes) {
            output += pair.first + std::string(":") + pair.second + ",";
        }
        if(!output.empty()) {
            output.pop_back();
        }
    }

    void deserializeCodes(const std::string& input) {
        std::istringstream ss(input);
        std::string item;
        while(std::getline(ss, item, ',')) {
            char character = item[0];
            std::string code = item.substr(2);
            codes[character] = code;
        }
    }

    void rebuildTree() {
        root = new HuffmanNode('\0', 0);
        for(const auto& pair : codes) {
            char character = pair.first;
            std::string code = pair.second;
            HuffmanNode* current = root;
            for(size_t i = 0; i < code.length(); i++) {
                if(code[i] == '0') {
                    if(!current->left) {
                        current->left = new HuffmanNode('\0', 0);
                    }
                    current = current->left;
                } else if(code[i] == '1') {
                    if(!current->right) {
                        current->right = new HuffmanNode('\0', 0);
                    }
                    current = current->right;
                }
                if(i == code.length() - 1) {
                    current->character = character;
                }
            }
        }
    }

public:
    HuffmanCoding() : root(nullptr) {}

    void encode(const std::string& input, std::string& encodedOutput, std::string& codeTable) {
        std::unordered_map<char, int> frequencyMap;
        for(char character : input) {
            frequencyMap[character]++;
        }
        buildTree(frequencyMap);
        generateCodes(root, "");
        serializeCodes(codeTable);
        for(char character : input) {
            encodedOutput += codes[character];
        }
    }

    void decode(const std::string& codeTable, const std::string& encodedInput, std::string& decodedOutput) {
        codes.clear();
        deserializeCodes(codeTable);
        rebuildTree();
        HuffmanNode* current = root;
        for(char bit : encodedInput) {
            current = (bit == '0') ? current->left : current->right;
            if(current->isLeaf()) {
                decodedOutput += current->character;
                current = root;
            }
        }
    }
};
