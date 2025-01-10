#pragma once

#include "Globals.h"
#include "Module.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "Car.h"
#include "Mud.h"
#include "Map.h"
#include "IA.h"
#include "raylib.h"
#include <vector>
#include <iostream>
#include "UIManager.h"

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
	void EndCollision(PhysBody* bodyA, PhysBody* bodyB);

	bool isDriftFxPlaying;
	bool isJumpFxPlaying;
	bool isRunFxPlaying;

public:

	//AI
	std::vector<Car*> entities;

	//
	Player* player;
	Mud* mud;
	Map* map;
	IA* ia;
	UIManager* UI;

	//Textures TODO
	Texture2D car;
	Texture2D carOpponent;

	vec2<int> ray;
	bool ray_on;

	//Sfx
	uint32 driftFx;
	uint32 jumpFx;
	uint32 gearFx;
	uint32 runFx;

};
