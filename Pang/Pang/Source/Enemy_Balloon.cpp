#include "Enemy_Balloon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Balloon::Enemy_Balloon(int x, int y) : Enemy(x,y)
{
	
	balloonAnim.PushBack({ 1, 6, 48, 40 });

	currentAnim = &balloonAnim;

	collider = App->collisions->AddCollider({ 0, 0, 48, 40 }, Collider::Type::BALLOON, (Module*)App->enemies);

}

void Enemy_Balloon::Update()
{
	//PHYSICS MOTIONS
	if (position.y < (SCREEN_HEIGHT - 40))
	{

	position.x += speedX;
	position.y -= (speedY + gravity);
	speedY -= gravity;
		 
	}
	else if (position.y >= (SCREEN_HEIGHT - 40))
	{
		speedY = 4.5f;
		position.y -= speedY;
	}
    if (position.x >= SCREEN_WIDTH-50)
	{
		speedX = -speedX;
	}
	else if (position.x <= 8)
	{
		speedX = 1.0f;
	}
	//TODO PHYSICS, IMPLEMENT RIGHT, LEFT AND TOP HIT WITH THE BALLOON, SHOULD NOT GAIN SPEED.

	Enemy::Update();
}