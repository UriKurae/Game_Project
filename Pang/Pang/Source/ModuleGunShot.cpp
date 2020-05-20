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
	this->gunShot.PushBack({ 99, 13, 5, 8 });
	this->gunShot.PushBack({ 112, 13, 8, 8 });
	this->gunShot.PushBack({ 128, 13, 12, 8 });
	this->gunShot.loop = false;
	
	/*gunShotMove.PushBack({ 99, 13, 5, 8 });
	gunShotMove.PushBack({ 99, 13, 5, 8 });
*/

	this->gunShotParticle.anim.PushBack({ 62, 13, 16, 6 });
	this->gunShotParticle.anim.PushBack({ 76, 8, 16, 11 });
	this->gunShotParticle.anim.PushBack({ 95, 9, 16, 10 });
	this->gunShotParticle.anim.PushBack({ 119, 5, 16, 14 });
	this->gunShotParticle.anim.loop = false;
	this->gunShotParticle.anim.speed = 0.3f;
}

ModuleGunShot::~ModuleGunShot()
{

}

bool ModuleGunShot::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	this->texture = App->textures->Load("Assets/Items&Weapons/Mini explosion.png");
	++totalTextures;

	this->gunShotFx = App->audio->LoadFx("Assets/Sound/FX/GunShoot.wav");
	++totalFx;

	this->x = App->player->position.x;
	this->y = App->player->position.y - speed;



	return true;
}

update_status ModuleGunShot::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;


	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->player->destroyed == false)
	{

		App->audio->PlayFx(gunShotFx);
		++activeFx;

		this->x = App->player->position.x + 10;
		this->y = App->player->position.y - 2;
		this->destroyed = false;

		this->colliderH = App->collisions->AddCollider({ (int)x, (int)y, 9, 8 }, Collider::Type::PLAYER_SHOT, (Module*)App->gunShot);
		++activeColliders; ++totalColliders;

		App->particles->AddParticle(gunShotParticle, x - 3, y - 6, Collider::Type::NONE, 0);
		this->increment = true;

		++activeTextures;
	}

	if (this->increment == true) {
		this->y -= speed;
		//h += speed;
		this->currentAnimation = &gunShot;
		/*if (gunShot.HasFinished())
		{
			currentAnimation = &gunShotMove;
		}
		else
		{
			currentAnimation = &gunShot;
		}*/
		this->currentAnimation->Update();
		this->colliderH->SetPos(x, y);
	}

	if (App->player->destroyed == true)
	{
		if (this->colliderH != nullptr) {
			this->colliderH->pendingToDelete = true;
		}
		this->increment = false;
		this->destroyed = true;

		this->gunShot.Reset();
		this->gunShotMove.Reset();
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
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		this->destroyed = true;
		this->increment = false;
		--activeTextures;
	}

	if (c2->type == Collider::Type::WALL)
	{
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		this->destroyed = true;
		this->increment = false;
		--activeTextures;
	}

	if (c2->type == Collider::Type::BREAKABLE_BLOCK) {
		//delete colliderH;
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		this->destroyed = true;
		this->increment = false;
		--activeTextures;
		LOG("\n\n\nHARPOON HIT UPPER WALL\n\n\n");
	}

	if (c2->type == Collider::Type::BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		//--activeColliders; --totalColliders;
		this->destroyed = true;
		this->increment = false;
		--activeTextures;
		LOG("\n\n\nHARPOON HIT VERY BIG BALLOON\n\n");
	}

	--activeFx;
}