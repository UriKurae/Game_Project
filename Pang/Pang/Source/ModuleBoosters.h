#pragma once


#include "Module.h"
#include "Animation.h"


struct SDL_Texture;
struct Collider;

struct Boost 
{
	int despawnTime = 0;
	int spawnRand = 0;
	bool booster = false;
	Collider* collider;
	Animation anim;

	//Position of the booster.
	int posX = 0, posY = 0;
	
};
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

	
	bool booster;
	
	float x;
	float y;

	
	Boost typeBooster[MAX];


	bool balloonD;

	

	int generatedNumber;


	//Animations
	Animation* currentAnim = nullptr;

	Animation* inmunityAnim = nullptr;
	Animation shieldInmunity;

	SDL_Texture* texture = nullptr;
	

	
};
