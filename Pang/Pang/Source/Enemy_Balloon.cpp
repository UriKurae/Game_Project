#include "Enemy_Balloon.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "Particle.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleHarpoon_Shot.h"

#include "SDL/include/SDL.h"


Enemy_Balloon::Enemy_Balloon(int x, int y, enum class ENEMY_TYPE type) : Enemy(x,y)
{

	ballonExplosion = App->audio->LoadFx("Assets/Sound/FX/DestroyBalls.wav");

	tipoBalloon = type;
	if (App->player->scene1) {
		veryBigBalloonAnim.PushBack({ 207,112, 48, 40 });
		bigBalloonAnim.PushBack({ 257,119, 32, 26 });
		smallBalloonAnim.PushBack({ 292,125,16,14 });
		verySmallBalloonAnim.PushBack({ 312,129,8,7 });
	}
	if (App->player->scene2) {
		veryBigBalloonAnim.PushBack({ 206, 9, 48, 40 });
		bigBalloonAnim.PushBack({ 257, 16, 32, 26 });
		smallBalloonAnim.PushBack({ 291,22,16,14 });
		verySmallBalloonAnim.PushBack({ 311,26,8,7 });
	}

	particleDeathVeryBig.anim.PushBack({ 4,142,48,39 });
	particleDeathVeryBig.anim.PushBack({ 60,148,28,25 });
	particleDeathVeryBig.anim.PushBack({ 96,143,41,37 });
	particleDeathVeryBig.anim.PushBack({ 145,137,48,46 });
	particleDeathVeryBig.anim.speed = 0.25f;
	particleDeathVeryBig.anim.loop = false;

	particleDeathBig.anim.PushBack({ 4,85,32,26 });
	particleDeathBig.anim.PushBack({ 44,88,20,15 });
	particleDeathBig.anim.PushBack({ 72,85,27,26 });
	particleDeathBig.anim.PushBack({ 107,83,32,30 });
	particleDeathBig.anim.speed = 0.25f;
	particleDeathBig.anim.loop = false;

	particleDeathSmall.anim.PushBack({ 4,44,16,14 });
	particleDeathSmall.anim.PushBack({ 28,47,9,8 });
	particleDeathSmall.anim.PushBack({ 45,43,15,15 });
	particleDeathSmall.anim.PushBack({ 68,43,16,16 });
	particleDeathSmall.anim.speed = 0.25f;
	particleDeathSmall.anim.loop = false;

	particleDeathVerySmall.anim.PushBack({ 4,12,5,5 });
	particleDeathVerySmall.anim.PushBack({ 17,12,7,6 });
	particleDeathVerySmall.anim.PushBack({ 32,11,10,8 });
	particleDeathVerySmall.anim.speed = 0.25f;
	particleDeathVerySmall.anim.loop = false;

	currentAnim = &veryBigBalloonAnim;
	
	
	if (tipoBalloon == ENEMY_TYPE::VERYBIGBALLOON)
	{
		collider = App->collisions->AddCollider({ position.x, position.y, 48, 40 }, Collider::Type::VERY_BIG_BALLOON, (Module*)App->enemies);
		currentAnim = &veryBigBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::BIGBALLOON)
	{
		collider = App->collisions->AddCollider({ position.x, position.y, 32, 26 }, Collider::Type::BIG_BALLOON, (Module*)App->enemies);
		currentAnim = &bigBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::BIGBALLOON2)
	{
		collider = App->collisions->AddCollider({ position.x, position.y, 32, 26 }, Collider::Type::BIG_BALLOON, (Module*)App->enemies);
		currentAnim = &bigBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::SMALLBALLOON)
	{
		collider = App->collisions->AddCollider({ position.x, position.y, 16, 14 }, Collider::Type::SMALL_BALLOON, (Module*)App->enemies);
		currentAnim = &smallBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::SMALLBALLOON2)
	{
		collider = App->collisions->AddCollider({ position.x, position.y, 16, 14 }, Collider::Type::SMALL_BALLOON, (Module*)App->enemies);
		currentAnim = &smallBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON)
	{
		collider = App->collisions->AddCollider({ position.x, position.y, 8, 7 }, Collider::Type::VERY_SMALL_BALLOON, (Module*)App->enemies);
		currentAnim = &verySmallBalloonAnim;
	}
	else if (tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON2)
	{
		collider = App->collisions->AddCollider({ position.x, position.y, 8, 7 }, Collider::Type::VERY_SMALL_BALLOON, (Module*)App->enemies);
		currentAnim = &verySmallBalloonAnim;
	}

	
		
}

