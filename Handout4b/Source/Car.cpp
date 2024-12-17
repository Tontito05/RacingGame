#include "Car.h"


b2Vec2 Car::GetFriction(b2Vec2 Velocity) const
{
	b2Vec2 Force = { 0,0 };

	//Check the velocity on the different axis
	if (Velocity.x > 0.1 || Velocity.x < 0.1)
	{
		Force.x = -Velocity.x * FrQueficient * GRAV;
	}
	if (Velocity.y > 0.1 || Velocity.y < -0.1)
	{
		Force.y = -Velocity.y * FrQueficient * GRAV;
	}

	return Force;
}
void Car::ApplyFriction(b2Vec2 Velocity)
{
	body->AddForce(GetFriction(Velocity));
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
	b2Vec2 velocity (GetVel().x/3, GetVel().y/3);
	b2Vec2 vec = ComputeVector(angle, velocity);

	//We use forces, important, if not the game works wierd
	body->AddForce(-vec);
}
void Car::Brake(float angle) 
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
	b2Vec2 PlayerVel = body->GetVelocity();

	if (GearChange < 3 && PlayerVel.Length() > GetMaxVel().Length()*0.8)
	{
		return true;
	}
	if (PlayerVel.Length() < GetMaxVel().Length())
	{
		return false;
	}

}
bool Player::GearBack()
{
	b2Vec2 PlayerVel = body->GetVelocity();

	if (GearChange != 0 && PlayerVel.Length() < Gears[GearChange - 1].Length()*0.3)
	{
		return true;
	}
	else
	{
		return false;
	}
}
b2Vec2 Player::GetMaxVel()
{
	b2Vec2 MaxVel = Gears[GearChange];
	MaxVel += GetFriction(MaxVel);
	return MaxVel;
}