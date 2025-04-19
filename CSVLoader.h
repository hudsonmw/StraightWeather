#ifndef CSVLOADER_H
#define CSVLOADER_H
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "hashmap.h"


class CSVLoader {
public:
    void load_csv(HashMap& hashmap, std::string city, std::string attribute);
};



#endif //CSVLOADER_H
