
#include <iostream>
#include "CSVLoader.h"
#include "hashmap.h"

int main() {
    // CSVLoader loader;
    // loader.load_csv("Chicago","wind");

    HashMap hashmap;
    cout << hashmap.convertToHashTime("2024-03-21 07:25:19") << endl;
    return 0;
}
