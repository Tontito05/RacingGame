#pragma once

#include "Globals.h"
#include "Module.h"
#include "ModulePhysics.h"
#include "p2Point.h"

#include "raylib.h"
#include <vector>
#include <iostream>

class PhysBody;
class PhysicEntity;

class PhysicEntity
{
protected:

	PhysicEntity(PhysBody* _body, Module* _listener)
		: body(_body)
		, listener(_listener)
	{
		body->listener = listener;
	}

public:
	virtual ~PhysicEntity() = default;
	virtual void Update() = 0;

	virtual int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal)
	{
		return 0;
	}

public:
	PhysBody* body;
	Module* listener;
};

class Box : public PhysicEntity
{
public:
	Box(ModulePhysics* physics, int _x, int _y, int width, int height, Module* _listener, Texture2D _texture, Group type)
		: PhysicEntity(physics->CreateRectangle(_x, _y, width, height,type), _listener)
		, texture(_texture)
	{

	}

	void Update() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);
		DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
			Rectangle{ (float)x, (float)y, (float)texture.width, (float)texture.height },
			Vector2{ (float)texture.width / 2.0f, (float)texture.height / 2.0f }, body->GetRotation() * RAD2DEG, WHITE);
	}

	int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal) override
	{
		return body->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);;
	}

private:
	Texture2D texture;
};

class Bike : public Box {
public:
	Bike(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture) : Box(physics, _x, _y, 18, 35, _listener, _texture, Group::LAND) {
	}
};

class Car : public Box {
public:
	Car(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture) : Box(physics, _x, _y, 26, 43, _listener, _texture, Group::LAND) {

	}
};

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
	std::vector<PhysicEntity*> entities;

	//Player
	PhysicEntity* Player;
	
	//Textures TODO
	Texture2D car;
	Texture2D bike;

	//Player velocity (Changes with gears)
	b2Vec2 Vel = { 1,1};

	//Player brake (Changes with gears)
	b2Vec2 Brake = { 0.5,0.5 };

	//Player rotation and rotation friction (they dont change)
	float RotForce = 1.5;
	float RotFriction = 0.05;

	//Gears --> They set a maximum velocity to the car and also can be changed with G
	std::vector<b2Vec2> Gears;
	int GearChange = 0;

	vec2<int> ray;
	bool ray_on;
};
