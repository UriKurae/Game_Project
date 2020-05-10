#include "ModuleHarpoon_Shot.h"

#include "ModulePlayer.h"
#include"Application.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleScene.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include <SDL\include\SDL_scancode.h>

ModuleHarpoon::ModuleHarpoon(bool startEnabled) : Module(startEnabled)
{
	
}

ModuleHarpoon::~ModuleHarpoon()
{
	if (colliderH != nullptr)
		colliderH->pendingToDelete = true;
}

bool ModuleHarpoon::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	texture = App->textures->Load("Assets/Items&Weapons/HookShot.png");
	++totalTextures;

	HarpoonFx = App->audio->LoadFx("Assets/Sound/FX/NormalShoot.wav");
	++totalFx;

	x = App->player->position.x;
	y = App->player->position.y - speed;



	return true;
}

update_status ModuleHarpoon::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;


	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && destroyed == true && App->player->destroyed == false)
	{

		App->audio->PlayFx(HarpoonFx);
		++activeFx;

		currentAnimation = &harpoonShot;

		h = 34;
		x = App->player->position.x + 10;
		y = App->player->position.y - 2;
		destroyed = false;

		colliderH = App->collisions->AddCollider({ (int)x, (int)y, 9, (int)h }, Collider::Type::PLAYER_SHOT, (Module*)App->harpoon);
		++activeColliders; ++totalColliders;

		App->particles->AddParticle(harpoonShotParticle, x - 3, y - 6, Collider::Type::NONE, 0);
		increment = true;

		++activeTextures;
	}

	if (increment == true) {
		y -= speed;
		h += speed;
		currentAnimation = &harpoonShot;
		colliderH->SetH(h);
		colliderH->SetPos(x, y);
		currentAnimation->Update();
	}
	if (App->player->destroyed == true)
	{
		if (colliderH != nullptr) {
			this->colliderH->pendingToDelete = true;
		}
		increment = false;
		destroyed = true;
		harpoonShot.Reset();

	}
	return ret;
}

update_status ModuleHarpoon::PostUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	if (App->player->destroyed == false && destroyed == false)
	{
		App->render->Blit(texture, x, y, &(harpoonShot.GetCurrentFrame()), 1.0f);
	}

	return ret;
}

void ModuleHarpoon::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::UNBREAKABLE_BLOCK)
	{

	}

	if (c2->type == Collider::Type::BREAKABLE_BLOCK) {
		//delete colliderH;
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		--activeTextures;
		LOG("\n\n\nHARPOON HIT UPPER WALL\n\n\n");
	}

	if (c2->type == Collider::Type::VERY_BIG_BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		//--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		--activeTextures;
		LOG("\n\n\nHARPOON HIT VERY BIG BALLOON\n\n");
	}

	if (c2->type == Collider::Type::BIG_BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		//--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		--activeTextures;
		LOG("\n\n\nHARPOON HIT BIG BALLOON\n\n");
	}

	if (c2->type == Collider::Type::SMALL_BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		//--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		--activeTextures;
	}

	if (c2->type == Collider::Type::VERY_SMALL_BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		//--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		--activeTextures;

	}

	--activeFx;

}