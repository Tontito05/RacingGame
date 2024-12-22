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
	player = new Player(App->physics, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 40,25,this,car,LAND);

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


	
	if (player->CheckGear() == false)
	{
		if (IsKeyDown(KEY_W))
		{
			player->MoveForward();
		}
		else if (IsKeyDown(KEY_S))
		{
			player->MoveBackwards();
		}

		if (IsKeyDown(KEY_SPACE))
		{
			player->state = STATES::DRIFTING;
			player->RotForce = 2;
		}
		else if (player->state == STATES::DRIFTING && IsKeyUp(KEY_SPACE))
		{
			player->state = STATES::END_DRIFTING;
		}
		else
		{
			player->RotForce = 1;
		}
	}
	if (player->CheckGear() == true)//Manage the gear change
	{
		DrawText("Press G to change gear", 10, 10, 20, RED);

		if (IsKeyDown(KEY_G))//TODO put a timer to change the gear
		{
			//Augment the gear and the player acceleration/Brake
			player->GearChange++;
			player->brake.x += 2;
			player->brake.y += 2;
		}
	}

	player->GearBack();
	player->ApplyMovement();

	std::cout << player->body->GetVelocity().Length() << std::endl;
	std::cout << player->GetMaxVel().Length()*0.8 << std::endl;

	return UPDATE_CONTINUE;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}
