#ifndef __ENEMY_BALLOON_H__
#define __ENEMY_BALLOON_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

struct SDL_Texture;

class Enemy_Balloon : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Balloon(int x, int y);

	float speedY = 0.0f;
	float gravity = 0.1f;
	float speedX = 1.0f;


	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	
private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation balloonAnim;
};

#endif // __ENEMY_BROWNSHIP_H__