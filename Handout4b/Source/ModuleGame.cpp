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

	car = LoadTexture("Assets/MiniPixelPack2/Cars/Player.png");
	player = new Player(App->physics, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, car.width,car.height,this,car,LAND);
	mud = new Mud(App->physics, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 40, 40, this, LAND);
	map = new Map(App->physics, 0,0, 2048, 3840, this, LAND);


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


	float leftJoystickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);

		if (IsKeyDown(KEY_A) || leftJoystickX < -0.2f)
		{
			player->Rotate(-1);
		}
		else if (IsKeyDown(KEY_D) || leftJoystickX > 0.2f)
		{
			player->Rotate(1);
		}
		else
		{
			player->Rotate(0);
		}



	
	if (player->CheckGear() == false)
	{
		if (IsKeyDown(KEY_W) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_TRIGGER) > 0.5f)
		{
			player->MoveForward();
		}
		else if (IsKeyDown(KEY_S) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
		{
			player->MoveBackwards();
		}

		if ((IsKeyDown(KEY_LEFT_SHIFT) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER) > 0.5f) && player->jump == false)
		{
			player->state = STATES::DRIFTING;
		}
		else if (player->state == STATES::DRIFTING && (IsKeyUp(KEY_LEFT_SHIFT) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER) > 0.5f))
		{
			player->state = STATES::END_DRIFTING;
		}
		
		if (IsKeyDown(KEY_SPACE)|| IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
		{
			player->TryJump();
		}

		player->GearBack();

	}
	if (player->CheckGear() == true)//Manage the gear change
	{
		DrawText("Press G to change gear", 10, 10, 20, RED);

		if (IsKeyDown(KEY_G) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))//TODO put a timer to change the gear
		{
			//Augment the gear and the player acceleration/Brake
			player->GearChange++;
		}
	}

	// Update camera position to follow the player
	float playerX, playerY;
	playerX = player->body->body->GetPosition().x;
	playerY = player->body->body->GetPosition().y;
	
	
	//std::cout << player->GearChange<< std::endl;

	return UPDATE_CONTINUE;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	switch (bodyB->entity->colType)
	{
	case ColliderTypes::CAR:
		break;
	case ColliderTypes::MUD:
		bodyA->body->SetLinearDamping(200);
		break;
	case ColliderTypes::NULLCOL:
		cout << "WARNING: " << bodyB << "'s ColliderType is NULL" << endl;
		break;
	default:
		
		break;
	}
}
