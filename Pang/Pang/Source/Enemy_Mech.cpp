#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy (x,y)
{
	
	forw.PushBack({ 6, 108, 30, 29 });
	forw.PushBack({ 39, 108, 30, 29 });
	forw.PushBack({ 72, 105, 28, 32 });
	forw.speed = 0.07f;


	backw.PushBack({ 106, 105, 28, 32 });
	backw.PushBack({ 139, 108, 30, 29 });
	backw.PushBack({ 172, 105, 28, 32 });
	backw.speed = 0.07f;



	path.steps[0].animation = &forw;
	path.steps[1].animation = &backw;

	currentAnim = path.steps[0].animation;


	if (path.steps[0].framesDuration == 10)
	{
		currentAnim->Reset();
		currentAnim = path.steps[1].animation;
		
	}


	path.PushBack({ -0.5f,0 }, 120, path.GetCurrentAnimation());
	
	collider = App->collisions->AddCollider({ 0, 0, 30, 29 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Mech::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}