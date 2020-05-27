#pragma once


#include "Module.h"
#include "Animation.h"


struct SDL_Texture;
struct Collider;


enum boosters
{
	clock,
	sandHourglass,
	dynamite,
	shield,
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

	bool booster = false;

	int generatedNumber;

	//Position of the booster.
	int posX, posY;

	//Animations
	Animation* currentAnim = nullptr;

	Animation clockAnim;
	Animation sandHourglassAnim;
	Animation dynamiteAnim;
	Animation shieldAnim;


private:

	//Time to despawn the booster and random chance to spawn it
	int despawnTime;
	int spawnRand;


	SDL_Texture* texture = nullptr;
	Collider* collider = nullptr;


};
