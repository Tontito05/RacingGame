#include "Car.h"


void Car::Friction(b2Vec2 Velocity) const
{
	b2Vec2 Force = { 0,0 };

	//Check the velocity on the different axis
	if (Velocity.x > 0 || Velocity.x < 0)
	{
		Force.x = -Velocity.x * FrQueficient * GRAV;
	}
	if (Velocity.y > 0 || Velocity.y < 0)
	{
		Force.y = -Velocity.y * FrQueficient * GRAV;
	}

	body->body->ApplyForceToCenter(Force, true);


}
b2Vec2 Car::ComputeVector(float angle, b2Vec2 impulse) const
{
	b2Vec2 vector = { 0,0 };

	vector.x = cos(angle) * impulse.x;
	vector.y = sin(angle) * impulse.y;

	return vector;
}
void Car::MoveForward(float angle) const
{
	b2Vec2 vec = ComputeVector(angle, Vel);

	//We use forces, important, if not the game works wierd
	body->AddForce(vec);

}
void Car::MoveBackwards(float angle) const
{
	b2Vec2 velocity (GetVel().x/2, GetVel().y/2);
	b2Vec2 vec = ComputeVector(angle, velocity);

	//We use forces, important, if not the game works wierd
	body->AddForce(-vec);
}
void Car::Brake(float angle) const
{
	b2Vec2 vec = ComputeVector(angle, brake);

	body->AddForce(vec);

}
void Car::Rotate(int direction) const
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
bool Player::CheckGear()
{
	if (GearChange < 3 && body->body->GetLinearVelocity().Length() > Gears[GearChange].Length() * 0.6)
	{
		return true;
	}
	if (body->body->GetLinearVelocity().Length() < Gears[GearChange].Length())
	{
		return false;
	}

}
bool Player::Slowing()
{
	if (GearChange != 0 && body->body->GetLinearVelocity().Length() < Gears[GearChange - 1].Length()*0.6)
	{
		return true;
	}
	else
	{
		return false;
	}
}