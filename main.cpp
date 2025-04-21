#include <vector>
#include <iostream>
#include <algorithm>
#include "CSVLoader.h"
#include <chrono>
#include "heap.h"
#include "hashmap.h"

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
    std::vector<std::string> attributes = {"Temperature","Humidity","Precipitation","Wind"}; //minor typo on precipitation you absolute bafoon
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
    HashMap hashmap;
    MaxHeap heap;
    loader.load_csv(hashmap,heap, city, att);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Data loaded in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
    bool cont = true;
    std::string option;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "1. Highest " << att << " recorded" << std::endl;
    std::cout << "2. Lowest " << att << " recorded" << std::endl;
    std::cout << "3. Specific datetime (YYYY-MM-DD HH:MM:SS)" << std::endl;
    std::cout << "4. Average " << att << " on specific day (YYYY-MM-DD)" << std::endl;
    std::cout << "5. Lowest " << att << " on specific day (YYYY-MM-DD)" << std::endl;
    std::cout << "6. Highest " << att << " on specific day (YYYY-MM-DD)" << std::endl;
    std::cout << "7. Average " << att << " for specific month (MM)" << std::endl;
    std::cout << "8. Exit" << std::endl;
    while(cont) {
        std::cout << "What type of data would you like to see?" << std::endl;
        std::cin >> option;
        if (option == "1") {
            begin = std::chrono::steady_clock::now();
            std::string highest_hash = hashmap.getHighest();
            end = std::chrono::steady_clock::now();
            std::cout << "Hashmap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Hashmap, " << highest_hash << std::endl;
            std::cout << std::endl;
            begin = std::chrono::steady_clock::now();
            optional<pair<string,double>> highest_heap = heap.getHighest();
            end = std::chrono::steady_clock::now();
            std::cout << "Heap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Heap, Highest: " << highest_heap->second << " on " << highest_heap->first<< std::endl;
            std::cout << std::endl;
        } else if(option == "2") {
            begin = std::chrono::steady_clock::now();
            std::string lowest_hash = hashmap.getLowest();
            end = std::chrono::steady_clock::now();
            std::cout << "Hashmap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Hashmap, " << lowest_hash << std::endl;
            std::cout << std::endl;
            begin = std::chrono::steady_clock::now();
            optional<pair<string,double>> lowest_heap = heap.getLowest();
            end = std::chrono::steady_clock::now();
            std::cout << "Heap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Heap, Lowest: " << lowest_heap->second << " on " << lowest_heap->first<< std::endl;
            std::cout << std::endl;
        } else if(option == "3") {
            std::string datetime;
            std::cout << "What datetime would you like to see data for? (YYYY-MM-DD HH:MM:SS format)" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // found on stack overflow as fix
            std::getline(std::cin,datetime); // no date valid check for now
            begin = std::chrono::steady_clock::now();
            optional<double> hashdate = hashmap.get(datetime);
            end = std::chrono::steady_clock::now();
            if(!hashdate.has_value()) {
                std::cout << "Datetime not found in data!" << std::endl;
            } else {
                std::cout << "Hashmap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
                std::cout << "Hashmap, " << datetime << ", " << att << ": " << hashdate.value() << std::endl;
                begin = std::chrono::steady_clock::now();
                optional<pair<string, double>> heapdate = heap.findDate(datetime);
                end = std::chrono::steady_clock::now();
                std::cout << "Heap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
                std::cout << "Heap, " << heapdate->first << ", " << att << ": " << heapdate->second << std::endl;
                std::cout << std::endl;
            }
        } else if(option == "4") {
            std::string datetime;
            std::cout << "What datetime would you like to see the average " << att << " for? (YYYY-MM-DD format)" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,datetime);
            begin = std::chrono::steady_clock::now();
            std::string hashdate = hashmap.getDayAverage(datetime);
            end = std::chrono::steady_clock::now();
            std::cout << "Hashmap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Hashmap, " << hashdate << std::endl;
            begin = std::chrono::steady_clock::now();
            optional<double> heapdate = heap.getAverageOnDay(datetime);
            end = std::chrono::steady_clock::now();
            std::cout << "Heap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Heap, Average on " << datetime << " : " << heapdate.value() << std::endl;
            std::cout << std::endl;
        } else if(option == "5") {
            std::string datetime;
            std::cout << "What datetime would you like to see the lowest " << att << " for? (YYYY-MM-DD format)" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,datetime);
            begin = std::chrono::steady_clock::now();
            std::string hashdate = hashmap.getDayLowest(datetime);
            end = std::chrono::steady_clock::now();
            std::cout << "Hashmap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Hashmap, " << hashdate << std::endl;
            begin = std::chrono::steady_clock::now();
            optional<pair<string,double>> heapdate = heap.getLowestOnDay(datetime);
            end = std::chrono::steady_clock::now();
            std::cout << "Heap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Heap, Lowest on " << datetime << " : " << heapdate->second << std::endl;
            std::cout << std::endl;
        } else if (option == "6") {
            std::string datetime;
            std::cout << "What datetime would you like to see the highest " << att << " for? (YYYY-MM-DD format)" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,datetime);
            begin = std::chrono::steady_clock::now();
            std::string hashdate = hashmap.getDayHighest(datetime);
            end = std::chrono::steady_clock::now();
            std::cout << "Hashmap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Hashmap, " << hashdate << std::endl;
            begin = std::chrono::steady_clock::now();
            optional<pair<string,double>> heapdate = heap.getHighestOnDay(datetime);
            end = std::chrono::steady_clock::now();
            std::cout << "Heap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
            std::cout << "Heap, Highest on " << datetime << " : " << heapdate->second << std::endl;
            std::cout << std::endl;
        } else if (option == "7") { // input validated
            std::string datetime;
            std::cout << "What month would you like to see the average " << att << " for? (YYYY-MM format)" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin,datetime);
            std::string month;
            if(datetime == "2024-01") {
                month = "January";
            } else if(datetime == "2024-02") {
                month = "February";
            } else if(datetime == "2024-03") {
                month = "March";
            } else if(datetime == "2024-04") {
                month = "April";
            } else if (datetime == "2024-05") {
                month = "May";
            } else {
                month = "invalid";
            }
            if(month == "invalid") {
                std::cout << "Invalid month" << std::endl;
            }
            else {
                begin = std::chrono::steady_clock::now();
                std::string hashdate = hashmap.getMonthAverage(datetime);
                end = std::chrono::steady_clock::now();
                std::cout << "Hashmap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
                std::cout << "Hashmap, " << hashdate << std::endl;
                begin = std::chrono::steady_clock::now();
                optional<double> heapdate = heap.getAverageForMonth(datetime);
                end = std::chrono::steady_clock::now();
                std::cout << "Heap data accessed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." << std::endl;
                std::cout << "Heap, Average for month of " << month << " : " << heapdate.value() << std::endl;
                std::cout << std::endl;
            }
        } else if(option == "8") {
            cont = false;
        } else {
            std::cout << "Invalid input choice" << std::endl;
        }
    }
    std::cout << "Thank you for using StraightWeather!" << std::endl;
    return 0;
}
