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

			if (tileID == 179 || tileID == 180 || tileID == 194 || tileID == 193 || tileID == 192 || tileID == 191 || tileID == 190)
			{
				mPhysics->CreateRectangle(x * tileWidth + tileWidth / 2, y * tileHeight + tileHeight / 2, tileWidth, tileHeight, Group::LAND, this, b2_staticBody);
			}
            if (tileID == 197)
            {
                //MUD
                mud = new Mud(mPhysics, x * tileWidth + tileWidth / 2, y * tileHeight + tileHeight / 2, tileWidth, tileHeight, listener, LAND);
                mudTiles.push_back(mud);
            }
        }
    }
}

vector<b2Vec2> Map::B2Vec2ListFromArray(const float* points, int numPoints)
{
       vector<b2Vec2> vec2List;

        for (size_t i = 0; i < numPoints; ++i) {
            float x = points[i * 2];      
            float y = points[i * 2 + 1];  

            vec2List.push_back(b2Vec2(x, y));
        }

        return vec2List;
}

bool Map::PointInsidePoly(const b2Vec2& point, vector<b2Vec2> trackBoundaryPoints)
{

        int crossings = 0;
        int numPoints = trackBoundaryPoints.size();

        for (size_t i = 0; i < numPoints; ++i) {
            b2Vec2 p1 = trackBoundaryPoints[i];          
            b2Vec2 p2 = trackBoundaryPoints[(i + 1) % numPoints];

            // Check if the ray from the point crosses the edge between p1 and p2
            if ((point.y > p1.y) != (point.y > p2.y) &&
                point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)
            {
                crossings++; 
            }
        }

        // If crossings are odd point is inside the polygon
        return (crossings % 2) == 1;
    
}


