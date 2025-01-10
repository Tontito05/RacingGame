#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "Car.h"
#include <math.h>

ModuleRender::ModuleRender(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    background = RAYWHITE;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRender::PreUpdate()
{
    BeginDrawing();
    ClearBackground(BEIGE);
    BeginMode2D(camera);

	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{

    camera.target = App->scene_intro->player->GetPosition();
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.f;

	//Render all the entities

	if (App->scene_intro->UI->inGame == true)
	{
		App->scene_intro->map->Render();
		App->scene_intro->ia->Render();
        App->scene_intro->player->Render();
	}

    EndMode2D();
    App->scene_intro->UI->Render();
    BeginMode2D(camera);

	//Give the player to the UI to get some values from it
    App->scene_intro->UI->GetPlayerGear(App->scene_intro->player->CanChangeGear);
	App->scene_intro->UI->GetPlayerJump(App->scene_intro->player->CanJump());
	App->scene_intro->UI->GetPlayerVelocity(App->scene_intro->player->body->GetVelocity().LengthSquared());

    return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
    // Draw everything in our batch!
    EndMode2D();
    DrawFPS(10, 10);
    EndDrawing();
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	return true;
}

void ModuleRender::SetBackgroundColor(Color color)
{
	background = color;
}

// Draw to screen
bool ModuleRender::Draw(Texture2D texture, int x, int y, const Rectangle* section, double angle, int pivot_x, int pivot_y) const
{

	bool ret = true;

	float scale = 1.0f;
    Vector2 position = { (float)x, (float)y };
    Rectangle rect = { 0.f, 0.f, (float)texture.width, (float)texture.height };

    if (section != NULL) rect = *section;

    position.x = (float)(x-pivot_x) * scale ;
    position.y = (float)(y-pivot_y) * scale ;

	rect.width *= scale;
	rect.height *= scale;

    DrawTextureRec(texture, rect, position, WHITE);

	return ret;
}

bool ModuleRender::DrawText(const char * text, int x, int y, Font font, int spacing, Color tint) const
{
    bool ret = true;

    Vector2 position = { (float)x, (float)y };

    DrawTextEx(font, text, position, (float)font.baseSize, (float)spacing, tint);

    return ret;
}