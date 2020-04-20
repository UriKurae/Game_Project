#include "Enemy_Balloon.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleScene.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleHarpoon_Shot.h"
#include <stdio.h>



Enemy_Balloon::Enemy_Balloon(int x, int y, enum class ENEMY_TYPE type) : Enemy(x,y)
{
	
	tipoBalloon = type;
	veryBigBalloonAnim.PushBack({ 207,112, 48, 40 });
	bigBalloonAnim.PushBack({ 257,119, 32, 26 });
	smallBalloonAnim.PushBack({292,125,16,14});
	verySmallBalloonAnim.PushBack({312,129,8,7});

	balloonDeath.PushBack({4,141,48,40});
	balloonDeath.PushBack({60,148,28,24});
	balloonDeath.PushBack({144,136,48,46});
	balloonDeath.speed = 0.1f;

	currentAnim = &veryBigBalloonAnim;
	
	
	if (tipoBalloon == ENEMY_TYPE::VERYBIGBALLOON)
	{
	printf("hola VERY BIG BALLOON");
	collider = App->collisions->AddCollider({ position.x, position.y, 48, 40 }, Collider::Type::VERY_BIG_BALLOON, (Module*)App->enemies);
	currentAnim = &veryBigBalloonAnim;
	}

	else if (tipoBalloon == ENEMY_TYPE::BIGBALLOON)//CLEAN ALL PRINTFS AND GET RID OF THE STDIO.H
	{
		printf("holaBIG BALLOON");

		collider = App->collisions->AddCollider({ position.x, position.y, 32, 26 }, Collider::Type::BIG_BALLOON, (Module*)App->enemies);
		
		currentAnim = &bigBalloonAnim;

	}
	else if (tipoBalloon == ENEMY_TYPE::BIGBALLOON2)
	{
		printf("hola BIG BALLOON 2");
		collider = App->collisions->AddCollider({ position.x, position.y, 32, 26 }, Collider::Type::BIG_BALLOON, (Module*)App->enemies);
		currentAnim = &bigBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::SMALLBALLOON)
	{
		printf("hola SMALL BALLOON");
		collider = App->collisions->AddCollider({ position.x, position.y, 16, 14 }, Collider::Type::SMALL_BALLOON, (Module*)App->enemies);
		currentAnim = &smallBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::SMALLBALLOON2)
	{
		printf("hola SMALL BALLOON");
		collider = App->collisions->AddCollider({ position.x, position.y, 16, 14 }, Collider::Type::SMALL_BALLOON, (Module*)App->enemies);
		currentAnim = &smallBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON)
	{
		printf("hola VERY SMALL BALLOON");
		collider = App->collisions->AddCollider({ position.x, position.y, 8, 7 }, Collider::Type::VERY_SMALL_BALLOON, (Module*)App->enemies);
		currentAnim = &verySmallBalloonAnim;
	}

	else if (tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON2)
	{
		printf("hola VERY SMALL BALLOON");
		collider = App->collisions->AddCollider({ position.x, position.y, 8, 7 }, Collider::Type::VERY_SMALL_BALLOON, (Module*)App->enemies);
		currentAnim = &verySmallBalloonAnim;
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

	if (!App->player->destroyed)
	{
		if (tipoBalloon == ENEMY_TYPE::BIGBALLOON2 || tipoBalloon == ENEMY_TYPE::SMALLBALLOON2 || tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON2) {

			position.x -= speedX;
			position.y -= (speedY + gravity);
			speedY -= gravity;
		}
		else {
			position.x += speedX;
			position.y -= (speedY + gravity);
			speedY -= gravity;
		}
	}
	
	//TODO PHYSICS, IMPLEMENT RIGHT, LEFT AND TOP HIT WITH THE BALLOON, SHOULD NOT GAIN SPEED.
}

void Enemy_Balloon::OnCollision(Collider* c2) {
	
	App->enemies->touchWall = false;
	
	SDL_Rect r = this->collider->rect;
	
	if (c2 == App->scene->lowerWall) {
		if (c2->Intersects(r)) {
			speedY = 4.5f;
			App->enemies->touchWall = true;
			LOG("\n\n\nBALLOON HIT FLOOR\n\n\n");
		}
	}
	
	if (c2 == App->scene->rightWall) {
		if (c2->Intersects(r)) {
			speedX = -speedX;
			App->enemies->touchWall = true;
			LOG("\n\n\nBALLOON HIT RIGHT WALL\n\n\n");
		}
	}

	if (c2 == App->scene->leftWall)
	{
		if (c2->Intersects(r)) {
			speedX = -speedX;
			App->enemies->touchWall = true;
			LOG("\n\n\nBALLOON HIT LEFT WALL\n\n\n");
		}
	}
	
	if (c2 == App->scene->upperWall) {
		if (c2->Intersects(r)) {
			speedY = -(speedY + 1.5f);
			App->enemies->touchWall = true;
			LOG("\nBALLOON HIT UPPER WALL\n");
		}
	}

	

	if (c2 == App->harpoon->colliderH) {
		if (c2->Intersects(r)) {

			if (tipoBalloon == ENEMY_TYPE::VERYBIGBALLOON)
			{
				
				App->enemies->AddEnemy(ENEMY_TYPE::BIGBALLOON, position.x, position.y);
				App->enemies->AddEnemy(ENEMY_TYPE::BIGBALLOON2, position.x, position.y);
				App->scene->balloonsOnScene--;
				
			}
			else if (tipoBalloon == ENEMY_TYPE::BIGBALLOON || tipoBalloon == ENEMY_TYPE::BIGBALLOON2)
			{
				App->enemies->AddEnemy(ENEMY_TYPE::SMALLBALLOON, position.x, position.y);
				App->enemies->AddEnemy(ENEMY_TYPE::SMALLBALLOON2, position.x, position.y);
				App->scene->balloonsOnScene--;

			}
			else if (tipoBalloon == ENEMY_TYPE::SMALLBALLOON || tipoBalloon == ENEMY_TYPE::SMALLBALLOON2)
			{
				App->enemies->AddEnemy(ENEMY_TYPE::VERYSMALLBALLOON, position.x, position.y);
				App->enemies->AddEnemy(ENEMY_TYPE::VERYSMALLBALLOON2, position.x, position.y);
				App->scene->balloonsOnScene--;

			}
			else if (tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON || tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON2)
			{
				App->scene->balloonsOnScene--;
			}
		}
	}
}