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
	carB = LoadTexture("Assets/MiniPixelPack2/Cars/Bronze.png");
	carS = LoadTexture("Assets/MiniPixelPack2/Cars/Silver.png");
	carP = LoadTexture("Assets/MiniPixelPack2/Cars/Plat.png");

	b2Vec2 start = { 332 * SCALE - 600, 330 * SCALE };

	ia_1 = new IA(App->physics, start.x, start.y, car.width, car.height, this, carB, LAND, 1);
	ia_2 = new IA(App->physics, start.x, start.y, car.width, car.height, this, carS, LAND, 2);
	ia_3 = new IA(App->physics, start.x, start.y, car.width, car.height, this, carP, LAND, 3);
	car = LoadTexture("Assets/MiniPixelPack2/Cars/Player.png");
	map = new Map(App->physics, 0, 0, 79 * 16, 4 * 16, this, LAND);
	player = new Player(App->physics,start.x,start.y, car.width,car.height,this,car,LAND, map);
	UI = new UIManager(App);
	
	//Load sound fx
	jumpFx = App->audio->LoadFx("Assets/Audio/jump.wav");
	driftFx = App->audio->LoadFx("Assets/Audio/drift.wav");
	gearFx = App->audio->LoadFx("Assets/Audio/gear.wav");
	//runFx = App->audio->LoadFx("Assets/Audio/run.wav");

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
			//if (!isRunFxPlaying) {
			//	App->audio->PlayFx(runFx);
			//	isRunFxPlaying = true;
			//}
		}
		//else if (isRunFxPlaying) {
		//	App->audio->StopFx(runFx);
		//	isRunFxPlaying = false;
		//}
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

	//DEBUG FINISH
	if (IsKeyPressed(KEY_F))
	{
		UI->menuState = UIManager::MenuStates::FINISH;
		player->SetXvelocity(0);
		player->SetYvelocity(0);

		player = new Player(App->physics, 332 * SCALE - 600, 330 * SCALE, car.width, car.height, this, car, LAND, map);
		ia_1 = new IA(App->physics, 332 * SCALE - 632, 330 * SCALE - 64, car.width, car.height, this, carB, LAND,3);
		ia_2 = new IA(App->physics, 332 * SCALE - 632, 330 * SCALE - 64, car.width, car.height, this, carS, LAND, 2);
		ia_3 = new IA(App->physics, 332 * SCALE - 632, 330 * SCALE - 64, car.width, car.height, this, carP, LAND, 1);
	}


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
		We check that coltype is CAR in case other bodies which are not cars are colliding with the map
		*/
		
		if (bodyA->entity->colType == ColliderTypes::CAR ) 
		{
			bodyA->body->SetLinearDamping(50);
		}

		break;
	case ColliderTypes::MUD:
		if (bodyA->entity->colType == ColliderTypes::CAR) 
		{
			bodyA->body->SetLinearDamping(75);
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
		if (bodyA->entity->colType == ColliderTypes::CAR)
		{
			bodyA->body->SetLinearDamping(0);
		}
		break;
	case ColliderTypes::MUD:

		if (bodyA->entity->colType == ColliderTypes::CAR)
		{
			bodyA->body->SetLinearDamping(0);
		};

		break;
	case ColliderTypes::NULLCOL:
		cout << "WARNING: " << bodyB << "'s ColliderType is NULL" << endl;
		break;
	default:
		break;
	}
}