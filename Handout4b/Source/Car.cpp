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
	//apply the friction to the Car
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
		//Maje the player Rotate
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

	//get the angle of the car inside the 360 degree range
	float angle = normalizeAngle(body->body->GetAngle());

	//If its drifting
	if (state == STATES::DRIFTING)
	{
		direction = lerpAngle(GetAngleOfVector(body->GetVelocity()), angle, DriftLerp);

	}
	//if its ending the drift
	else if (state == STATES::END_DRIFTING)
	{
		direction = lerpAngle(GetAngleOfVector(body->GetVelocity()), angle, EndDriftLerp);

		//This checks if the angles are as close together to be considered the same
		if (std::fabs(GetAngleOfVector(body->GetVelocity()) - angle) <= EPS)
		{
			state = STATES::DRIVEING;
		}
	}
	//Normal movement
	else
	{
		direction = lerpAngle(GetAngleOfVector(body->GetVelocity()), angle, NoDriftLerp);
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
		Acceleration = { 3,3 };
		brake = { Acceleration.x/2,Acceleration.y/2 };

		DriftLerp = 0.05;
		EndDriftLerp = 0.2;

		break;
	case 1:

		Acceleration = { 5,5 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.04;
		EndDriftLerp = 0.1;

		break;

	case 2:

		Acceleration = { 10 ,10 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.02;
		EndDriftLerp = 0.05;

		break;

	case 3:
		Acceleration = { 15,15 };
		brake = { Acceleration.x / 2,Acceleration.y / 2 };

		DriftLerp = 0.02;
		EndDriftLerp = 0.03;

		break;

	default:
		break;
	}

	//Naw chack if the player should or not change the gear
	if (GearChange < 3 && PlayerVel.Length() > GetMaxVel().Length()*0.8)
	{
		return true;
	}
	if (PlayerVel.Length() < GetMaxVel().Length())
	{
		return false;
	}



}
void Player::GearBack()
{
	b2Vec2 PlayerVel = body->GetVelocity();
	//Set the gears back if nessessary
	if (GearChange != 0 && PlayerVel.Length() < Gears[GearChange - 1].Length()*0.3)
	{
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

