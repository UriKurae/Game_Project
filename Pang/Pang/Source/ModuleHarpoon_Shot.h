#pragma once

#include "Animation.h"
#include "Module.h"
#include "p2Point.h"
#include "Particle.h"


struct SDL_Texture;
struct Collider;

class ModuleHarpoon : public Module
{
public:
	//position where is released
	float x = 0;
	float y = 0;
	float h = 34;

	float speed = 1.5f;

	bool destroyed = true;

	bool increment = false;

	//texture for all the harpoons sprites
	SDL_Texture* texture = nullptr;

	Animation harpoonParticleShot;

	Animation* currentAnimation = nullptr;

	Collider* colliderH = nullptr;

	Particle harpoonParticle;


public:
	ModuleHarpoon(bool startEnabled);
	~ModuleHarpoon();

	//load all textures
	bool Start();

	update_status Update() override;

	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

};
