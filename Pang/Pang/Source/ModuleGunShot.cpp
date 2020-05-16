#include "ModuleGunShot.h"

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
#include "ModuleAudio.h"

#include <SDL\include\SDL_scancode.h>

ModuleGunShot::ModuleGunShot(bool startEnabled) : Module(startEnabled)
{

}

ModuleGunShot::~ModuleGunShot()
{

}

bool ModuleGunShot::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	texture = App->textures->Load("Assets/Items&Weapons/Mini explosion.png");
	++totalTextures;

	HarpoonFx = App->audio->LoadFx("Assets/Sound/FX/NormalShoot.wav");
	++totalFx;

	x = App->player->position.x;
	y = App->player->position.y - speed;



	return true;
}

update_status ModuleGunShot::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;


	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && destroyed == true && App->player->destroyed == false)
	{

		App->audio->PlayFx(HarpoonFx);
		++activeFx;

		x = App->player->position.x + 10;
		y = App->player->position.y - 2;
		destroyed = false;

	  /*colliderH = App->collisions->AddCollider({ (int)x, (int)y, 9, (int)h }, Collider::Type::PLAYER_SHOT, (Module*)App->gunShot);
		++activeColliders; ++totalColliders;*/

		App->particles->AddParticle(gunShotParticle, x - 3, y - 6, Collider::Type::NONE, 0);
		increment = true;

		++activeTextures;
	}

	if (increment == true) {
		y -= speed;
		/*h += speed;
		colliderH->SetPos(x, y);*/
	}

	if (App->player->destroyed == true)
	{
		/*if (colliderH != nullptr) {
			this->colliderH->pendingToDelete = true;
		}*/
		increment = false;
		destroyed = true;
	}

	if (time == 0)
	{
		/*if (colliderH != nullptr) {
			this->colliderH->pendingToDelete = true;
		}*/
		//--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		time = 5;
		count = 0;
		--activeTextures;
	}

	return ret;
}

update_status ModuleGunShot::PostUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	if (App->player->destroyed == false && destroyed == false)
	{
		App->render->Blit(texture, x, y, &(currentAnimation->GetCurrentFrame()), 1.0f);
	}

	return ret;
}

void ModuleGunShot::OnCollision(Collider* c1, Collider* c2)
{

}

//void ModuleGunShot::OnCollision(Collider* c1, Collider* c2)
//{
//	if (c2->type == Collider::Type::UNBREAKABLE_BLOCK)
//	{
//		this->colliderH->pendingToDelete = true;
//		--activeColliders; --totalColliders;
//		destroyed = true;
//		increment = false;
//		--activeTextures;
//	}
//
//	if (c2->type == Collider::Type::WALL)
//	{
//		this->colliderH->pendingToDelete = true;
//		--activeColliders; --totalColliders;
//		destroyed = true;
//		increment = false;
//		--activeTextures;
//	}
//
//	if (c2->type == Collider::Type::BREAKABLE_BLOCK) {
//		//delete colliderH;
//		this->colliderH->pendingToDelete = true;
//		--activeColliders; --totalColliders;
//		destroyed = true;
//		increment = false;
//		--activeTextures;
//		LOG("\n\n\nHARPOON HIT UPPER WALL\n\n\n");
//	}
//
//	if (c2->type == Collider::Type::BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
//	{
//		this->colliderH->pendingToDelete = true;
//		//--activeColliders; --totalColliders;
//		destroyed = true;
//		increment = false;
//		--activeTextures;
//		LOG("\n\n\nHARPOON HIT VERY BIG BALLOON\n\n");
//	}
//
//	--activeFx;
//}