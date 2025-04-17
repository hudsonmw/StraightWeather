#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <vector>
#include <optional>
#include <utility>

class MaxHeap {
    struct Node {
        std::string datetime;   
        double      value;      

        bool operator>(const Node& other) const { return value > other.value; }
    };

    std::vector<Node> data;    

    void heapifyUp  (std::size_t idx);
    void heapifyDown(std::size_t idx);

public:
    MaxHeap() = default;

    void insert(const std::string& datetime, double value);
    std::optional<std::pair<std::string,double>> peek()      const;
    std::optional<std::pair<std::string,double>> extractMax();

    [[nodiscard]] bool   empty() const { return data.empty(); }
    [[nodiscard]] std::size_t size() const { return data.size(); }
};

#endif // HEAP_H
