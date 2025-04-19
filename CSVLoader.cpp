#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "hashmap.h"
#include "heap.h"

void CSVLoader::load_csv(HashMap& map, MaxHeap& heap, const std::string& city, const std::string& attribute) {
    int att_key;
    std::vector<std::string> cities = {"Chicago","New York","Phoenix","Philadelphia",
        "Houston","San Antonio","San Diego","Dallas","San Jose","Los Angeles"};

    if (std::find(cities.begin(), cities.end(), city) == cities.end()) {
        std::cerr << "Error: unsupported city '" << city << "'\n";
        return;
    }

    if (attribute == "Temperature")      att_key = 2;
    else if (attribute == "Humidity")    att_key = 3;
    else if (attribute == "Precipitation") att_key = 4;
    else if (attribute == "Wind")         att_key = 5;
    else {
        std::cerr << "Error: unsupported attribute '" << attribute << "'\n";
        return;
    }

    std::ifstream file("/Users/benx/CLionProjects/DSAProject3/weather_data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: could not open weather_data.csv\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        if (row.size() > static_cast<size_t>(att_key) && row[0] == city) {
            const std::string& datetime = row[1];
            double value = std::stod(row[att_key]);
            map.insert(datetime, value);
            heap.insert(datetime,value);
        }
    }

    file.close();
}

void CSVLoader::load_csv(MaxHeap& heap, const std::string& city, const std::string& attribute) {
    int att_key;

    std::vector<std::string> cities = {"Chicago","New York","Phoenix","Philadelphia",
        "Houston","San Antonio","San Diego","Dallas","San Jose","Los Angeles"};

    if (std::find(cities.begin(), cities.end(), city) == cities.end()) {
        std::cerr << "Error: unsupported city '" << city << "'\n";
        return;
    }

    if (attribute == "Temperature")      att_key = 2;
    else if (attribute == "Humidity")    att_key = 3;
    else if (attribute == "Precipitation") att_key = 4;
    else if (attribute == "Wind")         att_key = 5;
    else {
        std::cerr << "Error: unsupported attribute '" << attribute << "'\n";
        return;
    }

    std::ifstream file("weather_data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: could not open weather_data.csv\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        if (row.size() > static_cast<size_t>(att_key) && row[0] == city) {
            const std::string& datetime = row[1];
            double value = std::stod(row[att_key]);
            heap.insert(datetime, value);
        }
    }

    file.close();
}
