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
	position.x += 1;
	position.y -= 10 - 9, 8;

	Enemy::Update();
}