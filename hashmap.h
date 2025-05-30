#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <optional>
#include <string>
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
        string time;
        double value;
        Node* next = nullptr;
    };
    int size; // Number of buckets, hours from 2024-01-01:00 -> 2024-05-18:23
    vector<Node*> buckets;
    int convertToHashTime(string date);
    string convertFromHashTime(int hours);
    string findTime(string date);
    int findSeconds(string time);
public:
    HashMap(int s = 3335) {
        size = s;
        buckets.resize(size, nullptr);
    }
    void insert(string date, double value);
    optional<double> get(string date);
    double operator[](string date);
    bool remove(string date);
    string getDayData(string date);
    string getHighest();
    string getLowest();
    string getAverage();
    string getDayHighest(string date);
    string getDayLowest(string date);
    string getDayAverage(string date);
    string getMonthHighest(string date);
    string getMonthLowest(string date);
    string getMonthAverage(string date);
};



#endif //HASHMAP_H
