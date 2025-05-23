#include <vector>
#include "HuffmanNode.hpp"

class MinHeap {
private:
    std::vector<HuffmanNode*>heap;

    void heapifyUp(int index) {
        while(index > 0) {
            int parentIndex = (index - 1) / 2;
            if(heap[index]->frequency < heap[parentIndex]->frequency) {
                std::swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while(index < size) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if(leftChild < size && heap[leftChild]->frequency < heap[smallest]->frequency) {
                smallest = leftChild;
            }
            if(rightChild < size && rightChild < size && heap[rightChild]->frequency < heap[smallest]->frequency) {
                smallest = rightChild;
            }
            if(smallest != index) {
                std::swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    void insert(HuffmanNode* node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    HuffmanNode* extractMin() {
        if(heap.empty()) return nullptr;
        HuffmanNode* minNode = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if(!heap.empty()) {
            heapifyDown(0);
        }
        return minNode;
    }

    bool isEmpty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }
};
