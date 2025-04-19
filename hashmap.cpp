#include "hashmap.h"

#include <float.h>
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

string HashMap::convertFromHashTime(int hours) {
    string toReturn = "";
    string month = "";
    string days = "";
    string hrs = "";
    if (hours > 24 * 31) {
        hours -= 24 * 31;
        if (hours > 24 * 29) {
            hours -= 24 * 29;
            if (hours > 24 * 31) {
                hours -= 24 * 31;
                if (hours > 24 * 30) { // May
                    hours -= 24 * 30;
                    month = "05-";
                } else { // April
                    month = "04-";
                }
            } else { // March
                month = "03-";
            }
        } else { // February
            month = "02-";
        }
    } else { // January
        month = "01-";
    }
    days = to_string((hours - (hours % 24)) / 24);
    if (days.length() < 2) days = "0" + days;
    hrs = to_string(hours % 24);
    return "2024-" + month + days + " " + hrs;;
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

string HashMap::getHighest() {
    double highest = DBL_MIN;
    string d = "";
    for (int i = 0; i < buckets.size(); i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            if (curr->value > highest) {
                highest = curr->value;
                d = convertFromHashTime(i) + ":" + curr->time;
            }
            curr = curr->next;
        }
    }
    string returnstr = "Highest: ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << highest;
    returnstr += ss.str() + " on: " + d;
    return returnstr;
}

string HashMap::getLowest() {
    double lowest = DBL_MAX;
    string d = "";
    for (int i = 0; i < buckets.size(); i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            if (curr->value < lowest) {
                lowest = curr->value;
                d = convertFromHashTime(i) + ":" + curr->time;
            }
            curr = curr->next;
        }
    }
    string returnstr = "Lowest: ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << lowest;
    returnstr += ss.str() + " on: " + d;
    return returnstr;
}

string HashMap::getAverage() {
    double sum = 0.0;
    int count = 0;
    for (int i = 0; i < buckets.size(); i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            sum += curr->value;
            count++;
            curr = curr->next;
        }
    }
    string returnstr = "Average: ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << sum / count;
    returnstr += ss.str();
    return returnstr;
}

string HashMap::getDayHighest(string date) {
    int startBucket = convertToHashTime(date.substr(0, 10) + " 00");
    double highest = DBL_MIN;
    string d = "";
    for (int i = startBucket; i < startBucket + 24; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            if (curr->value > highest) {
                highest = curr->value;
                if (i < 10) {
                    d = "0" + to_string(i) + ":" + curr->time;
                } else {
                    d = to_string(i) + ":" + curr->time;
                }
            }
            curr = curr->next;
        }
    }
    string returnstr = "Highest on " + date.substr(0, 10) + " at " + d + " : ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << highest;
    returnstr += ss.str();
    return returnstr;
}

string HashMap::getDayLowest(string date) {
    int startBucket = convertToHashTime(date.substr(0, 10) + " 00");
    double lowest = DBL_MAX;
    string d = "";
    for (int i = startBucket; i < startBucket + 24; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            if (curr->value < lowest) {
                lowest = curr->value;
                if (i < 10) {
                    d = "0" + to_string(i) + ":" + curr->time;
                } else {
                    d = to_string(i) + ":" + curr->time;
                }
            }
            curr = curr->next;
        }
    }
    string returnstr = "Lowest on " + date.substr(0, 10) + " at " + d + " : ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << lowest;
    returnstr += ss.str();
    return returnstr;
}

string HashMap::getDayAverage(string date) {
    int startBucket = convertToHashTime(date.substr(0, 10) + " 00");
    double sum = 0.0;
    int count = 0;
    for (int i = startBucket; i < startBucket + 24; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            sum += curr->value;
            count++;
            curr = curr->next;
        }
    }
    string returnstr = "Average on " + date.substr(0, 10) + " : ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << sum / count;
    returnstr += ss.str();
    return returnstr;
}

string HashMap::getMonthHighest(string date) {
    int startbucket = convertToHashTime(date.substr(0, 7) + "-01 00");
    int endbucket;
    if (date.substr(5, 2) != "05") {
        int month = stoi(date.substr(5, 2));
        endbucket = convertToHashTime("2024-0" + to_string(month+1) + "-01 00");
    } else {
        endbucket = buckets.size();
    }
    double highest = DBL_MIN;
    string d = "";
    for(int i = startbucket; i < endbucket; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            if (curr->value > highest) {
                highest = curr->value;
                d = convertFromHashTime(i) + ":" + curr->time;
            }
            curr = curr->next;
        }
    }
    string returnstr = "Highest on " + d.substr(0, 10) + " at " + d.substr(11, 8) + " : ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << highest;
    returnstr += ss.str();
    return returnstr;
}

string HashMap::getMonthLowest(string date) {
    int startbucket = convertToHashTime(date.substr(0, 7) + "-01 00");
    int endbucket;
    if (date.substr(5, 2) != "05") {
        int month = stoi(date.substr(5, 2));
        endbucket = convertToHashTime("2024-0" + to_string(month+1) + "-01 00");
    } else {
        endbucket = buckets.size();
    }
    double lowest = DBL_MAX;
    string d = "";
    for(int i = startbucket; i < endbucket; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            if (curr->value < lowest) {
                lowest = curr->value;
                d = convertFromHashTime(i) + ":" + curr->time;
            }
            curr = curr->next;
        }
    }
    string returnstr = "Highest on " + d.substr(0, 10) + " at " + d.substr(11, 8) + " : ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << lowest;
    returnstr += ss.str();
    return returnstr;
}

string HashMap::getMonthAverage(string date) {
    int startbucket = convertToHashTime(date.substr(0, 7) + "-01 00");
    int endbucket;
    if (date.substr(5, 2) != "05") {
        int month = stoi(date.substr(5, 2));
        endbucket = convertToHashTime("2024-0" + to_string(month+1) + "-01 00");
    } else {
        endbucket = buckets.size();
    }
    double sum = 0.0;
    int count = 0;
    for(int i = startbucket; i < endbucket; i++) {
        Node* curr = buckets[i];
        while (curr != nullptr) {
            sum += curr->value;
            count++;
            curr = curr->next;
        }
    }
    string returnstr = "Average for the month of ";
    if (date.substr(5, 2) == "01") returnstr += "January";
    if (date.substr(5, 2) == "02") returnstr += "February";
    if (date.substr(5, 2) == "03") returnstr += "March";
    if (date.substr(5, 2) == "04") returnstr += "April";
    if (date.substr(5, 2) == "05") returnstr += "May";
    returnstr += " : ";
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(4);
    ss << sum / count;
    returnstr += ss.str();
    return returnstr;
}