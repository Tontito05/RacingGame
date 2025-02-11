#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "UIManager.h"
#include <iostream>


ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled), isDriftFxPlaying(false), isJumpFxPlaying(false)
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


	b2Vec2 start = { 332 * SCALE - 600, 330 * SCALE };
	map = new Map(App->physics, 0, 0, 79 * 16, 4 * 16, this, LAND);
	UI = new UIManager(App);

	player = new Player(App->physics, start.x - 20, start.y,  this,  LAND);
	ia_1 = new IA(App->physics, start.x, start.y,  this,  LAND, 1);
	ia_2 = new IA(App->physics, start.x, start.y,  this, LAND, 2);
	ia_3 = new IA(App->physics, start.x, start.y,  this,  LAND, 3);

	//We know this shouldn't be here, but didn't have time to change it, just to let you know that we are aware this is not the correct way
	//Load sound fx
	jumpFx = App->audio->LoadFx("Assets/Audio/jump.wav");
	driftFx = App->audio->LoadFx("Assets/Audio/drift.wav");
	gearFx = App->audio->LoadFx("Assets/Audio/gear.wav");

	return ret;
}

bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	delete player;
	delete ia_1;
	delete ia_2;
	delete ia_3;
	delete map;
	delete UI;

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
		ia_1->Pattern();
		ia_2->Pattern();
		ia_3->Pattern();
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
		else if (player->state == STATES::DRIFTING && (IsKeyUp(KEY_LEFT_SHIFT) || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER) > 0.5f))
		{
			player->state = STATES::END_DRIFTING;
			if (isDriftFxPlaying) {
				App->audio->StopFx(driftFx);
				isDriftFxPlaying = false;
			}
		}
		
		if (IsKeyDown(KEY_SPACE) && App->scene_intro->UI->inGame|| IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN ) && App->scene_intro->UI->inGame)
		{
			player->TryJump();
			if (!isJumpFxPlaying && player->TryJump())
			{
				App->audio->PlayFx(jumpFx);
				isJumpFxPlaying = true;
			}
		}
		else if (player->jump == false)
		{
			isJumpFxPlaying = false;
		}

		player->GearBack();

	}
	if (player->CanChangeGear == true && player->GearChange <3)//Manage the gear change
	{
		if (IsKeyPressed(KEY_G) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))//TODO put a timer to change the gear
		{
			//Augment the gear and the player acceleration/Brake
			player->GearChange++;
			App->audio->PlayFx(gearFx);
		}
	}
	else
	{
		player->CanChangeGear = false;
	}

	if (UI->menuState == UIManager::MenuStates::FINISH)
	{
		if (ia_1->finished == true && UI->position == 1)
		{
			UI->position++;
		}
		if (ia_2->finished == true && UI->position == 2)
		{
			UI->position++;
		}
		if (ia_3->finished == true && UI->position == 3)
		{
			UI->position++;
		}

		player->SetXvelocity(0);
		player->SetYvelocity(0);


		b2Vec2 start = { 332 * SCALE - 600, 330 * SCALE };

		if (UI->inGame == true)
		{
			player = new Player(App->physics, start.x, start.y, this,  LAND);
			ia_1 = new IA(App->physics, start.x, start.y,  this,  LAND, 1);
			ia_2 = new IA(App->physics, start.x, start.y,  this,  LAND, 2);
			ia_3 = new IA(App->physics, start.x, start.y,  this,  LAND, 3);
			UI->inGame = false;
		}

	}

	return UPDATE_CONTINUE;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//EXPLANATION: We check that coltype is CAR in case other bodies which are not cars are colliding with the map

	switch (bodyB->entity->colType)
	{
	case ColliderTypes::CAR:
		break;
	case ColliderTypes::MAP:
		
		if (bodyA->entity->colType == ColliderTypes::PLAYER)

		{
			player->SetFriction(0.5f);
		}

		break;
	case ColliderTypes::MUD:
		if (bodyA->entity->colType == ColliderTypes::PLAYER)
		{
			player->SetFriction(0.4f);
		}
		if (bodyA->entity->colType == ColliderTypes::CAR) 
		{
			ia_1->SetFriction(0.4f);
			ia_2->SetFriction(0.4f);
			ia_3->SetFriction(0.4f);
		}
		break;
	case ColliderTypes::FINISHLINE:

		if (bodyA->entity->colType == ColliderTypes::PLAYER)
		{

			UI->menuState = UIManager::MenuStates::FINISH;

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
		if (bodyA->entity->colType == ColliderTypes::PLAYER)
		{
			player->SetFriction(0.2f);
		}
		break;
	case ColliderTypes::MUD:

		if (bodyA->entity->colType == ColliderTypes::PLAYER)
		{
			player->SetFriction(0.2f);
		}
		if (bodyA->entity->colType == ColliderTypes::CAR)
		{
			ia_1->SetFriction(0.2f);
			ia_2->SetFriction(0.2f);
			ia_3->SetFriction(0.2f);
		}

		break;
	case ColliderTypes::NULLCOL:
		cout << "WARNING: " << bodyB << "'s ColliderType is NULL" << endl;
		break;
	default:
		break;
	
	case ColliderTypes::FINISHLINE:

		break;
	}

}