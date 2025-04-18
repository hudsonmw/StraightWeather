#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

void CSVLoader::load_csv(std::string city,std::string attribute) { // Pass by reference the hashmap and heap
    int att_key;
    for(int i=0; i < 1000000000; i++) {
        1 == 1;
    }
    std::vector<std::string> cities = {"Chicago","New York","Phoenix","Philadelphia", // all avalible cities
    "Houston","San Antonio","San Diego","Dallas","San Jose","Los Angeles"};
    if(std::find(cities.begin(),cities.end(),city) == cities.end()) {
        std::cout << "bad city" << std::endl;
        return;
    }
    if(attribute == "Temperature") {
        att_key = 2; // stores index of column which stores desired attribute
    } else if(attribute == "Humidity") {
        att_key = 3;
    } else if(attribute == "Precipitation") {
        att_key = 4;
    } else if (attribute == "Wind"){
        att_key = 5;
    } else { // main function should ensure that there are only valid values passed in
        std::cout << "bad attribute" << std::endl;
        return;
    }
    std::vector<std::vector<std::string>> data;
    std::ifstream file("~weather_data.csv");
    std::string line;
    while (std::getline(file, line)) { // parses through .csv one line at a time
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        if(row[0] == city) {
            std::string datetime = row[1];
            double att = std::stod(row[att_key]);
            std::cout << datetime << " " << att << std::endl;
        }
    }
    file.close();
}
