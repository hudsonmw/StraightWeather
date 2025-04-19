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
    [[nodiscard]] bool   empty() const { return data.empty(); }
    [[nodiscard]] std::size_t size() const { return data.size(); }
    std::optional<std::pair<std::string,double>> peek() const;
    std::optional<std::pair<std::string,double>> extractMax();

    std::optional<std::pair<std::string,double>> findDate(const std::string& datetime) const;

    std::optional<std::pair<std::string,double>> getHighest() const;
    std::optional<std::pair<std::string,double>> getLowest() const;

    std::optional<std::pair<std::string,double>> getMostRecent() const;

    std::optional<double> getAverageOnDay(const std::string& date) const;
    std::optional<std::pair<std::string,double>> getHighestOnDay(const std::string& date) const;
    std::optional<std::pair<std::string,double>> getLowestOnDay(const std::string& date) const;
    std::optional<double> getAverageForMonth(const std::string& month) const;
};

#endif // HEAP_H