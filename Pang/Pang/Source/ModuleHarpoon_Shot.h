#pragma once

#include "Animation.h"
#include "Module.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleHarpoon : public Module
{
public:
	//position where is released
	int x = 0;
	int y = 0;
	int h = 34;

	float speed = 1.5f;

	bool destroyed = false;

	//texture for all the harpoons sprites
	SDL_Texture* texture = nullptr;

	Animation harpoonShot[70];

	Animation* currentAnimation = nullptr;

	Collider* collider = nullptr;

public:
	ModuleHarpoon();
	~ModuleHarpoon();

	//load all textures
	bool Start();

	update_status Update() override;

	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

};
