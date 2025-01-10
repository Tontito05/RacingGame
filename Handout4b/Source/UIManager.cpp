#include "Globals.h"
#include "Module.h"
#include "ModuleRender.h"
#include "UIManager.h"
#include "Text.h"
#include "Application.h"
#include "ModuleAudio.h"

UIManager::UIManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	Start();
}
UIManager::~UIManager() {}

bool UIManager::Start()
{
	TitleScreen = new UIelement(LoadTexture("Assets/UI_PC/PC_Title.png"), KEY_SPACE, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
	TitleScreen->setSetxture2(LoadTexture("Assets/UI_CONTROLLER/Controller_Title.png"));

	MainMenu = new UIelement(LoadTexture("Assets/UI_PC/PC_Menu.png"), KEY_M, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
	MainMenu->setSetxture2(LoadTexture("Assets/UI_CONTROLLER/Controller_Menu.png"));

	Controls = new UIelement(LoadTexture("Assets/UI_PC/PC_Controls.png"), KEY_A, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
	Controls->setSetxture2(LoadTexture("Assets/UI_CONTROLLER/Controller_Controls.png"));

	Credits = new UIelement(LoadTexture("Assets/UI_PC/PC_Credits.png"), KEY_D, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
	Credits->setSetxture2(LoadTexture("Assets/UI_CONTROLLER/Controller_Credits.png"));

	PauseMenu = new UIelement(LoadTexture("Assets/UI_PC/PC_Pause.png"), KEY_TAB, GAMEPAD_BUTTON_MIDDLE_RIGHT);
	PauseMenu->setSetxture2(LoadTexture("Assets/UI_CONTROLLER/Controller_Pause.png"));

	InGame = new UIelement(LoadTexture("Assets/UI_PC/PC_InGame.png"), KEY_W, GAMEPAD_BUTTON_LEFT_FACE_UP);
	InGame->setSetxture2(LoadTexture("Assets/UI_CONTROLLER/Controller_InGame.png"));

	Finish = new UIelement(LoadTexture("Assets/UI_PC/PC_Finish.png"), KEY_TAB, GAMEPAD_BUTTON_MIDDLE_RIGHT);
	Finish->setSetxture2(LoadTexture("Assets/UI_CONTROLLER/Controller_Finish.png"));

	JumpVisual = new UIelement(LoadTexture("Assets/UI_GENERAL/Jump.png"), KEY_ZERO, GAMEPAD_BUTTON_UNKNOWN);
	JumpVisual->setSetxture2(LoadTexture("Assets/UI_GENERAL/Jump.png"));
	GearVisual = new UIelement(LoadTexture("Assets/UI_GENERAL/Gear.png"), KEY_ZERO, GAMEPAD_BUTTON_UNKNOWN);
	GearVisual->setSetxture2(LoadTexture("Assets/UI_GENERAL/Gear.png"));

	Star1 = new UIelement(LoadTexture("Assets/UI_GENERAL/Star1.png"), KEY_ZERO, GAMEPAD_BUTTON_UNKNOWN);
	Star1->setSetxture2(LoadTexture("Assets/UI_GENERAL/Star1.png"));
	Star2 = new UIelement(LoadTexture("Assets/UI_GENERAL/Star2.png"), KEY_ZERO, GAMEPAD_BUTTON_UNKNOWN);
	Star2->setSetxture2(LoadTexture("Assets/UI_GENERAL/Star2.png"));
	Star3 = new UIelement(LoadTexture("Assets/UI_GENERAL/Star3.png"), KEY_ZERO, GAMEPAD_BUTTON_UNKNOWN);
	Star3->setSetxture2(LoadTexture("Assets/UI_GENERAL/Star3.png"));

	Chrono.Initialise("Assets/UI_GENERAL/Font.png", '0', 48);
	Velocity.Initialise("Assets/UI_GENERAL/Font.png", '0', 48);

	menuState = TITLE_SCREEN;
		
	//menuMusic = App->audio->LoadFx("Assets/Audio/menuMusic.wav");
	//inGameMusic = App->audio->LoadFx("Assets/Audio/ingameMusic.wav");
	clickFx = App->audio->LoadFx("Assets/Audio/click.wav");
		

	return true;
}

update_status UIManager::Update()
{
	
	switch (menuState)
	{
	case MenuStates::TITLE_SCREEN:

		if (IsKeyReleased(TitleScreen->key) || IsGamepadButtonReleased(0, TitleScreen->button))
		{
			menuState = MAIN_MENU;
			App->audio->PlayFx(clickFx);
		}		

		break;
	case MenuStates::MAIN_MENU:

		if (IsKeyReleased(Controls->key) || IsGamepadButtonReleased(0, Controls->button))
		{
			App->audio->PlayFx(clickFx);
			menuState = CONTROLS;
		}
		else if (IsKeyReleased(Credits->key) || IsGamepadButtonReleased(0, Credits->button))
		{
			App->audio->PlayFx(clickFx);
			menuState = CREDITS;
		}
		else if (IsKeyReleased(InGame->key) || IsGamepadButtonReleased(0, InGame->button))
		{
			App->audio->PlayFx(clickFx);
			menuState = INGAME;
			timer.Start();
		}
		else if (IsKeyReleased(Back_Keyboard) || IsGamepadButtonReleased(0, Back_Controller))
		{
			App->audio->PlayFx(clickFx);
			menuState = TITLE_SCREEN;
		}

		break;
	case MenuStates::CONTROLS:

		if (IsKeyReleased(Back_Keyboard) || IsGamepadButtonReleased(0, Back_Controller))
		{
			App->audio->PlayFx(clickFx);
			menuState = MAIN_MENU;
		}

		break;
	case MenuStates::CREDITS:

		if (IsKeyReleased(Back_Keyboard) || IsGamepadButtonReleased(0, Back_Controller))
		{
			App->audio->PlayFx(clickFx);
			menuState = MAIN_MENU;
		}

		break;
	case MenuStates::PAUSE_MENU:

		if (IsKeyReleased(PauseMenu->key) || IsGamepadButtonReleased(0, PauseMenu->button))
		{
			App->audio->PlayFx(clickFx);
			menuState = INGAME;
		}
		if (IsKeyReleased(MainMenu->key) || IsGamepadButtonReleased(0, MainMenu->button))
		{
			App->audio->PlayFx(clickFx);
			menuState = MAIN_MENU;
		}

		break;
	case MenuStates::INGAME:

		inGame = true;

		if (IsKeyReleased(PauseMenu->key) || IsGamepadButtonReleased(0, PauseMenu->button))
		{
			App->audio->PlayFx(clickFx);
			menuState = PAUSE_MENU;
		}
		
		break;
	case MenuStates::FINISH:

		timer.Stop();

		if (IsKeyReleased(Finish->key) || IsGamepadButtonReleased(0, Finish->button))
		{
			menuState = MAIN_MENU;
		}
		if (IsKeyReleased(Back_Keyboard) || IsGamepadButtonReleased(0, Back_Controller))
		{
			menuState = MAIN_MENU;
		}

		break;

	default:
		break;
	}

	

	return UPDATE_CONTINUE;
}

void UIManager::Render()
{
	switch (menuState)
	{
	case MenuStates::TITLE_SCREEN:

		TitleScreen->Draw( );

		break;
	case MenuStates::MAIN_MENU:

		MainMenu->Draw();

		break;
	case MenuStates::CONTROLS:

		Controls->Draw();

		break;
	case MenuStates::CREDITS:

		Credits->Draw();

		break;
	case MenuStates::PAUSE_MENU:

		PauseMenu->Draw();
		InGame->Draw();

		break;
	case MenuStates::INGAME:

		InGame->Draw();

		if (activeJump)
			JumpVisual->color.a = 255;
		else
			JumpVisual->color.a = 100;

		if (activeGear)
			GearVisual->color.a = 255;
		else
			GearVisual->color.a = 100;

		JumpVisual->Draw();
		GearVisual->Draw();

		Chrono.Draw(1110, 70, std::to_string(timer.ReadSec()), WHITE, 2);
		Velocity.Draw(  240,  25, std::to_string(PlayerVelocity*5), WHITE,3);

		break;
	case MenuStates::FINISH:

		Finish->Draw();
		InGame->Draw();

		JumpVisual->Draw();
		GearVisual->Draw();

		Chrono.Draw(1110, 70, std::to_string(timer.ReadSec()), WHITE, 2);
		Chrono.Draw(470, 300, std::to_string(timer.ReadSec()), WHITE, 2);

		Velocity.Draw(240, 25, "0.000", WHITE, 3);

		Star1->Draw();
		Star2->Draw();
		Star3->Draw();

		break;

	default:
		break;
	}

}

void UIelement::Draw()
{
	if (IsGamepadAvailable(0) == false)
	{
		DrawTexturePro(texture_pc, { 0.0f, 0.0f, (float)texture_pc.width, (float)texture_pc.height }, { 0, 0, (float)texture_pc.width, (float)texture_pc.height }, { 0, 0 }, 0.0f, color);
	}
	else
	{
		DrawTexturePro(texture_con, { 0.0f, 0.0f, (float)texture_con.width, (float)texture_con.height }, { 0, 0, (float)texture_con.width, (float)texture_con.height }, { 0, 0 }, 0.0f, color);
	}
	
}
