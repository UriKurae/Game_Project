#pragma once


#include "Module.h"
#include "Animation.h"


struct SDL_Texture;
struct Collider;


enum boosters
{
	CLOCK,
	SANDHOURGLASS,
	DYNAMITE,
	SHIELD,
	GUN,
	HOOK,
	DOUBLESHOT,
	MAX
};

class ModuleBoosters:public Module
{

public:
	
	ModuleBoosters(bool startEnabled);

	~ModuleBoosters();

	bool Start();

	update_status Update() override;

	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

public:

	bool booster[MAX];

	//bool hookIsAlive = false;
	//bool doubleshotIsAlive = false;
	//bool gunIsAlive = false;
	//bool clockIsAlive = false;
	//bool sandIsAlive = false;
	//bool dynamiteIsAlive = false;
	//bool shieldIsAlive = false;

	bool balloonD;

	float x;
	float y;

	int generatedNumber;

	//Position of the booster.
	int posX[MAX], posY[MAX];

	//Animations
	Animation* currentAnim = nullptr;

	Animation clockAnim;
	Animation sandHourglassAnim;
	Animation dynamiteAnim;
	Animation shieldAnim;
	Animation gunAnim;
	Animation doubleshotAnim;
	Animation hookAnim;

	SDL_Texture* texture = nullptr;
	Collider* collider[MAX];

private:

	//Time to despawn the booster and random chance to spawn it
	int despawnTime;
	int spawnRand;
};
