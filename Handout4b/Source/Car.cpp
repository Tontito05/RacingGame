#include "Car.h"


//CAR////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
b2Vec2 Car::GetFriction(b2Vec2 vec) const
{
	b2Vec2 Force = { 0,0 };

	//Check the velocity on the different axis
	if (vec.x > 0.1 || vec.x < 0.1)
	{
		Force.x = -vec.x * FrQueficient * GRAV* dt;
	}
	if (vec.y > 0.1 || vec.y < -0.1)
	{
		Force.y = -vec.y * FrQueficient *GRAV * dt;
	}

	//Get the friction force
	return Force;
}
void Car::ApplyFriction()
{
	//Apply the friction to the Car
	mainVec.x += GetFriction(mainVec).x;
	mainVec.y += GetFriction(mainVec).y;
}

void Car::MoveForward() 
{
	//Accelerate the car
	mainVec.x += Acceleration.x*dt;
	mainVec.y += Acceleration.y*dt;
}
void Car::MoveBackwards() 
{
	//Slow down the car
	mainVec.x -= brake.x*dt;
	mainVec.y -= brake.y*dt;
}
void Car::Rotate(int direction) const
{

	//Check if the car is moving
	if (body->GetVelocity().LengthSquared() > EPS)
	{
		//Make the player Rotate
		if (direction == -1)
		{
			body->AngularVelocity(-RotForce);
		}
		else if (direction == 1)
		{
			body->AngularVelocity(RotForce);
		}
		//If the player is not pressing any key, make the player stop rotating with a friction only for the rotation
		else
		{
			if (body->body->GetAngularVelocity() > 0.1)
			{
				body->AddTorque(-RotFriction);
			}
			else if (body->body->GetAngularVelocity() < -0.1)
			{
				body->AddTorque(RotFriction);
			}
			else
			{
				body->AngularVelocity(0);
			}
		}
	}
	else
	{
		body->AngularVelocity(0);
	}
}
void Car::Jump()
{
	if (recoveryTime.ReadSec() > airTime)
	{
		//Start the timer
		if (body->GetGroup() == Group::LAND)
		{
			jumpTimer.Start();
		}

		//Go up
		if (jumpTimer.ReadSec() <= airTime / 2)
		{
			state = STATES::JUMPING;
			scale += jumpaScale;
			//Change Collision group
			body->ChangeGroup(AIR);
		}
		//Go down
		else if (jumpTimer.ReadSec() > airTime / 2 && jumpTimer.ReadSec() <= airTime)
		{
			state = STATES::FALLING;
			scale -= jumpaScale;
		}
		//Reset all the values
		else if (jumpTimer.ReadSec() > airTime)
		{
			state = STATES::END_DRIFTING;
			scale = 1;
			//Change Collision group
			body->ChangeGroup(LAND);
			jump = false;
			recoveryTime.Start();
		}
	}
}
bool Car::TryJump()
{
	if (recoveryTime.ReadSec() > 1 )
	{
		jump = true;
		return true;
	}

	return false;

}






float Car::GetAngleOfVector(const b2Vec2& vec)
{
	return atan2(vec.y, vec.x); // atan2 returns the angle in radians
}
b2Vec2 Car::GetAcceleration()  
{ 
	return Acceleration; 
}

float Car::lerpAngle(float from, float to, float t) {


	// Geth The short path, if not it rotattes wirrd
	float diff = fmod(to - from, 2 * PI);
	if (diff > PI) {
		diff -= 2 * PI;
	}

	//Return the lerp angle
	return fmod(from + diff * t, 2 * PI);
}




