#pragma once
#include "ModulePhysics.h"
#include "Module.h"
#include "PhysEntity.h"
#include "Timer.h"
#include "Globals.h"
#include "Mud.h"
#include "FinishLine.h"

#include <iostream>
#include <vector>

using namespace std;

class Map : public PhysicEntity
{
public:

	Map(ModulePhysics* physics, int _x, int _y, int width, int height, Module* _listener, Group type)
		: PhysicEntity(physics->CreateRectangleSensor(_x, _y, 0, 0, LAND, this), _listener, ColliderTypes::MAP)
	{
		mPhysics = physics;
		decorationMap = readCSV(mapDecorationCSV);
		mapDecorationFromCSV(decorationMap, 16, 16);
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
			Vector2{ 0, 0 }, body->GetRotation() * RAD2DEG, WHITE);
	}


private:

	Texture2D texture = LoadTexture("Assets/Level/AltMap.png");

	ModulePhysics* mPhysics;

	string mapDecorationCSV = "Assets/Level/AltMap_Tile Layer 2.csv";

	vector<vector<int>> decorationMap;
	vector<vector<int>> mudMap;


	vector<vector<int>> readCSV(const string& filename);
	void mapDecorationFromCSV(const vector<vector<int>>& map, float tileWidth, float tileHeight);

	Mud* mud;
	vector<Mud*> mudTiles;

	FinishLine* finishLine;
	vector<FinishLine*> fLineTiles;


};