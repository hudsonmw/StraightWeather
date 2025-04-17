
#include <iostream>
#include "CSVLoader.h"
#include "hashmap.h"

int main() {
    CSVLoader loader;
    loader.load_csv("Chicago","wind");

    // Hashmap Testing Section
    /*
    HashMap hashmap;
    vector<double> testVals = {249.1027, 96.221, -42.904};
    string testDate = "2024-03-21 07:25:19"; // Bucket: 1329
    hashmap.insert(testDate, testVals);
    vector<double>& testReturn = hashmap[testDate];
    if (testReturn.size() > 0) {
        for (double value : testReturn) {
            cout << value << " ";
        }
        cout << endl;
    } else {
        cout << "Not found!" << endl;
    }
    testReturn = hashmap["2024-01-02 15:25:39"]; // Bucket: 39
    if (testReturn.size() > 0) {
        for (double value : testReturn) {
            cout << value << " ";
        }
        cout << endl;
    } else {
        cout << "Not found!" << endl;
    }
    vector<double>* testReturnPtr = hashmap.get("2024-01-01 03:06:09"); // Bucket: 3
    if (testReturnPtr != nullptr) {
        for (double value : *testReturnPtr) {
            cout << value << " ";
        }
        cout << endl;
    } else {
        cout << "Not found!" << endl;
    }
    hashmap.insert("2024-01-01 03:00:01", testVals);
    hashmap.insert("2024-01-01 03:00:02", testVals);
    hashmap.insert("2024-01-01 03:00:03", testVals);
    hashmap.remove("2024-01-01 03:00:02");
    hashmap.insert("2024-01-01 00:00:01", testVals);
    hashmap.insert("2024-01-01 01:00:01", testVals);
    hashmap.insert("2024-01-01 02:00:01", testVals);
    hashmap.insert("2024-01-01 04:00:01", testVals);
    hashmap.insert("2024-01-01 05:00:01", testVals);
    hashmap.insert("2024-01-01 06:00:01", testVals);
    hashmap.insert("2024-01-01 10:00:01", testVals);
    hashmap.insert("2024-01-01 15:00:01", testVals);
    hashmap.insert("2024-01-01 20:00:01", testVals);
    hashmap.insert("2024-01-01 22:00:01", testVals);
    hashmap.insert("2024-01-01 23:00:01", testVals);
    cout << hashmap.getDayData("2024-01-01 01:29:31"); // Anything after YYYY-MM-DD won't matter
    */
    return 0;
}