void Enemy_Balloon::Update()
{
	balloonBounce();
	
	if (App->player->destroyed)
	{
		collider->pendingToDelete = true;
	}

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
	
	//App->enemies->touchWall = false;

	/*if (c2 == App->scene->lowerWall) {
		if (c2->Intersects(collider->rect) == true) {
			speedY = 4.5f;
			App->enemies->touchWall = true;
		}
	}

	if (c2 == App->scene2->lowerWall) {
		if (c2->Intersects(collider->rect) == true) {
			speedY = 4.5f;
			App->enemies->touchWall = true;
		}
	}
	
	if (c2 == App->scene->rightWall) {
		if (c2->Intersects(collider->rect) == true) {
			speedX = -speedX;
			App->enemies->touchWall = true;
		}
	}

	if (c2 == App->scene2->rightWall) {
		if (c2->Intersects(collider->rect) == true) {
			speedX = -speedX;
			App->enemies->touchWall = true;
		}
	}

	if (c2 == App->scene->leftWall)
	{
		if (c2->Intersects(collider->rect) == true) {
			speedX = -speedX;
			App->enemies->touchWall = true;
		}
	}

	if (c2 == App->scene2->leftWall)
	{
		if (c2->Intersects(collider->rect) == true) {
			speedX = -speedX;
			App->enemies->touchWall = true;
		}
	}
	
	if (c2 == App->scene->upperWall) {
		if (c2->Intersects(collider->rect) == true) {
			speedY = -(speedY + 1.5f);
			App->enemies->touchWall = true;
		}
	}

	if (c2 == App->scene2->upperWall) {
		if (c2->Intersects(collider->rect) == true) {
			speedY = -(speedY + 1.5f);
			App->enemies->touchWall = true;
		}
	}*/
	
	if (c2->type == Collider::Type::WALL) {
			
		if (collider->rect.y + collider->rect.h > c2->rect.y && collider->rect.y < c2->rect.y) {
			speedY = 4.5f;
		}

		//if (collider->rect.x < c2->rect.x + c2->rect.w) {
		//	speedX = -speedX;
		//}

		else if (collider->rect.x + collider->rect.w > c2->rect.x) {
			speedX = -speedX;
		}

		//if (collider->rect.x < c2->rect.x + c2->rect.w) { //LeftWall
		//	speedX = -speedX;
		//}

			//else if (collider->rect.x + collider->rect.w > c2->rect.x) { //RightWall
			//	speedX = -speedX;
			//}

		
	}

	SDL_Rect r = collider->rect;

		if (c2 == App->harpoon->colliderH) {
			if (c2->Intersects(r) == true) {
				App->enemies->touchWall = false;
				if (tipoBalloon == ENEMY_TYPE::VERYBIGBALLOON)
				{
					App->player->lastBalloon = ENEMY_TYPE::VERYBIGBALLOON;
					collider->pendingToDelete = true;
					App->particles->AddParticle(particleDeathVeryBig, position.x, position.y, Collider::Type::NONE, 0);
					App->audio->PlayFx(ballonExplosion);
					App->enemies->AddEnemy(ENEMY_TYPE::BIGBALLOON, position.x, position.y);
					App->enemies->AddEnemy(ENEMY_TYPE::BIGBALLOON2, position.x, position.y);
					App->scene->balloonsOnScene--;
					App->scene2->balloonsOnScene--;
					App->player->score += 100;
					App->player->cont++;
					App->harpoon->totalColliders--;
				}
				else if (tipoBalloon == ENEMY_TYPE::BIGBALLOON || tipoBalloon == ENEMY_TYPE::BIGBALLOON2)
				{
					if (App->player->lastBalloon == ENEMY_TYPE::BIGBALLOON && tipoBalloon == ENEMY_TYPE::BIGBALLOON2 || App->player->lastBalloon == tipoBalloon) {
						App->player->cont++;
						App->player->score += 200 * App->player->cont;
					}
					else {
						App->player->score += 200;
						App->player->cont = 1;
					}
					App->player->lastBalloon = ENEMY_TYPE::BIGBALLOON;
					collider->pendingToDelete = true;
					App->particles->AddParticle(particleDeathBig, position.x, position.y, Collider::Type::NONE, 0);
					App->audio->PlayFx(ballonExplosion);
					App->enemies->AddEnemy(ENEMY_TYPE::SMALLBALLOON, position.x, position.y);
					App->enemies->AddEnemy(ENEMY_TYPE::SMALLBALLOON2, position.x, position.y);
					App->scene->balloonsOnScene--;
					App->scene2->balloonsOnScene--;
					App->harpoon->totalColliders--;
				}
				else if (tipoBalloon == ENEMY_TYPE::SMALLBALLOON || tipoBalloon == ENEMY_TYPE::SMALLBALLOON2)
				{
					if (App->player->lastBalloon == ENEMY_TYPE::SMALLBALLOON && tipoBalloon == ENEMY_TYPE::SMALLBALLOON2 || App->player->lastBalloon == tipoBalloon) {
						App->player->cont++;
						App->player->score += 300 * App->player->cont;
					}
					else {
						App->player->score += 300;
						App->player->cont = 1;
					}
					App->player->lastBalloon = ENEMY_TYPE::SMALLBALLOON;
					collider->pendingToDelete = true;
					App->particles->AddParticle(particleDeathSmall, position.x, position.y, Collider::Type::NONE, 0);
					App->audio->PlayFx(ballonExplosion);
					App->enemies->AddEnemy(ENEMY_TYPE::VERYSMALLBALLOON, position.x, position.y);
					App->enemies->AddEnemy(ENEMY_TYPE::VERYSMALLBALLOON2, position.x, position.y);
					App->scene->balloonsOnScene--;
					App->scene2->balloonsOnScene--;
					App->harpoon->totalColliders--;
			}
			else if (tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON || tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON2)
			{
				if (App->player->lastBalloon == ENEMY_TYPE::VERYSMALLBALLOON && tipoBalloon == ENEMY_TYPE::VERYSMALLBALLOON2 || App->player->lastBalloon == tipoBalloon) {
					App->player->cont++;
					App->player->score += 400 * App->player->cont;
				}
				else {
					App->player->score += 400;
					App->player->cont = 1;
				}
				App->player->lastBalloon = ENEMY_TYPE::VERYSMALLBALLOON;
				collider->pendingToDelete = true;
				App->particles->AddParticle(particleDeathVerySmall, position.x, position.y, Collider::Type::NONE, 0);
				App->audio->PlayFx(ballonExplosion);
				/*App->audio->UnloadFx(ballonExplosion);
				App->audio->activeFx--;*/
				App->scene->balloonsOnScene--;
				App->scene2->balloonsOnScene--;
				App->harpoon->totalColliders--;
			}
		}
	
	}
}