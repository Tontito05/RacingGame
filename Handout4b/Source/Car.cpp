#include "Car.h"


b2Vec2 Car::GetFriction(b2Vec2 vec) const
{
	b2Vec2 Force = { 0,0 };


	//Check the velocity on the different axis
	if (vec.x > 0.1 || vec.x < 0.1)
	{
		Force.x = -vec.x * FrQueficient * GRAV;
	}
	if (vec.y > 0.1 || vec.y < -0.1)
	{
		Force.y = -vec.y * FrQueficient * GRAV;
	}

	return Force;
}
void Car::ApplyFriction(float angle)
{
	SumToVec(GetFriction(mainVec));
}
b2Vec2 Car::ComputeVector(float angle, b2Vec2 impulse) const
{
	b2Vec2 vector = { 0,0 };

	vector.x = cos(angle) * impulse.x;
	vector.y = sin(angle) * impulse.y;

	return vector;
}
void Car::SumToVec(b2Vec2 f)
{
	mainVec.x += f.x;
	mainVec.y += f.y;
}
void Car::SubToVec(b2Vec2 f)
{
	mainVec.x -= f.x;
	mainVec.y -= f.y;
}
void Car::MoveForward(float angle) 
{
	//We use forces, important, if not the game works wierd
	SumToVec(ComputeVector(angle, Vel));
}
void Car::MoveBackwards(float angle) 
{
	//We use forces, important, if not the game works wierd
	SubToVec(ComputeVector(angle, brake));
}
void Car::Brake(float angle) 
{

	if (abs(body->GetVelocity().x)>0||abs(body->GetVelocity().y)>0)
	{
		b2Vec2 vec = ComputeVector(angle, -body->GetVelocity());
		vec.x *= brake.x;
		vec.y *= brake.y;

		if (body->GetVelocity().x < 0)
		{
			vec.x *= -1;
		}
		if (body->GetVelocity().y < 0)
		{
			vec.y *= -1;
		}

		SumToVec(vec);
	}
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