#pragma once

#include "Module.h"

class ModulePlatforms : public Module 
{
public:

	ModulePlatforms(bool startEnabled);

	~ModulePlatforms();

	//Position of the platform
	iPoint position;

	//Texture for the platform
	SDL_Texture* texture = nullptr;

	//Animation for when the platform starts to get destroyed
	Animation* currentAnimation = nullptr;

	//Animations (Provisional)
	Animation untouched;
	Animation touched;
	Animation almostDestroyed;

	
};
