#pragma once
#include "Car.h"

class IA : public Car
{
public:
	//IA constructor
	IA(ModulePhysics* physics, int x, int y, int width, int height, Module* listener, Texture2D texture, Group type)
		: Car(physics, x, y, width, height, listener, texture, type)
	{
		//Set the gears
		Gears.push_back({ 1,1 });
		Gears.push_back({ 2,2 });
		Gears.push_back({ 4,4 });
		Gears.push_back({ 6,6 });

		//Set the waypoints
		waypoints.push_back({ 576,296 });
		waypoints.push_back({ 600,296 });
		waypoints.push_back({ 700,296 });
		/*waypoints.push_back({ 0,0 });
		waypoints.push_back({ 0,0 });
		waypoints.push_back({ 0,0 });
		waypoints.push_back({ 0,0 });
		waypoints.push_back({ 0,0 });
		waypoints.push_back({ 0,0 });
		waypoints.push_back({ 0,0 });*/
	}

	//Player functions////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Check if it can change gears
	bool CheckGear();
	//Check if the gear should go back
	void GearBack();
	//Get the maximum velocity of the car
	b2Vec2 GetMaxVel();

	// Method to get the car's position
	Vector2 GetPosition();

	// Pattern to follow the finish line and the road
	void Pattern();

	//Gears --> They set a maximum velocity to the car and also can be changed with G
	std::vector<b2Vec2> Gears;
	int GearChange = 0;

	int waypointsIndex = 1;
	std::vector<b2Vec2> waypoints;
	/*float speed;*/

private:

};
