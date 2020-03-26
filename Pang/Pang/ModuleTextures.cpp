#include "ModuleTextures.h"

#include "Application.h"
#include "ModuleRender.h"

#include "External_Libraries/SDL/include/SDL.h"
#include "External_Libraries/SDL_image/include/SDL_image.h"
#pragma comment( lib, "External_Libraries/SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
}

ModuleTextures::~ModuleTextures()
{}

bool ModuleTextures::Init()
{
	bool ret = true;

	
	return ret;
}

bool ModuleTextures::CleanUp()
{


	return true;
}
/*
SDL_Texture* const ModuleTextures::Load(const char* path)
{

	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

		if (texture == NULL)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			for (uint i = 0; i < MAX_TEXTURES; ++i)
			{
				if (textures[i] == nullptr)
				{
					textures[i] = texture;
					break;
				}
			}
		}

		SDL_FreeSurface(surface);
	}
	
	return texture;

}
	*/
