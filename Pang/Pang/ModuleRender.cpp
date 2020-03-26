#include "ModuleRender.h"

#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

#include "External_Libraries/SDL/include/SDL_render.h"
#include "External_Libraries/SDL/include/SDL_scancode.h"

ModuleRender::ModuleRender() : Module()
{

}

ModuleRender::~ModuleRender()
{

}

bool ModuleRender::Init()
{
	bool ret = true;

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{

	return update_status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
{
	bool ret = true;

	return ret;
}