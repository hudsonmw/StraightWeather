#include "hashmap.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string HashMap::findTime(string date) { return date.substr(14, date.length()); }

int HashMap::findSeconds(string time) { return ((stoi(time.substr(0, 2)) * 60) + stoi(time.substr(3, 2))); }

int HashMap::convertToHashTime(string date) { 
    int sumHours = 0;
    try {
        string year = date.substr(0, 4);
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        int hour = stoi(date.substr(11, 2));
        /* // Testing
            cout << date << "\n";
            cout << year << "/" << month << "/" << day << " : " << hour << endl;
        */
        if (year != "2024") throw string(year + " called they want their year back");
        if (month > 1) sumHours += 24 * 31;
        if (month > 2) sumHours += 24 * 29;
        if (month > 3) sumHours += 24 * 31;
        if (month > 4) sumHours += 24 * 30;
        sumHours += (day - 1) * 24;
        sumHours += hour;
        return sumHours;
    } catch(...) {
        throw string("Are you even trying to give me good data?");
    }
}

void HashMap::insert(string date, double val) {
    int bucket = convertToHashTime(date); 
    if (buckets[bucket] == nullptr) {
        Node* nodeptr = new Node{findTime(date), val, nullptr};
        buckets[bucket] = nodeptr; 
    } else {
        // Old system (unsorted linked lists)
        /*
        Node* nodeptr = new Node{findTime(date), vals, buckets[bucket]};
        buckets[bucket] = nodeptr;*/

        // New system (sorted)
        Node* nodeptr = new Node{findTime(date), val, nullptr};
        Node* curr = buckets[bucket];
        if (findSeconds(curr->time) > findSeconds(nodeptr->time)) {
            buckets[bucket] = nodeptr;
            nodeptr->next = curr;
        } else {
            while (curr->next != nullptr && findSeconds(curr->next->time) < findSeconds(nodeptr->time)) {
                curr = curr->next;
            }
            if (curr->next == nullptr) {
                curr->next = nodeptr;
            } else {
                Node* temp = curr->next;
                curr->next = nodeptr;
                nodeptr->next = temp;
            }
        }
    }
}

double HashMap::operator[](string date) { // This get function WILL create default values
    int bucket = convertToHashTime(date);
    string time = findTime(date);
    if (buckets[bucket] != nullptr) {
        Node* curr = buckets[bucket];
        while (curr->next != nullptr) {
            if (curr->time == time)
                return curr->value;
            curr = curr->next;
        }
        if (curr->time == time)
            return curr->value;
        // Bucket is not empty, but the time does not exist, create default
        curr->next = new Node{time, 0.0, nullptr};
        return curr->next->value;
    }
    // Bucket is empty, create default
    buckets[bucket] = new Node{time, 0.0, nullptr};
    return buckets[bucket]->value;
}

optional<double> HashMap::get(string date) { // This function will NOT create default values, returns nullopt if remove fails
    int bucket = convertToHashTime(date);
    string time = findTime(date);
    if (buckets[bucket] != nullptr) {
        Node* curr = buckets[bucket];
        while (curr != nullptr) {
            if (curr->time == time)
                return curr->value;
            curr = curr->next;
        }
        // Bucket is not empty, but the time does not exist, return null
        return nullopt;
    }
    // Bucket is empty, return null
    return nullopt;
}

bool HashMap::remove(string date) {
    int bucket = convertToHashTime(date);
    string time = findTime(date);
    if (buckets[bucket] != nullptr) {
        Node* curr = buckets[bucket];
        if (curr->time == time) {
            buckets[bucket] = curr->next;
            delete curr;
            return true;
        }
        while (curr->next != nullptr) {
            if (curr->next->time == time) {
                Node* temp = curr->next->next;
                delete curr->next;
                curr->next = temp;
                return true;
            }
            curr = curr->next;
        }
        // Bucket is not empty, but the time does not exist, return false
        return false;
    }
    // Bucket is empty, return false
    return false;
}

string HashMap::getDayData(string date) { // For this function, only "YYYY-MM-DD" is necessary, but including more will not break it
    int startBucket = convertToHashTime(date.substr(0, 10) + " 00");
    int count = 0;
    string returnstr = "hh:mm:ss:   Data\n";
    for (int i = startBucket; i < startBucket + 24; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            count++;
            std::ostringstream oss;
            oss << setw(2) << setfill('0') << i;
            returnstr += oss.str() + ":" + curr->time + ":  ";
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(4);
            ss << curr->value;
            returnstr += ss.str() + "\n";
            curr = curr->next;
        }
    }
    returnstr = "------------------------------------------\nDisplaying day data for: " + date.substr(0, 10) + "\nCount: " + to_string(count) + "\n" + returnstr + "------------------------------------------\n";
    return returnstr;
}