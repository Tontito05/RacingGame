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
    /*camera.x = 0;
    camera.y = 0;
    camera.width = SCREEN_WIDTH;
    camera.height = SCREEN_HEIGHT;*/
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
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
    camera.target = App->scene_intro->player->GetPosition();
    //Previous Attempt Commented -Wakiren
    //camera.target.x = App->scene_intro->player->body->body->GetPosition().x;
    //camera.target.y = App->scene_intro->player->body->body->GetPosition().y;
    camera.offset = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.f;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera); 

    //cout << "PlayerX:" << App->scene_intro->player->body->body->GetPosition().x << endl;
    //cout << "CameraX:" << camera.target.x - camera.offset.x;

	//Render all the entities (I know this shouldnt be this way but or naw it works)

	if (App->scene_intro->UI->inGame == true)
	{
		App->scene_intro->map->Render();
		App->scene_intro->player->Render();
		App->scene_intro->ia->Render();
		App->scene_intro->mud->Render();
	}
    App->scene_intro->UI->Render(getCameraPosition());

	//Give the player to the UI to get some values from it
    App->scene_intro->UI->GetPlayerGear(App->scene_intro->player->CanChangeGear);
	App->scene_intro->UI->GetPlayerJump(App->scene_intro->player->CanJump());
	App->scene_intro->UI->GetPlayerVelocity(App->scene_intro->player->body->GetVelocity().LengthSquared());

    //std::cout << "Camera target: " << camera.target.x << " / " << camera.target.y << std::endl;
    EndMode2D();

    EndDrawing(); 

    return UPDATE_CONTINUE;
}


// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
    // Draw everything in our batch!
    DrawFPS(10, 10);

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

Vector2 ModuleRender::getCameraPosition() const
{
	Vector2 position = { camera.target.x-SCREEN_WIDTH/2, camera.target.y-SCREEN_HEIGHT/2 };
	return position;
}