#include "hashmap.h"
#include <iostream>
#include <vector>

using namespace std;

int HashMap::convertToHashTime(string date) { // hudson
    int sumHours = 0; // hudson
    int year = stoi(date.substr(0, 4)); // hudson
    int month = stoi(date.substr(5, 2)); // hudson
    int day = stoi(date.substr(8, 2)); // hudson
    int hour = stoi(date.substr(11, 2)); // hudson
    /* // Testing // hudson
    cout << date << "\n"; // hudson
    cout << year << "/" << month << "/" << day << " : " << hour << endl;  // hudson
    */  // hudson
    if (year != 2024) throw string(year + " called they want their year back dumbass");  // hudson
    if (month > 1) sumHours += 24 * 31; // hudson
    if (month > 2) sumHours += 24 * 29; // hudson
    if (month > 3) sumHours += 24 * 31; // hudson
    if (month > 4) sumHours += 24 * 30; // hudson
    sumHours += (day - 1) * 24; // hudson
    sumHours += hour; // hudson
    return sumHours; // hudson
} // hudson
// hudson
void HashMap::insert(string date, vector<bool> vals) { // hudson
    int bucket = convertToHashTime(date); // hudson
    if (buckets[bucket] == nullptr) { // hudson
        Node* nodeptr = new Node; // hudson
        nodeptr->next = nullptr; // hudson
        nodeptr->values = vals; // hudson
        buckets[bucket] = nodeptr; // hudson
    } // hudson
} // hudson // hudson // hudson // hudson // hudson
