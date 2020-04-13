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
	Enemy_Balloon(int x, int y, enum class ENEMY_TYPE tipe);

	//virtual void OnCollision(Collider* collider);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//balloon motions
	float speedY = 0.0f;
	float gravity = 0.1f;
	float speedX = 1.0f;
	
private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	
	
	void balloonBounce();

	void OnCollision(Collider* c1) override;
	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation veryBigBalloonAnim;
	Animation bigBalloonAnim;
	Animation smallBalloonAnim;
	Animation verySmallBalloonAnim;
	Animation balloonDeath;
	enum class ENEMY_TYPE tipoBalloon;

};

#endif // __ENEMY_BROWNSHIP_H__