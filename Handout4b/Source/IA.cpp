#include "IA.h"

bool IA::CheckGear()
{
	b2Vec2 vel = body->GetVelocity();

	//Check the gear in each moment, and set diferent variables to the car, so that each gear ist equilibrated
	switch (GearChange)
	{
	case 0:
		Acceleration = { 4,4 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.05;
		EndDriftLerp = 0.2;

		break;
	case 1:

		Acceleration = { 6,6 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.04;
		EndDriftLerp = 0.1;

		jumpaScale = 0.015;
		airTime = 0.6;

		break;

	case 2:

		Acceleration = { 10 ,10 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.02;
		EndDriftLerp = 0.05;

		jumpaScale = 0.02;
		airTime = 0.7;

		break;

	case 3:
		Acceleration = { 12,12 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.02;
		EndDriftLerp = 0.03;
		jumpaScale = 0.025;
		airTime = 0.8;

		break;

	default:
		break;
	}

	//Naw chack if the player should or not change the gear
	if (GearChange < 3 && vel.Length() > GetMaxVel().Length() * 0.8)
	{
		return true;
	}
	if (vel.Length() < GetMaxVel().Length())
	{
		return false;
	}

}
void IA::GearBack()
{
	b2Vec2 vel = body->GetVelocity();
	//Set the gears back if nessessary
	if (GearChange != 0 && vel.Length() < Gears[GearChange - 1].Length() * 0.3)
	{
		GearChange--;
	}
}
b2Vec2 IA::GetMaxVel()
{
	//get the maximum velocity that the car can reach in each gear
	b2Vec2 MaxVel = Gears[GearChange];
	MaxVel += GetFriction(MaxVel);
	return MaxVel;
}

Vector2 IA::GetPosition() {
	int x, y;
	body->GetPhysicPosition(x, y);
	return Vector2{ (float)x, (float)y };
}

void IA::MoveAlwaysForward(float speed) {
	// Get the current angle of the body
	float angle = body->body->GetAngle();

	// Calculate the forward direction vector
	b2Vec2 forwardVec(cos(angle), sin(angle));

	// Set the body's velocity in the forward direction
	b2Vec2 velocity = speed * forwardVec;
	body->body->SetLinearVelocity(velocity);
}

void IA::Pattern()
{
	if (waypointsIndex < waypoints.size()-1) {
		
		// Waypoint direction
		b2Vec2 currentPosition = body->body->GetPosition();
		b2Vec2 diff;
		diff.x = (PIXEL_TO_METERS(waypoints[waypointsIndex].x)*SCALE - currentPosition.x);
		diff.y = (PIXEL_TO_METERS(waypoints[waypointsIndex].y)*SCALE - currentPosition.y);

		float distance = diff.Length();
		if (distance > 0) {
			b2Vec2 direction = diff;
			direction.Normalize();
			
			float desiredAngle = atan2(direction.y, direction.x);
			body->body->SetTransform(currentPosition, desiredAngle);

			float speed = 2.75f;

			MoveAlwaysForward(speed);
		}

		if (distance < 0.1f) {
			waypointsIndex++;
			
			cout << "Waypoint: " << waypointsIndex << " x: " << waypoints[waypointsIndex].x << " y: " << waypoints[waypointsIndex].y << endl;
			
			cout << "Waypoint: " << waypointsIndex << " x: " << PIXEL_TO_METERS(waypoints[waypointsIndex].x) << " y: " << PIXEL_TO_METERS(waypoints[waypointsIndex].y) << endl;
		}
	}
	else {
		std::cout << "Waypoints completed." << std::endl;
	}


}