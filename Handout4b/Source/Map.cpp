#include <fstream>
#include <sstream>
#include <string>

#include "ModulePhysics.h"
#include "Application.h"
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

void Map::mapDecorationFromCSV(const vector<vector<int>>& map, float tileWidth, float tileHeight)
{
    tileHeight = tileHeight * SCALE;
    tileWidth = tileWidth * SCALE;

    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            int tileID = map[y][x];

			if (tileID == 179 || tileID == 180 || tileID == 194 || tileID == 193 || tileID == 192 || tileID == 191 || tileID == 190 || tileID == 213 || tileID == 214 || tileID == 169 || tileID == 270)
			{
				mPhysics->CreateRectangle(x * tileWidth + tileWidth / 2, y * tileHeight + tileHeight / 2, tileWidth, tileHeight, Group::LAND, this, b2_staticBody);
			}
            else if (tileID == 197)
            {
                //MUD
                mud = new Mud(mPhysics, x * tileWidth + tileWidth / 2, y * tileHeight + tileHeight / 2, tileWidth, tileHeight, listener, LAND);
                mudTiles.push_back(mud);
            }
            else 
            {
				if (tileID != 177 && tileID != 178 && tileID != 195 && tileID != 196)
				{
                    mPhysics->CreateRectangleSensor(x * tileWidth + tileWidth / 2, y * tileHeight + tileHeight / 2, tileWidth, tileHeight, Group::LAND, this);

				}
            }
        }
    }
}




