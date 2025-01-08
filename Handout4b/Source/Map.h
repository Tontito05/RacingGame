#pragma once
#include "ModulePhysics.h"
#include "Module.h"
#include "PhysEntity.h"
#include "Timer.h"
#include <iostream>
#include <vector>

using namespace std;

class Map : public PhysicEntity
{
public:

	Map(ModulePhysics* physics, int _x, int _y, int width, int height, Module* _listener, Group type)
		: PhysicEntity(physics->CreateChain(_x, _y, points, 224, this), _listener, ColliderTypes::MAP)
	{
		readCSV(mapCSV);
	}
	void Update() override
	{

	}

	void Render() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);
		DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
			Rectangle{ (float)x, (float)y, (float)texture.width * SCALE, (float)texture.height * SCALE },
			Vector2{ (float)texture.width * SCALE / 2.0f, (float)texture.height * SCALE / 2.0f }, body->GetRotation() * RAD2DEG, WHITE);
	}
private:

	Texture2D texture = LoadTexture("Assets/Level/Map.png");
	static constexpr int points[224] = {
		1176, 47,
		1177, 245,
		1225, 337,
		1224, 544,
		1174, 636,
		1176, 763,
		1175, 816,
		1157, 842,
		1129, 858,
		443, 856,
		443, 896,
		487, 988,
		488, 1391,
		440, 1486,
		442, 1523,
		1382, 1523,
		1380, 1480,
		680, 1481,
		637, 1470,
		615, 1435,
		615, 1313,
		632, 1286,
		660, 1270,
		1555, 1270,
		1602, 1273,
		1640, 1304,
		1640, 2174,
		1642, 2247,
		1700, 2248,
		1734, 2279,
		1736, 2352,
		1708, 2389,
		1657, 2392,
		1437, 2394,
		1398, 2377,
		1381, 2347,
		1381, 1896,
		633, 1896,
		633, 1934,
		621, 1972,
		584, 1992,
		541, 1992,
		475, 1993,
		475, 2033,
		521, 2128,
		521, 2283,
		472, 2382,
		473, 2677,
		515, 2677,
		517, 2565,
		535, 2535,
		566, 2518,
		740, 2518,
		775, 2532,
		792, 2564,
		792, 2612,
		793, 3148,
		741, 3148,
		740, 2568,
		570, 2568,
		567, 2647,
		561, 2705,
		532, 2725,
		493, 2728,
		452, 2722,
		425, 2691,
		423, 2614,
		421, 2026,
		422, 1984,
		448, 1950,
		492, 1941,
		581, 1941,
		581, 1899,
		592, 1868,
		620, 1847,
		677, 1844,
		1309, 1844,
		1368, 1844,
		1407, 1856,
		1429, 1883,
		1434, 1936,
		1480, 2030,
		1480, 2207,
		1432, 2301,
		1432, 2338,
		1683, 2338,
		1683, 2296,
		1644, 2296,
		1605, 2281,
		1588, 2242,
		1588, 2173,
		1590, 1322,
		665, 1320,
		665, 1429,
		1380, 1430,
		1414, 1444,
		1434, 1475,
		1434, 1524,
		1423, 1556,
		1392, 1576,
		1348, 1576,
		1284, 1576,
		492, 1576,
		439, 1576,
		404, 1560,
		389, 1524,
		389, 897,
		392, 845,
		409, 818,
		440, 804,
		1124, 804,
		1127, 47
	};

	string mapCSV = "Assets/Level/Map_Decoration.csv";
	vector<vector<int>> readCSV(const string& filename);

};