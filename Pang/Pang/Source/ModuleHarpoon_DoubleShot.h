#pragma once

#include "Animation.h"
#include "Module.h"
#include "p2Point.h"
#include "Particle.h"

#define SHOTS 2

struct SDL_Texture;
struct Collider;

class ModuleDoubleShot : public Module
{
public:

	float x = 0;
	float y = 0;

	int shotsOnScreen = 0;

	int speed = 2;

	//texture for all the harpoons sprites
	SDL_Texture* texture = nullptr;

	struct DoubleShot
	{
		int x = 0;
		int y = 0;
		int h = 34;
		Collider* colliderH = nullptr;
		Animation DoubleShot;
		bool destroyed = true;
		bool increment = false;
	};

	DoubleShot harpoon[SHOTS];

	Particle harpoonShotParticle;

	uint HarpoonFx = 0;

public:
	ModuleDoubleShot(bool startEnabled);
	~ModuleDoubleShot();

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