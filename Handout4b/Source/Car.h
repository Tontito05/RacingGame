#pragma once
#include "ModulePhysics.h"
#include "Module.h"
#include "PhysEntity.h"
#include <iostream>
#include <vector>
class Car : public PhysicEntity
{
public:
	Car(ModulePhysics* physics, int _x, int _y, int width, int height, Module* _listener, Texture2D _texture, Group type)
		: PhysicEntity(physics->CreateRectangle(_x, _y, width, height, type), _listener)
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

	//CarFunctions
	b2Vec2 GetFriction(b2Vec2 vec) const;
	void ApplyFriction(float angle);
	b2Vec2 ComputeVector(float angle, b2Vec2 Force) const;
	void MoveForward(float angle) ;
	void MoveBackwards(float angle) ;
	void Brake(float angle) ;
	void Rotate(int direction) const;

	void SumToVec(b2Vec2 f);
	void SubToVec(b2Vec2 f);

	b2Vec2 GetVel() const { return Vel; }
	void SetVel(b2Vec2 _Vel) { Vel = _Vel; }
	void SetFriction(float FrQuo) { FrQueficient = FrQuo; }
	void SetRotFriction(float RotFr) { RotFriction = RotFr; }

	b2Vec2 mainVec;

	//Player velocity (Changes with gears)
	b2Vec2 Vel;

	//Player brake (Changes with gears)
	b2Vec2 brake = { 0.5,0.5};

private:
	Texture2D texture;

	float FrQueficient = 0.2;

	//Player rotation and rotation friction (they dont change)
	float RotForce = 1;
	float RotFriction = 0.1;
};

class Player : public Car
{
public:
	Player(ModulePhysics* physics, int _x, int _y, int width, int height, Module* _listener, Texture2D _texture, Group type)
		: Car(physics, _x, _y, width, height, _listener, _texture, type)
	{
		Gears.push_back({ 3,3 });
		Gears.push_back({ 6,6 });
		Gears.push_back({ 8,8 });
		Gears.push_back({ 10,10 });

		Vel = { 2,2 };
	}


	bool CheckGear();
	bool GearBack();
	b2Vec2 GetMaxVel();

	//Gears --> They set a maximum velocity to the car and also can be changed with G
	std::vector<b2Vec2> Gears;
	int GearChange = 0;

};