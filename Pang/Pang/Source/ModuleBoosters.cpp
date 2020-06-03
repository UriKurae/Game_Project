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

	for (int i = 0; i < MAX; i++)
	{
		typeBooster[i].booster = false;
		typeBooster[i].anim.Reset();

	}

	doubleshotUI.PushBack({ 223, 68, 29, 32 });
	gunUI.PushBack({183, 76, 32, 24});
	hookUI.PushBack({261, 69, 32, 31});

	shieldInmunity.PushBack({ 105,69,32,39 });
	shieldInmunity.PushBack({ 65,69,33,38 });
	shieldInmunity.speed = 0.2f;
	shieldInmunity.loop = true;

	balloonD = false;
	
	return true;
}

update_status ModuleBoosters::Update()
{
	if (balloonD == true)
	{
	
		srand(SDL_GetTicks());

		//generatedNumber = rand() % 4;
		generatedNumber = 3;
		

		LOG("%d",generatedNumber);

		if (generatedNumber == 3)
		{
			//generatedNumber = rand() % 8;
			generatedNumber = 7;
			
		
			switch (generatedNumber)
			{

			case 0:
				if (typeBooster[CLOCK].booster == false)
				{
					typeBooster[CLOCK].posX = x;
					typeBooster[CLOCK].posY = y;

					typeBooster[CLOCK].collider = App->collisions->AddCollider({ typeBooster[CLOCK].posX, typeBooster[CLOCK].posY ,16,16 }, Collider::Type::BOOSTERS);

					typeBooster[CLOCK].anim.PushBack({ 8,9,16,16 });
					currentAnim = &typeBooster[CLOCK].anim;

					typeBooster[CLOCK].booster = true;
				}
				
				break;
			case 1:
				if (typeBooster[SANDHOURGLASS].booster == false)
				{
					typeBooster[SANDHOURGLASS].posX = x;
					typeBooster[SANDHOURGLASS].posY = y;

					typeBooster[SANDHOURGLASS].collider = App->collisions->AddCollider({ typeBooster[SANDHOURGLASS].posX, typeBooster[SANDHOURGLASS].posY ,16,16 }, Collider::Type::BOOSTERS);
					typeBooster[SANDHOURGLASS].anim.PushBack({ 48,9,16,16 });
					currentAnim = &typeBooster[SANDHOURGLASS].anim;

					typeBooster[SANDHOURGLASS].booster = true;
				}
				
				break;

			case 2:

				if (typeBooster[DYNAMITE].booster == false)
				{
					typeBooster[DYNAMITE].posX = x;
					typeBooster[DYNAMITE].posY = y;

					typeBooster[DYNAMITE].collider = App->collisions->AddCollider({ typeBooster[DYNAMITE].posX, typeBooster[DYNAMITE].posY ,16,16 }, Collider::Type::BOOSTERS);
					typeBooster[DYNAMITE].anim.PushBack({ 88,9,15,16 });
					typeBooster[DYNAMITE].anim.PushBack({ 111,9,16,16 });
					typeBooster[DYNAMITE].anim.PushBack({ 135,9,16,16 });
					currentAnim = &typeBooster[DYNAMITE].anim;
					typeBooster[DYNAMITE].anim.speed = 0.2f;
					typeBooster[DYNAMITE].booster = true;
				}
			
				break;

			case 3:

				if (typeBooster[SHIELD].booster == false)
				{
					typeBooster[SHIELD].posX = x;
					typeBooster[SHIELD].posY = y;
					typeBooster[SHIELD].collider = App->collisions->AddCollider({ typeBooster[SHIELD].posX, typeBooster[SHIELD].posY ,16,16 }, Collider::Type::BOOSTERS);

					typeBooster[SHIELD].anim.PushBack({ 6,42,16,14 });
					typeBooster[SHIELD].anim.PushBack({ 26,41,16,14 });
					typeBooster[SHIELD].anim.PushBack({ 49,40,16,14 });
					typeBooster[SHIELD].anim.PushBack({ 73,40,16,14 });
					typeBooster[SHIELD].anim.PushBack({ 97,40,16,14 });
					typeBooster[SHIELD].anim.PushBack({ 121,40,16,14 });
					typeBooster[SHIELD].anim.PushBack({ 145,40,16,14 });
					typeBooster[SHIELD].anim.PushBack({ 168,41,16,14 });
					currentAnim = &typeBooster[SHIELD].anim;
					typeBooster[SHIELD].anim.speed = 0.2f;
					typeBooster[SHIELD].booster = true;
				}
			
				break;
			case 4:

				if (typeBooster[GUN].booster == false)
				{
					typeBooster[GUN].posX = x;
					typeBooster[GUN].posY = y;
					typeBooster[GUN].collider = App->collisions->AddCollider({ typeBooster[GUN].posX, typeBooster[GUN].posY ,16,16 }, Collider::Type::BOOSTERS);
					typeBooster[GUN].anim.PushBack({ 269, 42, 16, 13 });
					currentAnim = &typeBooster[GUN].anim;
					typeBooster[GUN].booster = true;

				}

				break;

			case 5: 
				
				if (typeBooster[HOOK].booster == false)
				{
					typeBooster[HOOK].posX = x;
					typeBooster[HOOK].posY = y;
					typeBooster[HOOK].collider = App->collisions->AddCollider({ typeBooster[HOOK].posX, typeBooster[HOOK].posY ,16,16 }, Collider::Type::BOOSTERS);
					typeBooster[HOOK].anim.PushBack({ 191, 39, 15, 14 });
					currentAnim = &typeBooster[HOOK].anim;
					typeBooster[HOOK].booster = true;
				}
				
				break;
			case 6:
				
				if (typeBooster[DOUBLESHOT].booster == false)
				{
					typeBooster[DOUBLESHOT].posX = x;
					typeBooster[DOUBLESHOT].posY = y;
					typeBooster[DOUBLESHOT].collider = App->collisions->AddCollider({ typeBooster[DOUBLESHOT].posX, typeBooster[DOUBLESHOT].posY ,16,16 }, Collider::Type::BOOSTERS);
					typeBooster[DOUBLESHOT].anim.PushBack({ 230, 39, 15, 16 });
					currentAnim = &typeBooster[DOUBLESHOT].anim;
					typeBooster[DOUBLESHOT].booster = true;
				}

				break;
			case 7:

				if (typeBooster[EXTRALIFE].booster == false)
				{
					typeBooster[EXTRALIFE].posX = x;
					typeBooster[EXTRALIFE].posY = y;
					typeBooster[EXTRALIFE].collider = App->collisions->AddCollider({ typeBooster[EXTRALIFE].posX, typeBooster[EXTRALIFE].posY ,16,16 }, Collider::Type::BOOSTERS);
					typeBooster[EXTRALIFE].anim.PushBack({ 175, 8, 16, 16 });
					currentAnim = &typeBooster[EXTRALIFE].anim;
					typeBooster[EXTRALIFE].booster = true;
				}

				break;
			}
		}
	}

	balloonD = false;

	for (int i = 0; i < MAX; i++) {
		if (typeBooster[i].booster == true) {
			currentAnim->Update();
			typeBooster[i].posY += 2;
			typeBooster[i].collider->SetPos(typeBooster[i].posX, typeBooster[i].posY);
			if (typeBooster[i].posY >= 184) {
				typeBooster[i].posY = 184;
			}
		}
	}

	
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBoosters::PostUpdate()
{
	for (int i = 0; i < MAX; i++)
	{
		if (typeBooster[i].booster == true)
		{
			App->render->Blit(texture, typeBooster[i].posX, typeBooster[i].posY, &(typeBooster[i].anim.GetCurrentFrame()), 1.0f);
		}
	}
	shieldInmunity.Update();

	if (App->player->doubleshot) {
		App->render->Blit(texture, 97, 225, &doubleshotUI.GetCurrentFrame(), 1.0f);
	}
	return update_status::UPDATE_CONTINUE;
}

void ModuleBoosters::OnCollision(Collider* c1, Collider* c2)
{


}
