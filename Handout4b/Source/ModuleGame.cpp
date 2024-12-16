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

	car = LoadTexture("Assets/Car.png");
	player = new Player(App->physics, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, car.width,car.height,this,car,LAND);

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
	b2Vec2 Velocity = player->body->body->GetLinearVelocity();
	//get the player angular velocity
	float Angular = player->body->body->GetAngularVelocity();
	//Get the player angle
	float angle = player->body->body->GetAngle();

	if (IsKeyDown(KEY_A))
	{
		player->Rotate(-1);
	}
	else if (IsKeyDown(KEY_D))
	{
		player->Rotate(1);
	}
	else
	{
		player->Rotate(0);
	}

	//If the velocity of the player is less than the expected velocity to change the gear, make the player accelerate or brake
	if (player->CheckGear()==false)
	{
		
		if (IsKeyDown(KEY_W))
		{
			player->MoveForward(angle);
		}
		if (IsKeyDown(KEY_W))
		{
			player->MoveForward(angle);
		}
	}
	if (player->CheckGear()==true)//Manage the gear change
	{
		DrawText("Press G to change gear", 10, 10, 20, RED);

		if (IsKeyDown(KEY_G) && Velocity.Length() < player->Gears[player->GearChange].Length())
		{
			//Augment the gear and the player acceleration/Brake
			player->GearChange++;
			player->Vel = player->Gears[player->GearChange];
		}
	}
	else if (player->Slowing() == true)
	{
		player->GearChange--;
		player->Vel = player->Gears[player->GearChange];
	}

	std::cout << player->GearChange << "     ";
	std::cout << player->Gears[player->GearChange].Length()*0.6 << "     ";
	std::cout << Velocity.Length() << std::endl;



	//Manage the friction of the player
	player->Friction(Velocity);


	return UPDATE_CONTINUE;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}
