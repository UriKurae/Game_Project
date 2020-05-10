#pragma once

#include "Module.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "p2Point.h"

struct SDL_Texture;

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


public:
	bool Start();

	update_status Update() override;

	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;
	
};
