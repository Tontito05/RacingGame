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
    float playerX, playerY;
    playerX = App->scene_intro->player->GetPosition().x;
    playerY = App->scene_intro->player->GetPosition().y;
    
    camera1.target = { playerX + 20, playerY + 20 };
    
    BeginDrawing();
    ClearBackground(background);
    BeginMode2D(camera1);

    EndMode2D();
    
    camera1.target = { 0, 0};
    camera1.offset.x = -playerX + SCREEN_WIDTH / 2;
    camera1.offset.y = -playerY + SCREEN_HEIGHT / 2;
    camera1.rotation = 0.0f;
    camera1.zoom = 1.0f;

    std::cout << playerX << " / " << playerY << std::endl;
    std::cout << playerX << " / " << playerY << std::endl;

    // NOTE: This function setups render batching system for
    // maximum performance, all consecutive Draw() calls are
    // not processed until EndDrawing() is called
    
    
    EndTextureMode();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
    // Draw everything in our batch!
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

