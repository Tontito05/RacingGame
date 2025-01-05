#pragma once

#include "Globals.h"
#include "Module.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "Car.h"
#include "Mud.h"
#include "Map.h"
#include "raylib.h"
#include <vector>
#include <iostream>

class PhysBody;
class PhysicEntity;


class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	//AI
	std::vector<Car*> entities;

	//
	Player* player;
	Mud* mud;
	Map* map;


	//Textures TODO
	Texture2D car;

	vec2<int> ray;
	bool ray_on;
};