void Car::ApplyMovement()
{
	dt = GetFrameTime();
	//Apply the friction to the car
	ApplyFriction();

	//Check The values of the velocities to stop it moveing
	CheckEps();

	//Check Road Limits
	//RoadLimits();

	//get the angle of the car inside the 360 degree range
	float angle = normalizeAngle(body->body->GetAngle());

	switch (state)
	{
	case STATES::DRIVING:

		direction = lerpAngle(GetAngleOfVector(body->GetVelocity()), angle, NormalLerp);
		RotForce = 1;

		break;
	case STATES::DRIFTING:

		direction = lerpAngle(GetAngleOfVector(body->GetVelocity()), angle, DriftLerp);
		RotForce = 2;

		break;
	case STATES::END_DRIFTING:

		direction = lerpAngle(GetAngleOfVector(body->GetVelocity()), angle, EndDriftLerp);

		//This checks if the angles are as close together to be considered the same
		if (std::fabs(GetAngleOfVector(body->GetVelocity()) - angle) <= EPS)
		{
			state = STATES::DRIVING;
		}

		RotForce = 1;

		break;
	case STATES::JUMPING:

		direction = lerpAngle(GetAngleOfVector(body->GetVelocity()), angle, JumpLerp);
		RotForce = 0.5;

		break;
	case STATES::FALLING:

		direction = lerpAngle(GetAngleOfVector(body->GetVelocity()), angle, JumpLerp);
		RotForce = 0.5;

		break;
	default:
		break;
	}

	//Set all the values to the car with a vector
	b2Vec2 vector;
	vector.x = cos(direction) * mainVec.x;
	vector.y = sin(direction) * mainVec.y;
	body->body->SetLinearVelocity(vector);
}



void Car::CheckEps()
{
	if (abs(body->GetVelocity().x) < EPS)
	{
		SetXvelocity(0);
	}
	if (abs(body->GetVelocity().y) < EPS)
	{
		SetYvelocity(0);
	}
}

void Car::RoadLimits()
{
	if (body->entity->OnRoad) 
	{
		body->body->SetLinearDamping(0);
	}
	else 
	{
		body->body->SetLinearDamping(50);
	}
}



float Car::normalizeAngle(float angle) {

	float twoPi = 2.0f * PI; //==360 degrees

	angle = fmod(angle, twoPi); //Thiis makes the angle be inside the 360 degree range

	if (angle < 0) {
		angle += twoPi;  //Then set the angle to the positives
	}

	//All of this is maded beacouse the rotation in Box2D is in radians and it goes over the 360 degrees, so when we are
	//doing the lerp if this is not maded the car will rotate weirdly

	return angle;
}


//PLAYER////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Player::CheckGear()
{
	b2Vec2 PlayerVel = body->GetVelocity();

	//Check the gear in each moment, and set diferent variables to the car, so that each gear ist equilibrated
	switch (GearChange)
	{
	case 0:
		Acceleration = { 4,4 };
		brake = { Acceleration.x/2,Acceleration.y/2 };

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
	if (GearChange < 3 && PlayerVel.Length() > GetMaxVel().Length())
	{
		CanChangeGear = true;
		return true;
	}
	 
	return false;

}
void Player::GearBack()
{
	b2Vec2 PlayerVel = body->GetVelocity();
	//Set the gears back if nessessary
	if (GearChange != 0 && PlayerVel.Length() < Gears[GearChange - 1].Length()*0.8)
	{
		CanChangeGear = false;
		GearChange--;
	}
}
b2Vec2 Player::GetMaxVel()
{
	//get the maximum velocity that the car can reach in each gear
	b2Vec2 MaxVel = Gears[GearChange];
	MaxVel += GetFriction(MaxVel);
	return MaxVel;
}

Vector2 Player::GetPosition() {
	int x, y;
	body->GetPhysicPosition(x, y);
	return Vector2{ (float)x, (float)y };
}

vector<b2Vec2> Player::B2Vec2ListFromArray(const int* points, int numPoints)
{
	vector<b2Vec2> vec2List;

	for (size_t i = 0; i < numPoints; ++i) {
		float x = PIXEL_TO_METERS(points[i * 2]);
		float y = PIXEL_TO_METERS(points[i * 2] + 1);

		vec2List.push_back(b2Vec2(x, y));
	}

	return vec2List;
}

bool Player::PointInsidePoly(const b2Vec2& point, vector<b2Vec2> trackBoundaryPoints)
{

	int crossings = 0;
	int numPoints = trackBoundaryPoints.size();

	for (size_t i = 0; i < numPoints; ++i) {
		b2Vec2 p1 = trackBoundaryPoints[i];
		b2Vec2 p2 = trackBoundaryPoints[(i + 1) % numPoints];

		// Check if the ray from the point crosses the edge between p1 and p2
		if ((point.y > p1.y) != (point.y > p2.y) &&
			point.x < (p2.x - p1.x) * (point.y - p1.y) / (p2.y - p1.y) + p1.x)
		{
			crossings++;
		}
	}

	// If crossings are odd point is inside the polygon
	return (crossings % 2) == 1;

}