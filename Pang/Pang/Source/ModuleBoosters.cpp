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
	return true;
}

update_status ModuleBoosters::Update()
{
	

	//De momento, pulsar 1 para comprobar el booster generado aleatoriamente
	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
	{
	
		/*LOG("BALLON POSITION %d , %d", posX, posY);*/
		

		srand(SDL_GetTicks());

		generatedNumber = rand() % 4;

		//LOG("%d",generatedNumber);

		if (generatedNumber == 3)
		{
			generatedNumber = rand() % 4;

			switch (generatedNumber)
			{

			case 0:

				App->collisions->AddCollider({ posX, posY,16,16 }, Collider::Type::BOOSTERS);
				clockAnim.PushBack({ 8,9,16,16 });
				currentAnim = &clockAnim;
				
				break;
			case 1:
				App->collisions->AddCollider({ posX, posY,16,16 }, Collider::Type::BOOSTERS);
				sandHourglassAnim.PushBack({ 48,9,16,16 });
				currentAnim = &sandHourglassAnim;
				
				break;

			case 2:
				App->collisions->AddCollider({ posX, posY,16,16 }, Collider::Type::BOOSTERS);
				dynamiteAnim.PushBack({ 88,12,15,13 });
				dynamiteAnim.PushBack({ 111,9,16,16 });
				dynamiteAnim.PushBack({ 135,9,16,16 });
				currentAnim = &dynamiteAnim;
			
				break;

			case 3:
				App->collisions->AddCollider({ posX, posY,16,14 }, Collider::Type::BOOSTERS);
				shieldAnim.PushBack({ 9,46,10,8 });
				shieldAnim.PushBack({ 27,42,14,12 });
				shieldAnim.PushBack({ 49,40,16,14 });
				shieldAnim.PushBack({ 73,40,16,14 });
				shieldAnim.PushBack({ 97,40,16,14 });
				shieldAnim.PushBack({ 121,40,16,14 });
				shieldAnim.PushBack({ 145,40,16,14 });
				shieldAnim.PushBack({ 169,42,14,12 });
				currentAnim = &shieldAnim;
			
				break;

			}

		}

	}


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBoosters::PostUpdate()
{

	
	
	
	
	App->render->Blit(texture, posX, posY, &(clockAnim.GetCurrentFrame()), 1.0f);
	App->render->Blit(texture, posX, posY, &(shieldAnim.GetCurrentFrame()), 1.0f);
	App->render->Blit(texture, posX, posY, &(dynamiteAnim.GetCurrentFrame()), 1.0f);
	App->render->Blit(texture, posX, posY, &(sandHourglassAnim.GetCurrentFrame()), 1.0f);
	


	return update_status::UPDATE_CONTINUE;
}

void ModuleBoosters::OnCollision(Collider* c1, Collider* c2)
{


}
