#ifndef HUFFMAN_NODE_HPP
#define HUFFMAN_NODE_HPP

class HuffmanNode {
public:
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char character, int frequency)
        : character(character), frequency(frequency), left(nullptr), right(nullptr) {}
    
    HuffmanNode(int frequency, HuffmanNode* left, HuffmanNode* right)
        : character('\0'), frequency(frequency), left(left), right(right) {}
    
    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

#endif
