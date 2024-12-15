#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

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

	App->renderer->camera.x = App->renderer->camera.y = 0;

	car = LoadTexture("Assets/Car.png");
	bike = LoadTexture("Assets/Bike.png");
	


	Player = new Car(App->physics,SCREEN_WIDTH/2, SCREEN_HEIGHT/2, this, car);


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
	if(IsKeyPressed(KEY_SPACE))
	{
		ray_on = !ray_on;
		ray.x = GetMouseX();
		ray.y = GetMouseY();
	}

	// Prepare for raycast ------------------------------------------------------
	
	vec2i mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	vec2f normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------


	for (PhysicEntity* entity : entities)
	{
		entity->Update();
		if (ray_on)
		{
			int hit = entity->RayHit(ray, mouse, normal);
			if (hit >= 0)
			{
				ray_hit = hit;
			}
		}
	}
	

	// ray -----------------
	if(ray_on == true)
	{
		vec2f destination((float)(mouse.x-ray.x), (float)(mouse.y-ray.y));
		destination.Normalize();
		destination *= (float)ray_hit;

		DrawLine(ray.x, ray.y, (int)(ray.x + destination.x), (int)(ray.y + destination.y), RED);

		if (normal.x != 0.0f)
		{
			DrawLine((int)(ray.x + destination.x), (int)(ray.y + destination.y), (int)(ray.x + destination.x + normal.x * 25.0f), (int)(ray.y + destination.y + normal.y * 25.0f), Color{ 100, 255, 100, 255 });
		}
	}

	//PlayerUpdate

	b2Vec2 Velocity = Player->body->body->GetLinearVelocity();

	if (IsKeyDown(KEY_W) && ((Velocity.x < MaxVelocity.x) || (Velocity.y < MaxVelocity.y)))
	{
		Player->body->body->ApplyForce(-Vel, Player->body->body->GetWorldCenter(), true);
	}
	if (IsKeyDown(KEY_S) && ((Velocity.x < MaxVelocity.x) || (Velocity.y < MaxVelocity.y)))
	{
		Player->body->body->ApplyForce(Vel, Player->body->body->GetWorldCenter(), true);
	}
	if (IsKeyDown(KEY_A))
	{
		Player->body->body->ApplyTorque(0.1f, true);
	}
	if (IsKeyDown(KEY_D))
	{
		Player->body->body->ApplyTorque(-0.1f, true);
	}

	b2Vec2 Fr = Player->body->body->GetLinearVelocity();

	if (Fr.x > 0 )
	{
		Player->body->body->ApplyLinearImpulseToCenter({ -Fr.x*Friction,0 }, true);
	}
	else if(Fr.x < 0)
	{
		Player->body->body->ApplyLinearImpulseToCenter({ -Fr.x * Friction,0 }, true);
	}
	if (Fr.y > 0)
	{
		Player->body->body->ApplyLinearImpulseToCenter({ 0,-Fr.y * Friction, }, true);
	}
	else if (Fr.y < 0)
	{
		Player->body->body->ApplyLinearImpulseToCenter({ 0,-Fr.y * Friction, }, true);;
	}


	

	return UPDATE_CONTINUE;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}
