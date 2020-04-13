#include "Enemy_Balloon.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleScene.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include <stdio.h>



Enemy_Balloon::Enemy_Balloon(int x, int y, enum class ENEMY_TYPE tipe) : Enemy(x,y)
{
	tipoBalloon = tipe;
	balloonAnim.PushBack({ 207,112, 48, 40 });
	balloonDeath.PushBack({4,141,48,40});
	balloonDeath.PushBack({60,148,28,24});
	balloonDeath.PushBack({144,136,48,46});
	balloonDeath.speed = 0.1f;

	currentAnim = &balloonAnim;
	
	if (tipoBalloon == ENEMY_TYPE::BIGBALLOON)//CLEAN ALL PRINTFS AND GET RID OF THE STDIO.H
	{
		printf("holaBIG BALLOON");
		collider = App->collisions->AddCollider({ 200, 0, 32, 26 }, Collider::Type::BIG_BALLOON, (Module*)App->enemies);
		balloonAnim.PushBack({ 257,119, 32, 26 });
		currentAnim = &balloonAnim;

	}else if (tipoBalloon == ENEMY_TYPE::VERYBIGBALLOON)
	{
		printf("hola VERY BIG BALLOON");
		collider = App->collisions->AddCollider({ position.x, position.y, 48, 40 }, Collider::Type::VERY_BIG_BALLOON, (Module*)App->enemies);
	}
	else if (tipoBalloon == ENEMY_TYPE::SMALLBALLOON)
	{
		printf("hola SMALL BALLOON");
		collider = App->collisions->AddCollider({ position.x, position.y, 48, 40 }, Collider::Type::VERY_BIG_BALLOON, (Module*)App->enemies);
	}
	else if (tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON)
	{
		printf("hola VERY SMALL BALLOON");
		collider = App->collisions->AddCollider({ position.x, position.y, 48, 40 }, Collider::Type::VERY_BIG_BALLOON, (Module*)App->enemies);
	}
	
	
		
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

void Enemy_Balloon::OnCollision(Collider* c2) {
	SDL_Rect r = this->collider->rect;
	if (c2->Intersects(r)) {
		
		App->enemies->AddEnemy(ENEMY_TYPE::BIGBALLOON,position.x, position.y);
		//collider = App->collisions->AddCollider({ 200, 0, 100, 100 }, Collider::Type::BIG_BALLOON, (Module*)App->enemies);
	}
}