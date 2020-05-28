#include "ModuleBoosters.h"

#include "ModulePlayer.h"
#include"Application.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "Enemy_Balloon.h"


#include <stdlib.h>

#include <SDL/include/SDL.h>


ModuleBoosters::ModuleBoosters(bool startEnabled) : Module(startEnabled)
{
	name = "BOOSTERS";
}

ModuleBoosters::~ModuleBoosters()
{
}

bool ModuleBoosters::Start()
{
	//Load the textures
	texture = App->textures->Load("Assets/Items&Weapons/Boosters.png");
	++totalTextures;

	balloonD = false;

	return true;
}

update_status ModuleBoosters::Update()
{
	if (balloonD == true)
	{
		/*LOG("BALLON POSITION %d , %d", posX, posY);*/
	
		srand(SDL_GetTicks());

		generatedNumber = rand() % 4;

		LOG("%d",generatedNumber);

		if (generatedNumber == 3)
		{
			generatedNumber = rand() % 7;

			switch (generatedNumber)
			{

			case 0:
				posX[CLOCK] = x;
				posY[CLOCK] = y;
				collider[CLOCK] = App->collisions->AddCollider({ posX[CLOCK], posY[CLOCK],16,16 }, Collider::Type::BOOSTERS);
				clockAnim.PushBack({ 8,9,16,16 });
				currentAnim = &clockAnim;
				booster[CLOCK] = true;
				
				break;
			case 1:
				posX[SANDHOURGLASS] = x;
				posY[SANDHOURGLASS] = y;
				collider[SANDHOURGLASS] = App->collisions->AddCollider({ posX[SANDHOURGLASS], posY[SANDHOURGLASS],16,16 }, Collider::Type::BOOSTERS);
				sandHourglassAnim.PushBack({ 48,9,16,16 });
				currentAnim = &sandHourglassAnim;
				booster[SANDHOURGLASS] = true;
				
				break;

			case 2:
				posX[DYNAMITE] = x;
				posY[DYNAMITE] = y;
				collider[DYNAMITE] = App->collisions->AddCollider({ posX[DYNAMITE], posY[DYNAMITE],16,16 }, Collider::Type::BOOSTERS);
				dynamiteAnim.PushBack({ 88,12,15,13 });
				dynamiteAnim.PushBack({ 111,9,16,16 });
				dynamiteAnim.PushBack({ 135,9,16,16 });
				currentAnim = &dynamiteAnim;
				booster[DYNAMITE] = true;
			
				break;

			case 3:
				posX[SHIELD] = x;
				posY[SHIELD] = y;
				collider[SHIELD] = App->collisions->AddCollider({ posX[SHIELD], posY[SHIELD],16,14 }, Collider::Type::BOOSTERS);
				shieldAnim.PushBack({ 9,46,10,8 });
				shieldAnim.PushBack({ 27,42,14,12 });
				shieldAnim.PushBack({ 49,40,16,14 });
				shieldAnim.PushBack({ 73,40,16,14 });
				shieldAnim.PushBack({ 97,40,16,14 });
				shieldAnim.PushBack({ 121,40,16,14 });
				shieldAnim.PushBack({ 145,40,16,14 });
				shieldAnim.PushBack({ 169,42,14,12 });
				currentAnim = &shieldAnim;
				shieldAnim.speed = 0.1f;
				booster[SHIELD] = true;
			
				break;
			case 4:
				posX[GUN] = x;
				posY[GUN] = y;
				collider[GUN] = App->collisions->AddCollider({ posX[GUN], posY[GUN],16,13 }, Collider::Type::BOOSTERS);
				gunAnim.PushBack({ 269, 42, 16, 13 });
				currentAnim = &gunAnim;
				booster[GUN] = true;

				break;

			case 5: 
				posX[HOOK] = x;
				posY[HOOK] = y;
				collider[HOOK] = App->collisions->AddCollider({ posX[HOOK], posY[HOOK],15,16 }, Collider::Type::BOOSTERS);
				hookAnim.PushBack({ 191, 39, 15, 14 });
				currentAnim = &hookAnim;
				booster[HOOK] = true;
				
				break;
			case 6:
				posX[DOUBLESHOT] = x;
				posY[DOUBLESHOT] = y;
				collider[DOUBLESHOT] = App->collisions->AddCollider({ posX[DOUBLESHOT], posY[DOUBLESHOT],15,16 }, Collider::Type::BOOSTERS);
				doubleshotAnim.PushBack({ 230, 39, 15, 16 });
				currentAnim = &doubleshotAnim;
				booster[DOUBLESHOT] = true;

				break;
			}
		}
	}

	balloonD = false;
	
	//if (gunIsAlive || hookIsAlive || shieldIsAlive || dynamiteIsAlive || doubleshotIsAlive || sandIsAlive || clockIsAlive) {
	//	currentAnim->Update();
	//	posY += 2;
	//	collider->SetPos(posX, posY);
	//}

	for (int i = 0; i < MAX; i++) {
		if (booster[i] == true) {
			currentAnim->Update();
			posY[i] += 2;
			collider[i]->SetPos(posX[i], posY[i]);
			if (posY[i] >= 184) {
				posY[i] = 184;
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBoosters::PostUpdate()
{
	if (booster[CLOCK] == true) {
		App->render->Blit(texture, posX[CLOCK], posY[CLOCK], &(clockAnim.GetCurrentFrame()), 1.0f);
	}

	if (booster[SANDHOURGLASS] == true) {
		App->render->Blit(texture, posX[SANDHOURGLASS], posY[SANDHOURGLASS], &(sandHourglassAnim.GetCurrentFrame()), 1.0f);
	}

	if (booster[SHIELD] == true) {
		App->render->Blit(texture, posX[SHIELD], posY[SHIELD], &(shieldAnim.GetCurrentFrame()), 1.0f);
	}

	if (booster[DYNAMITE] == true) {
		App->render->Blit(texture, posX[DYNAMITE], posY[DYNAMITE], &(dynamiteAnim.GetCurrentFrame()), 1.0f);
	}

	if (booster[GUN] == true) {
		App->render->Blit(texture, posX[GUN], posY[GUN], &(gunAnim.GetCurrentFrame()), 1.0f);
	}

	if (booster[DOUBLESHOT] == true) {
		App->render->Blit(texture, posX[DOUBLESHOT], posY[DOUBLESHOT], &(doubleshotAnim.GetCurrentFrame()), 1.0f);
	}

	if (booster[HOOK] == true) {
		App->render->Blit(texture, posX[HOOK], posY[HOOK], &(hookAnim.GetCurrentFrame()), 1.0f);
	}


	return update_status::UPDATE_CONTINUE;
}

void ModuleBoosters::OnCollision(Collider* c1, Collider* c2)
{


}
