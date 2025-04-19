#include <vector>
#include <iostream>
#include "CSVLoader.h"
#include "hashmap.h"
#include <chrono>

int main() {
    std::cout << "Welcome to StraightWeather!" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    bool city_bool = false;
    std::vector<std::string> cities = {"Chicago","New York","Phoenix","Philadelphia","Houston","San Antonio","San Diego","Dallas","San Jose","Los Angeles"};
    std::string city;
    while(!city_bool) {
        std::cout << "Avalible Cities:" << std::endl;
        std::cout << std::endl;
        std::cout << "- Chicago" << std::endl;
        std::cout << "- Dallas" << std::endl;
        std::cout << "- Houston" << std::endl;
        std::cout << "- Los Angeles" << std::endl;
        std::cout << "- New York" << std::endl;
        std::cout << "- Philadelphia" << std::endl;
        std::cout << "- Phoenix" << std::endl;
        std::cout << "- San Antonio" << std::endl;
        std::cout << "- San Diego" << std::endl;
        std::cout << "- San Jose" << std::endl;
        std::cout << "What city would you like to see data for?" << std::endl;
        std::getline(std::cin,city);
        if(std::find(cities.begin(),cities.end(),city) == cities.end()) {
            std::cout << "Please enter a valid city name!" << std::endl;
        } else {
            city_bool = true;
        }
    }
    std::cout << "-------------------------------------------" << std::endl;
    bool att_bool = false;
    std::vector<std::string> attributes = {"Temperature","Humidity","Percipitation","Wind"};
    std::string att;
    while(!att_bool) {
        std::cout << "Avalible Attributes:" << std::endl;
        std::cout << std::endl;
        std::cout << "- Temperature" << std::endl;
        std::cout << "- Humidity" << std::endl;
        std::cout << "- Precipitation" << std::endl;
        std::cout << "- Wind" << std::endl;
        std::cout << "What attribute would you like to view data for?" << std::endl;
        std::cin >> att;
        if(std::find(attributes.begin(),attributes.end(),att) == attributes.end()) {
            std::cout << "Please enter a valid attribute name!" << std::endl;
        } else {
            att_bool = true;
        }
    }
    CSVLoader loader;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Loading data..." << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // Heap heap;
    HashMap hashmap;
    loader.load_csv(hashmap, city,att);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Data loaded!" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;

    cout << hashmap.getHighest() << endl;
    cout << hashmap.getLowest() << endl;
    cout << hashmap.getAverage() << endl;
    cout << hashmap.getDayHighest("2024-01-01") << endl;
    cout << hashmap.getDayLowest("2024-01-01") << endl;
    cout << hashmap.getDayAverage("2024-01-01") << endl;
    cout << hashmap.getMonthHighest("2024-01-01") << endl;
    cout << hashmap.getMonthLowest("2024-01-01") << endl;
    cout << hashmap.getMonthAverage("2024-01-01") << endl;
    // return 0;

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
