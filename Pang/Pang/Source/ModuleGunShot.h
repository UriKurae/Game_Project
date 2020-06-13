#pragma once

#include "Animation.h"
#include "Module.h"
#include "p2Point.h"
#include "Particle.h"

#define MAX_GUNSHOT 7

struct SDL_Texture;
struct Collider;

class ModuleGunShot : public Module
{
public:
	//position where is released
	float x = 0;
	float y = 0;

	float speed = 2.0f;

	bool increment = false;
	bool canShot = false;

	//texture for all the harpoons sprites
	SDL_Texture* texture = nullptr;

	//Collider* colliderH = nullptr;

	Particle gunShotParticle;

	Particle shotGun;

	uint gunShotFx = 0;

public:

	ModuleGunShot(bool startEnabled);
	~ModuleGunShot();

	//load all textures
	bool Start();

	update_status Update() override;

	update_status PostUpdate() override;

	bool CleanUp() override;
};