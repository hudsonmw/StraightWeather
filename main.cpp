
#include <iostream>
#include "CSVLoader.h"

int main() {
    std::cout << "Welcome to GayWeather!" << std::endl;
    std::cout << "What city would you like to see data for?" << std::endl;
    std::cout << "1. Chicago" << std::endl;
    std::cout << "2. Dallas" << std::endl;
    std::cout << "3. Houston" << std::endl;
    std::cout << "4. Los Angeles" << std::endl;
    std::cout << "5. New York" << std::endl;
    std::cout << "6. Philadelphia" << std::endl;
    std::cout << "7. Phoenix" << std::endl;
    std::cout << "8. San Antonio" << std::endl;
    std::cout << "9. San Diego" << std::endl;
    std::cout << "10. San Jose" << std::endl;
    std::cout << "What city would you like to see data for?" << std::endl;
    std::string city;
    std::cin >> city;
    CSVLoader loader;
    loader.load_csv("Chicago","wind");
    return 0;
}
