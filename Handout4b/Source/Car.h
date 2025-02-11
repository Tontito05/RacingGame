#pragma once
#include "ModulePhysics.h"
#include "Module.h"
#include "PhysEntity.h"
#include "Timer.h"
#include "Map.h"
#include <iostream>
#include <vector>

using namespace std;

enum class STATES
{
	DRIVING,
	DRIFTING,
	END_DRIFTING,
	JUMPING,
	FALLING
};
enum class TypeCar
{
	PLAYER,
	IA_1,
	IA_2,
	IA_3
};

class Car : public PhysicEntity
{
public:

	Car(ModulePhysics* physics, int _x, int _y,  Module* _listener, Group type, ColliderTypes Ctype,TypeCar car)
		: PhysicEntity(physics->CreateRectangle(_x, _y, 16* SCALE, 9* SCALE, type, this), _listener, Ctype)
	{
		recoveryTime.Start();
		switch (car)
		{
		case TypeCar::PLAYER:
			texture = LoadTexture("Assets/MiniPixelPack2/Cars/Player.png");
			break;
		case TypeCar::IA_1:
			texture = LoadTexture("Assets/MiniPixelPack2/Cars/Plat.png");
			break;
		case TypeCar::IA_2:
			texture = LoadTexture("Assets/MiniPixelPack2/Cars/Silver.png");
			break;
		case TypeCar::IA_3:
			texture = LoadTexture("Assets/MiniPixelPack2/Cars/Bronze.png");
			break;
		default:
			break;
		}

	}

	void Update() override 
	{
		ApplyMovement();
		if (jump == true)
		{
			Jump();
		}
	}

	void Render() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);

		//Get The top left corner of the car to draw from there ;)
		x -= ((texture.width * SCALE) / 2) * cos(body->GetRotation());
		y -= ((texture.height * SCALE) / 2) * sin(body->GetRotation());

		DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
			Rectangle{ (float)x, (float)y, (float)texture.width * scale * SCALE, (float)texture.height * scale * SCALE },
			Vector2{ (float)texture.width * scale / 2.0f, (float)texture.height * scale / 2.0f }, body->GetRotation() * RAD2DEG, WHITE);
	}

	int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal) override
	{
		return body->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);;
	}

	//CAR FUNCTIONS////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float normalizeAngle(float angle);

	//FRICTION
	b2Vec2 GetFriction(b2Vec2 vec) const;
	void ApplyFriction();

	//MOVEMENT
	void MoveForward() ;
	void MoveBackwards() ;
	void Rotate(int direction) const;
	void Jump();
	bool TryJump();

	//VELOCITY SETTERS
	void SetXvelocity(float x) { body->body->SetLinearVelocity({ x,body->GetVelocity().y });}
	void SetYvelocity(float y) { body->body->SetLinearVelocity({ body->GetVelocity().x,y }); }

	//GETTERS
	b2Vec2 GetAcceleration();
	float GetAngleOfVector(const b2Vec2& vec);

	//DRIFT ROTATION AND MOVEMENT
	float lerpAngle(float from, float to, float t);

	//SETTERS
	void SetAcceleration(b2Vec2 Acc) { Acceleration = Acc; }
	void SetFriction(float FrQuo) { FrQueficient = FrQuo; }
	void SetRotFriction(float RotFr) { RotFriction = RotFr; }

	//APPLY THE VECTOR
	void ApplyMovement();

	//CHECK EPS
	void CheckEps();

	//ROAD LIMITS
	void RoadLimits();

	//VARIABLES///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//The vector that the Car will follow
	b2Vec2 mainVec;
	//The direction of the vector
	float direction = 0;

	//Car Acceleration
	b2Vec2 Acceleration;

	//Car Brake
	b2Vec2 brake = { 10,10};

	//Vector Lerps rotation
	float DriftLerp = 0.01;
	float EndDriftLerp = 0.05;
	float NormalLerp = 1;
	float JumpLerp = 0;

	//
	float RotForce;

	//Car state
	STATES state = STATES::DRIVING;

	//Delta time
	float dt  = GetFrameTime();

	//Jump////////////////////////////////

	//Flag
	bool jump = false;

	//Scaling
	float jumpaScale = 0.01;
	float scale = 1;

	//Jump timer and Recovery time
	Timer jumpTimer;
	Timer recoveryTime;

	//max air time
	float airTime = 0.5;

	//Check
	bool CanJump() 
	{
		if (recoveryTime.ReadSec() > airTime) 
		{ 
			return true; 
		} 
		
		return false;
	}

private:

	//Texture
	Texture2D texture;

	//Frictions
	float FrQueficient = 0.2;
	float RotFriction = 0.1;

};

class Player : public Car
{
public:

	//Player constructor
	Player(ModulePhysics* physics, int _x, int _y, Module* _listener, Group type)
		: Car(physics, _x, _y, _listener, type, ColliderTypes::PLAYER, TypeCar::PLAYER)
	{
		//Set the gears
		Gears.push_back({ 1,1 });
		Gears.push_back({ 2,2 });
		Gears.push_back({ 4,4 });
		Gears.push_back({ 6,6 });
	}

	//Player functions////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Update() override 
	{
		ApplyMovement();
		if (jump == true)
		{
			Jump();
		}
	}

	//Check if it can change gears
	bool CheckGear();
	//Check if the gear should go back
	void GearBack();
	//Get the maximum velocity of the car
	b2Vec2 GetMaxVel();

	// Method to get the car's position
	Vector2 GetPosition();


	//Gears --> They set a maximum velocity to the car and also can be changed with G
	std::vector<b2Vec2> Gears;
	int GearChange = 0;
	bool CanChangeGear = false;


	vector<b2Vec2> trackPoints;

};