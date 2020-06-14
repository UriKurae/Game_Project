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
	Enemy_Balloon() {
		particleDeathVeryBig.anim.Reset();
	};

	//virtual void OnCollision(Collider* collider);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	//balloon motions
	float speedY = 0.05f;
	float gravity = 0.1f;
	float speedX = 1.0f;
	float speedX2 = -speedX;
	float speedY2 = speedY;

	uint ballonExplosion = 0;

	//Count of balloons on scene
	uint balloonsOnScene = 0;

	uint destroyBalloonsTime = 3;
	uint destroyBalloonsCount = 0;

	int countDestroyBalloons = 0;
	int timeDestroyBalloons = 3;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	iPoint tile;

	void balloonBounce();
	void balloonBounce2();

	void bigBalloonBounce();
	void bigBalloonBounce2();

	void smallBalloonBounce();
	void smallBalloonBounce2();

	void verySmallBalloonBounce();
	void verySmallBalloonBounce2();

	void MRUA();
	void dynamiteDestroy();

	void OnCollision(Collider* c1) override;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation veryBigBalloonAnim;
	Animation bigBalloonAnim;
	Animation smallBalloonAnim;
	Animation verySmallBalloonAnim;
	Animation balloonDeath;

	Particle particleDeathVeryBig;
	Particle particleDeathVeryBigBlue;
	Particle particleDeathBig;
	Particle particleDeathSmall;
	Particle particleDeathVerySmall;

	enum class ENEMY_TYPE tipoBalloon;
};

#endif // __ENEMY_BROWNSHIP_H__