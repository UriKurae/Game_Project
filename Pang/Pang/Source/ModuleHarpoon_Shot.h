#pragma once

#include "Animation.h"
#include "Module.h"
#include"p2Point.h"

struct SDL_Texture;

class ModuleHarpoon : public Module
{
public:
	//position where is released
	int x = 0;
	int y = 0;
	int h = 34;

	float speed = 1.5f;

	//texture for all the harpoons sprites
	SDL_Texture* texture = nullptr;

	Animation harpoonShot[25];

	Animation* currentAnimation = nullptr;

	Collider* collider = nullptr;

public:
	ModuleHarpoon();
	~ModuleHarpoon();

	//load all textures
	bool Start();

	update_status Update();

	update_status PostUpdate();

	void OnCollision(Collider* c1, Collider* c2) override;

};