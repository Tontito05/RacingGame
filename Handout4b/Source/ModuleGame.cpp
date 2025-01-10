#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "UIManager.h"
#include <iostream>


ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled), isDriftFxPlaying(false)
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
	carOpponent = LoadTexture("Assets/MiniPixelPack2/Cars/Bronze.png");
	ia = new IA(App->physics, 332*SCALE -632, 330*SCALE -64, carOpponent.width, carOpponent.height, this, carOpponent, LAND);
	map = new Map(App->physics, 0, 0, 79 * 16, 4 * 16, this, LAND);
	player = new Player(App->physics, 332*SCALE -600, 330 * SCALE, car.width,car.height,this,car,LAND, map);
	mud = new Mud(App->physics, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 40, 40, this, LAND);
	UI = new UIManager(App);
	
	//Load sound fx
	jumpFx = App->audio->LoadFx("Assets/Audio/jump.wav");
	driftFx = App->audio->LoadFx("Assets/Audio/drift.wav");

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
		
	//Check if in game, if not, just update the UI
	if (UI->inGame == true)
	{
		//Update Entities
		map->Update();
		player->Update();
		ia->Pattern();
		//ia->Update();
		mud->Update();
	}
	UI->Update();

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
		if (IsKeyDown(KEY_S) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
		{
			player->MoveBackwards();
		}

		if ((IsKeyDown(KEY_LEFT_SHIFT) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER) > 0.5f) && player->jump == false)
		{
			player->state = STATES::DRIFTING;
			if (!isDriftFxPlaying) {
				App->audio->PlayFx(driftFx);
				isDriftFxPlaying = true;
			}
		}
		else if (player->state == STATES::DRIFTING && (IsKeyUp(KEY_LEFT_SHIFT) || ia->state == STATES::END_DRIFTING || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER) > 0.5f))
		{
			player->state = STATES::END_DRIFTING;
			isDriftFxPlaying = false;
		}
		
		if (IsKeyDown(KEY_SPACE) && App->scene_intro->UI->inGame|| IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN && App->scene_intro->UI->inGame))
		{
			player->TryJump();
			if (player->jump == true)
			{
				App->audio->PlayFx(jumpFx);
			}
		}

		player->GearBack();

	}
	if (player->CanChangeGear == true && player->GearChange <3)//Manage the gear change
	{
		if (IsKeyPressed(KEY_G) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))//TODO put a timer to change the gear
		{
			//Augment the gear and the player acceleration/Brake
			player->GearChange++;
		}
	}
	else
	{
		player->CanChangeGear = false;
	}

	//DEBUG FINISH
	if (IsKeyPressed(KEY_F))
	{
		UI->menuState = UIManager::MenuStates::FINISH;
		player->SetXvelocity(0);
		player->SetYvelocity(0);
		ia->SetXvelocity(0);
		ia->SetYvelocity(0);
	}

	//std::cout << GetMousePosition().x << "     " << GetMousePosition().y << endl;

	// Update camera position to follow the player
	float playerX, playerY;
	playerX = player->body->body->GetPosition().x;
	playerY = player->body->body->GetPosition().y;

	float iaX, iaY;
	iaX = ia->body->body->GetPosition().x;
	iaY = ia->body->body->GetPosition().y;

	std::cout << "Player: " << playerX << " " << playerY << " IA: " << iaX << " " << iaY << endl;

	return UPDATE_CONTINUE;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	switch (bodyB->entity->colType)
	{
	case ColliderTypes::CAR:
		break;
	case ColliderTypes::MAP:

		/*EXPLANATION:
		1 - We check that coltype is CAR in case other bodies which are not cars are colliding with the map
		2 - We check that the fixture of the bodyB is a sensor because we are interested in checking the chain sensor that limits the road, the decoration such
		as cactus and rocks are also in the map class but we don't want anything to happen when colliding with them
		*/
		
		if (bodyA->entity->colType == ColliderTypes::CAR && bodyB->body->GetFixtureList()->IsSensor() == true) 
		{
			//bodyA->entity->OnRoad = !bodyA->entity->OnRoad;
		}

		break;
	case ColliderTypes::MUD:
		if (bodyA->entity->colType == ColliderTypes::CAR) 
		{
			bodyA->body->SetLinearDamping(100);
			bodyA->body->SetAngularDamping(100);
		}

		break;
	case ColliderTypes::NULLCOL:
		cout << "WARNING: " << bodyB << "'s ColliderType is NULL" << endl;
		break;
	default:
		break;
	}
}

void ModuleGame::EndCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	switch (bodyB->entity->colType)
	{
	case ColliderTypes::CAR:
		break;
	case ColliderTypes::MAP:

		break;
	case ColliderTypes::MUD:
		bodyA->body->SetLinearDamping(0);
		bodyA->body->SetAngularDamping(0);
		break;
	case ColliderTypes::NULLCOL:
		cout << "WARNING: " << bodyB << "'s ColliderType is NULL" << endl;
		break;
	default:
		break;
	}
}
