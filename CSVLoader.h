#ifndef CSVLOADER_H
#define CSVLOADER_H
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "hashmap.h"
#include "heap.h"


class CSVLoader {
    public:
        void load_csv(HashMap& map,
                      const std::string& city,
                      const std::string& attribute);
    
        void load_csv(MaxHeap& heap,
                      const std::string& city,
                      const std::string& attribute);
    };



#endif //CSVLOADER_H
