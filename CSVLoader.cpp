#include "CSVLoader.h"
#include "hashmap.h"
#include <fstream>
#include <sstream>
#include <iostream>

void CSVLoader::load_csv(std::string city,std::string attribute) { // temp,humidity,precip,wind
    int att_key;
    HashMap hashmap;
    if(attribute == "temp") {
        att_key = 2;
    } else if(attribute == "humidity") {
        att_key = 3;
    } else if(attribute == "precip") {
        att_key = 4;
    } else if(attribute == "wind") {
        att_key = 5;
    } else {
        std::cout << "specify a valid attribute retard" << std::endl;
        return;
    }
    std::vector<std::vector<std::string>> data;
    std::ifstream file("weather_data.csv"); // Change the working directory in CLion (under "edit configuration") to the project folder
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        if(row[0] == city) {
            std::string datetime = row[1];
            double att = std::stod(row[att_key]);
            std::vector<double> values;
            values.push_back(att);
            hashmap.insert(datetime, values);
            // std::cout << datetime << " " << att << std::endl;
        }
    }
    file.close();
    std::cout << hashmap.getDayData("2024-01-01") << std::endl;
}
