#pragma once
#include "Animation.h"
#include "Module.h"
#include "p2Point.h"
#include "Particle.h"


struct SDL_Texture;
struct Collider;

class ModuleHookShot : public Module
{
public:
	//position where is released
	int x = 0;
	int y = 0;
	int h = 34;

	int speed = 2.0f;

	bool destroyed = true;

	bool timeToDestroy = false;

	bool increment = false;

	//texture for all the harpoons sprites
	SDL_Texture* texture = nullptr;

	Animation hookShot;
	Animation idleHookShot;

	Animation* currentAnimation = nullptr;

	Collider* colliderH = nullptr;

	Particle hookShotParticle;

	uint HarpoonFx = 0;

	uint time = 5;
	uint count = 0;
public:
	ModuleHookShot(bool startEnabled);
	~ModuleHookShot();

	//load all textures
	bool Start();

	update_status Update() override;

	void breakableCollision();

	void unbreakableCollision();

	void wallCollision();

	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	bool CleanUp() override;
};
