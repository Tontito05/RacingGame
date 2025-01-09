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
		waypoints.push_back({ 132,330 });
		waypoints.push_back({ 213,333 }); 
		waypoints.push_back({ 288,335 }); 
		waypoints.push_back({ 360,325 }); 
		waypoints.push_back({ 396,296 }); 
		waypoints.push_back({ 334,271 }); 
		waypoints.push_back({ 260,233 }); 
		waypoints.push_back({ 227,183 });
		waypoints.push_back({ 249,141 });
		waypoints.push_back({ 330,107 }); 
		waypoints.push_back({ 441,97 }); 
		waypoints.push_back({ 536,134 }); 
		waypoints.push_back({ 541,172 });
		waypoints.push_back({ 506,252 });
		waypoints.push_back({ 454,320 });
		waypoints.push_back({ 399,370 });
		waypoints.push_back({ 287,377 });
		waypoints.push_back({ 235,395 });
		waypoints.push_back({ 198,427 });
		waypoints.push_back({ 193,484 });
		waypoints.push_back({ 267,547 });
		waypoints.push_back({ 391,596 });
		waypoints.push_back({ 458,600 });
		waypoints.push_back({ 556,576 });
		waypoints.push_back({ 596,521 });
		waypoints.push_back({ 560,477 });
		waypoints.push_back({ 470,448 });
		waypoints.push_back({ 430,406 });
		waypoints.push_back({ 465,366 });
		waypoints.push_back({ 540,355 });
		waypoints.push_back({ 626,331 });
		waypoints.push_back({ 715,278 });
		waypoints.push_back({ 771,184 });
		waypoints.push_back({ 846,147 });
		waypoints.push_back({ 986,144 });
		waypoints.push_back({ 1023,173 });
		waypoints.push_back({ 1020,198 });
		waypoints.push_back({ 946,233 });
		waypoints.push_back({ 832,271 });
		waypoints.push_back({ 750,311 });
		waypoints.push_back({ 687,362 });
		waypoints.push_back({ 650,417 });
		waypoints.push_back({ 661,464 });
		waypoints.push_back({ 702,484 });
		waypoints.push_back({ 778,466 });
		waypoints.push_back({ 832,440 });
		waypoints.push_back({ 894,395 });
		waypoints.push_back({ 970,325 });
		waypoints.push_back({ 1024,295 });
		waypoints.push_back({ 1080,326 });
		waypoints.push_back({ 1122,371 });
		waypoints.push_back({ 1146,423 });
		waypoints.push_back({ 1115,487 });
		waypoints.push_back({ 1070,541 });
		waypoints.push_back({ 1051,610 });

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

	// Always forward
	void MoveAlwaysForward(float speed);

	//Gears --> They set a maximum velocity to the car and also can be changed with G
	std::vector<b2Vec2> Gears;
	int GearChange = 0;
	bool CanChangeGear = false;

	int waypointsIndex = 0;
	std::vector<b2Vec2> waypoints;

	/*float speed;*/

private:

};
