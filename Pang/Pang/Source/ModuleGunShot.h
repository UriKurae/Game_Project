#pragma once

#include "Animation.h"
#include "Module.h"
#include "p2Point.h"
#include "Particle.h"


struct SDL_Texture;
struct Collider;

class ModuleGunShot : public Module
{
public:
	//position where is released
	float x = 0;
	float y = 0;

	float speed = 2.0f;

	bool destroyed = true;

	bool increment = false;

	//texture for all the harpoons sprites
	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;

	Animation gunShot;
	Animation gunShotMove;

	//Collider* colliderH = nullptr;

	Particle gunShotParticle;

	Collider* colliderH = nullptr;

	uint gunShotFx = 0;

	uint time = 5;
	uint count = 0;
public:
	ModuleGunShot(bool startEnabled);
	~ModuleGunShot();

	//load all textures
	bool Start();

	update_status Update() override;

	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

};