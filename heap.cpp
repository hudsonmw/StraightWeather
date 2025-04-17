#include "heap.h"
#include <utility>   

using namespace std;

void MaxHeap::heapifyUp(size_t idx)
{
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (data[idx] > data[parent]) {
            swap(data[idx], data[parent]);
            idx = parent;
        } else
            break;
    }
}

void MaxHeap::heapifyDown(size_t idx)
{
    const size_t n = data.size();
    while (true) {
        size_t left  = 2 * idx + 1;
        size_t right = 2 * idx + 2;
        size_t largest = idx;

        if (left  < n && data[left]  > data[largest]) largest = left;
        if (right < n && data[right] > data[largest]) largest = right;

        if (largest != idx) {
            swap(data[idx], data[largest]);
            idx = largest;
        } else
            break;
    }
}

void MaxHeap::insert(const string& datetime, double value)
{
    data.push_back({datetime, value});
    heapifyUp(data.size() - 1);
}

optional<pair<string,double>> MaxHeap::peek() const
{
    if (data.empty()) return nullopt;
    const Node& top = data.front();
    return make_pair(top.datetime, top.value);
}

optional<pair<string,double>> MaxHeap::extractMax()
{
    if (data.empty()) return nullopt;

    Node top = data.front();
    data.front() = data.back();
    data.pop_back();
    if (!data.empty())
        heapifyDown(0);

    return make_pair(top.datetime, top.value);
}
