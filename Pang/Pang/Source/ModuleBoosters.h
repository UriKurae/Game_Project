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
	EXTRALIFE,
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

	void spawnBooster();

public:

	
	bool booster;
	
	float x;
	float y;


	//Store location of the mouse pointer
	int mouseX;
	int mouseY;
	
	Boost typeBooster[MAX];


	bool balloonD;

	

	int generatedNumber;


	//Animations
	Animation* currentAnim = nullptr;

	Animation doubleshotUI;
	Animation hookUI;
	Animation gunUI;

	Animation* inmunityAnim = nullptr;
	Animation shieldInmunity;

	SDL_Texture* texture = nullptr;
	

	
};
