#pragma once

#include "ModulePhysics.h"
#include "Module.h"
#include "PhysEntity.h"
#include "Timer.h"
#include <iostream>
#include <vector>
using namespace std;

class FinishLine : public PhysicEntity
{
public:

	FinishLine(ModulePhysics* physics, int _x, int _y, int width, int height, Module* _listener, Group type)
		: PhysicEntity(physics->CreateRectangleSensor(_x, _y, width, height, type, this), _listener, ColliderTypes::FINISHLINE)
	{

	}
	void Update() override
	{

	}

	void Render() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);
		DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
			Rectangle{ (float)x, (float)y, (float)texture.width * scale, (float)texture.height * scale },
			Vector2{ (float)texture.width * scale / 2.0f, (float)texture.height * scale / 2.0f }, body->GetRotation() * RAD2DEG, WHITE);
	}
private:
	int scale;
	Texture2D texture;
};