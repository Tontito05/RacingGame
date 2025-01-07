#pragma once
#include "Module.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "Timer.h"

enum class ColliderTypes
{
	NULLCOL, 
	MUD,
	CAR,
	MAP
};

class PhysicEntity
{
protected:

	PhysicEntity(PhysBody* _body, Module* _listener, ColliderTypes _colType = ColliderTypes::NULLCOL)
		: body(_body)
		, listener(_listener)
		, colType(_colType)
	{
		body->listener = listener;
	}

public:
	virtual ~PhysicEntity() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal)
	{
		return 0;
	}

public:
	PhysBody* body;
	Module* listener;
	ColliderTypes colType;
};