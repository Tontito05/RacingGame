#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include <iostream>


ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ray_on = false;
}

ModuleGame::~ModuleGame()
{}

// Load assets
bool ModuleGame::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	Player = new Car(App->physics, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, this, car);

	car = LoadTexture("Assets/Car.png");
	bike = LoadTexture("Assets/Bike.png");

	Gears.push_back({ 1,1 });
	Gears.push_back({ 2,2 });
	Gears.push_back({ 3,3 });
	Gears.push_back({ 4,4 });


	return ret;
}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
	//PlayerUpdate

	//Get the player linear velocity
	b2Vec2 Velocity = Player->body->body->GetLinearVelocity();
	//get the player angular velocity
	float Angular = Player->body->body->GetAngularVelocity();
	//Get the player angle
	float angle = Player->body->body->GetAngle();

	//Maje the player Rotate
	if (IsKeyDown(KEY_A))
	{
		Player->body->body->SetAngularVelocity(-RotForce);
	}
	else if (IsKeyDown(KEY_D))
	{
		Player->body->body->SetAngularVelocity(RotForce);
	}
	//If the player is not pressing any key, make the player stop rotating with a friction only for the rotation
	else 
	{
		if (Angular > 0.1)
		{
			Player->body->body->ApplyTorque(-RotFriction, true);
		}
		else if (Angular < -0.1)
		{
			Player->body->body->ApplyTorque(RotFriction, true);
		}
		else
		{
			Player->body->body->SetAngularVelocity(0);
		}
	}

	//If the velocity of the player is less than the expected velocity to change the gear, make the player accelerate or brake
	if (Velocity.Length() < Gears[GearChange].Length())
	{
		if (IsKeyDown(KEY_W))
		{
			b2Vec2 vec = Player->body->ComputeVector(angle, Vel);

			//We use forces, important, if not the game works wierd
			Player->body->body->ApplyForceToCenter(vec, true);
		}
		if (IsKeyDown(KEY_S))
		{
			b2Vec2 vec =  Player->body->ComputeVector(angle, Brake);

			Player->body->body->ApplyForceToCenter(vec, true);
		}
	}
	if (GearChange < 3 && Velocity.Length() > Gears[GearChange].Length() * 0.9)//Manage the gear change
	{

		DrawText("Press G to change the gear", 100, 10, 20, GREEN);

		if (IsKeyPressed(KEY_G))
		{
			//Augment the gear and the player acceleration/Brake
			GearChange++;
			Vel.x *=1.25;
			Vel.y *=1.25;
			Brake.x *= 1.25;
			Brake.y *= 1.25;
		}
	}
	else if (GearChange != 0 && Velocity.Length() < Gears[GearChange - 1].Length())
	{
		GearChange--;
	}

	std::cout<<GearChange<<"     ";
	std::cout << Velocity.Length() << std::endl;

	//Manage the friction of the player
	b2Vec2 FrFriction = Player->body->Friction(Velocity);
	Player->body->body->ApplyForceToCenter(FrFriction, true);

	return UPDATE_CONTINUE;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}
