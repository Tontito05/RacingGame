#include <fstream>
#include <sstream>
#include <string>

#include "Map.h"

vector<vector<int>> Map::readCSV(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> map;

    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return map; 
    }
    cout << "CSV file Opened Successfully :)" << endl;
    string line;
    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) { 
            row.push_back(stoi(cell));
        }
        map.push_back(row); 
    }

    return map;
}