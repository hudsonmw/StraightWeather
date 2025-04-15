#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
using namespace std;

/*-----------------
   PROPOSED HASH FUNCTION - Days from 2024-01-01

Number of days from 2024-01-01
Ex. 2024-01-01 == 1 - 1 == 0
    2024-02-01 == 31 + 1 - 1 == 31
    2024-05-18 == (31 + 28 + 31 + 30) + 18 - 1 == 137

Days in each (necessary) month:
    Jan: 31
    Feb: 28
    March: 31
    April: 30

-----------------*/
/*-----------------
   PROPOSED HASH FUNCTION - Hours from 01-01:00

Number of days from 2024-01-01
Ex. 2024-01-01:00 == 0 hours
    2024-02-01:00 == 24(31 + 1) == 744 hours
    2024-05-18:09 == 24((31 + 29 + 31 + 30) + 18 - 1) + 9 == 3321 hours

Days in each (necessary) month:
    Jan: 31 days == 744 hours
    Feb: 29 days == 696 hours
    March: 31 days == 744 hours
    April: 30 days == 720 hours

-----------------*/

class HashMap {
    struct Node {
        vector<bool> values;
        Node* next = nullptr;
    };
    int size; // Number of buckets, hours from 2024-01-01:00 -> 2024-05-18:23
    vector<Node*> buckets;
public:
    HashMap(int s = 3335) {
        size = s;
        buckets.resize(size, nullptr);
    }
    void insert(string date, vector<bool> values);
    void remove();
    bool isEmpty();
    int convertToHashTime(string date);
};



#endif //HASHMAP_H
