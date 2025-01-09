#pragma once
#include "Globals.h"
#include "Module.h"
#include "Text.h"
#include "Timer.h"

class UIelement
{
public:
	UIelement(Texture2D texture_, KeyboardKey key_, GamepadButton button_) :texture_pc(texture_), key(key_), button(button_)
	{

	}
	~UIelement();

	void Draw();
	KeyboardKey key;
	GamepadButton button;

	void setSetxture2(Texture2D texture_controller)
	{
		texture_con = texture_controller;
	}

	Color color = WHITE;

private:

	Texture2D texture_pc;
	Texture2D texture_con;

};

class UIManager : public Module
{
public:
	UIManager(Application* app, bool start_enabled = true);
	~UIManager();

	bool Start();

	enum MenuStates
	{
		TITLE_SCREEN,
		MAIN_MENU,
		CONTROLS,
		CREDITS,
		PAUSE_MENU,
		INGAME,
		FINISH
	};

	MenuStates menuState = TITLE_SCREEN;
	bool inGame = false;

	update_status Update();
	void Render();

	void GetPlayerJump(bool Pjump)
	{
		activeJump = Pjump;
	}
	void GetPlayerGear(bool Pgear)
	{
		activeGear = Pgear;
	}
	void GetPlayerVelocity(float f)
	{
		PlayerVelocity = f;
	}

	bool activeGear;
	bool activeJump;
	float PlayerVelocity;

private:

	UIelement* TitleScreen;
	UIelement* MainMenu;
	UIelement* Controls;
	UIelement* Credits;
	UIelement* PauseMenu;
	UIelement* InGame;
	UIelement* Finish;

	UIelement* JumpVisual;
	UIelement* GearVisual;
	UIelement* Star1;
	UIelement* Star2;
	UIelement* Star3;

	Text Velocity;
	Text Chrono;

	Timer timer;

	KeyboardKey Back_Keyboard = KEY_B;
	GamepadButton Back_Controller = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT;

	Application* app;

	Music menuMusic;
};
