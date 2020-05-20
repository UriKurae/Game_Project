#include "ModuleScene6.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "Enemy_Balloon.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleHarpoon_Shot.h"
#include "ModuleHarpoon_HookShot.h"
#include "ModuleGunShot.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"
#include "IntroScene.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModuleScene6::ModuleScene6(bool startEnabled) : Module(startEnabled)
{
	name = "LEVEL 6";
}

ModuleScene6::~ModuleScene6()
{
}

bool ModuleScene6::Start()
{
	return false;
}

update_status ModuleScene6::Update()
{
	return update_status();
}

update_status ModuleScene6::PostUpdate()
{
	return update_status();
}

bool ModuleScene6::CleanUp()
{
	return false;
}
