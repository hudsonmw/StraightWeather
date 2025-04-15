#include "hashmap.h"

using namespace std;

HashMap::HashMap() {
    this->buckets = new vector<int, vector<double>>(this->size);
}