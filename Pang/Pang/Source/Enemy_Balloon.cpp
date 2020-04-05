#include "Enemy_Balloon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Balloon::Enemy_Balloon(int x, int y) : Enemy(x,y)
{
	
	balloonAnim.PushBack({ 207,112, 48, 40 });
	balloonDeath.PushBack({4,141,48,40});
	balloonDeath.PushBack({60,148,28,24});
	balloonDeath.PushBack({144,136,48,46});
	balloonDeath.speed = 0.1f;

	currentAnim = &balloonAnim;

	collider = App->collisions->AddCollider({ 0, 0, 48, 40 }, Collider::Type::BALLOON, (Module*)App->enemies);

}

void Enemy_Balloon::Update()
{
	balloonBounce();
	
	
	 
	Enemy::Update();
}

void Enemy_Balloon::balloonBounce()
{
	//PHYSICS MOTIONS

	//TODO PHYSICS, IMPLEMENT RIGHT, LEFT AND TOP HIT WITH THE BALLOON, SHOULD NOT GAIN SPEED.
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
	if (position.x >= SCREEN_WIDTH - 50)
	{
		speedX = -speedX;
	}
	else if (position.x <= 8)
	{
		speedX = 1.0f;
	}
}

void Enemy_Balloon::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::WALL && c2->type == Collider::Type::PLAYER)
	{
		position.x = position.x;
	}




	if (c1->type == Collider::Type::BALLOON && c2->type == Collider::Type::PLAYER_SHOT)
	{
		currentAnim = &balloonDeath;
	}



}