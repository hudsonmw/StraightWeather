#include "heap.h"
#include <utility>
#include <algorithm>
#include <limits>

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

optional<pair<string,double>> MaxHeap::findDate(const string& datetime) const {
    for (const auto& node : data) {
        if (node.datetime == datetime) {
            return make_pair(node.datetime, node.value);
        }
    }
    return nullopt;
}

optional<pair<string,double>> MaxHeap::getHighest() const {
    return peek();
}

optional<pair<string,double>> MaxHeap::getLowest() const {
    if (data.empty()) return nullopt;
    auto it = min_element(data.begin(), data.end(), [](auto& a, auto& b){ return a.value < b.value; });
    return make_pair(it->datetime, it->value);
}

optional<pair<string,double>> MaxHeap::getMostRecent() const {
    if (data.empty()) return nullopt;
    auto it = max_element(data.begin(), data.end(), [](auto& a, auto& b){ return a.datetime < b.datetime; });
    return make_pair(it->datetime, it->value);
}

optional<double> MaxHeap::getAverageOnDay(const string& date) const {
    double sum = 0.0;
    size_t count = 0;
    for (const auto& node : data) {
        if (node.datetime.rfind(date, 0) == 0) {
            sum += node.value;
            ++count;
        }
    }
    if (count == 0) return nullopt;
    return sum / count;
}

optional<pair<string,double>> MaxHeap::getHighestOnDay(const string& date) const {
    double best = numeric_limits<double>::lowest();
    string bestDt;
    for (const auto& node : data) {
        if (node.datetime.rfind(date, 0) == 0 && node.value > best) {
            best = node.value;
            bestDt = node.datetime;
        }
    }
    if (bestDt.empty()) return nullopt;
    return make_pair(bestDt, best);
}

optional<pair<string,double>> MaxHeap::getLowestOnDay(const string& date) const {
    double best = numeric_limits<double>::max();
    string bestDt;
    for (const auto& node : data) {
        if (node.datetime.rfind(date, 0) == 0 && node.value < best) {
            best = node.value;
            bestDt = node.datetime;
        }
    }
    if (bestDt.empty()) return nullopt;
    return make_pair(bestDt, best);
}

optional<double> MaxHeap::getAverageForMonth(const string& month) const {
    string prefix = (month.size() == 2 ? string("2024-") + month : month);
    double sum = 0.0;
    size_t count = 0;
    for (const auto& node : data) {
        if (node.datetime.rfind(prefix, 0) == 0) {
            sum += node.value;
            ++count;
        }
    }
    if (count == 0) return nullopt;
    return sum / count;
}