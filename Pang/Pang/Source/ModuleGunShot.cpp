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


	gunShotParticle.anim.PushBack({ 62, 13, 16, 6 });
	gunShotParticle.anim.PushBack({ 76, 8, 16, 11 });
	gunShotParticle.anim.PushBack({ 95, 9, 16, 10 });
	gunShotParticle.anim.PushBack({ 119, 5, 16, 14 });
	gunShotParticle.anim.loop = false;
	gunShotParticle.anim.speed = 0.3f;
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

		App->particles->AddParticle(gunShot, x - 3, y - 6, Collider::Type::PLAYER_SHOT, 0);

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

	return ret;
}

void ModuleGunShot::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::UNBREAKABLE_BLOCK)
	{
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		--activeTextures;
	}

	if (c2->type == Collider::Type::WALL)
	{
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		--activeTextures;
	}

	if (c2->type == Collider::Type::BREAKABLE_BLOCK) {
		//delete colliderH;
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		--activeTextures;
		LOG("\n\n\nHARPOON HIT UPPER WALL\n\n\n");
	}

	if (c2->type == Collider::Type::BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		//--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		--activeTextures;
		LOG("\n\n\nHARPOON HIT VERY BIG BALLOON\n\n");
	}

	--activeFx;
}