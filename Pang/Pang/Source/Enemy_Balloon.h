#ifndef __ENEMY_BALLOON_H__
#define __ENEMY_BALLOON_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"
#include "Particle.h"



class Enemy_Balloon : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Balloon(int x, int y, enum class ENEMY_TYPE type);
	Enemy_Balloon() {};

	//virtual void OnCollision(Collider* collider);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//balloon motions
	float speedY = 0.0f;
	float gravity = 0.1f;
	float speedX = 1.0f;

	uint ballonExplosion = 0;

	uint balloonsOnScene = 0;
	
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

	Particle particleDeathVeryBig;
	Particle particleDeathBig;
	Particle particleDeathSmall;
	Particle particleDeathVerySmall;

	//uint ballonExplosion = 0;
	enum class ENEMY_TYPE tipoBalloon;
};

#endif // __ENEMY_BROWNSHIP_H__