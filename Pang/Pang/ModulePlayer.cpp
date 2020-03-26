#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#include "External_Libraries/SDL/include/SDL_scancode.h"

// Street Fighter reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	return ret;
}

update_status ModulePlayer::Update()
{


	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	

	return update_status::UPDATE_CONTINUE;
}