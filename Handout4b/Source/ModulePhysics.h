#pragma once

#include "Module.h"
#include "Globals.h"

#include "box2d\box2d.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y 0.0f

#define GRAV 10.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 1/PIXELS_PER_METER // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class PhysicEntity;

enum Group
{
	DEFAULD = 1<<0,
	LAND = 1 << 1,
	AIR = 1 << 2,
	SEA = 1 << 3
};

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL), entity(NULL)
	{}

	//void GetPosition(int& x, int& y) const;
	void GetPhysicPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;
	void AddTorque(float t);
	void AngularVelocity(float w);
	b2Vec2 GetVelocity();
	void ChangeGroup(Group type);
	uint16 GetGroup();

public:
	int width, height;
	b2Body* body;
	Module* listener;
	PhysicEntity* entity;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, PhysicEntity* entity_);
	PhysBody* CreateRectangle(int x, int y, int width, int height, Group type, PhysicEntity* entity_, b2BodyType btype = b2_dynamicBody);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, Group type, PhysicEntity* entity_);
	PhysBody* CreateChain(int x, int y, const int* points, int size, Group type, PhysicEntity* entity_);
	PhysBody* CreateChainSensor(int x, int y, const int* points, int size, Group type, PhysicEntity* entity_);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
};
