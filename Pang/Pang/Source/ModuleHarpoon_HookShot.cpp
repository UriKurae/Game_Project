#include "ModuleHarpoon_HookShot.h"

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

ModuleHookShot::ModuleHookShot(bool startEnabled) : Module(startEnabled)
{
	hookShot.PushBack({ 0, 155, 9, 36 });
	hookShot.PushBack({ 11, 153, 9, 38 });
	hookShot.PushBack({ 22, 150, 9, 41 });
	hookShot.PushBack({ 33, 148, 9, 43 });
	hookShot.PushBack({ 44, 146, 9, 45 });
	hookShot.PushBack({ 55, 144, 9, 47 });
	hookShot.PushBack({ 66, 141, 9, 50 });
	hookShot.PushBack({ 77, 139, 9, 52 });
	hookShot.PushBack({ 88, 137, 9, 54 });
	hookShot.PushBack({ 99, 135, 9, 56 });
	hookShot.PushBack({ 110, 132, 9, 59 });
	hookShot.PushBack({ 121, 130, 9, 61 });
	hookShot.PushBack({ 132, 128, 9, 63 });
	hookShot.PushBack({ 143, 126, 9, 65 });
	hookShot.PushBack({ 154, 123, 9, 68 });
	hookShot.PushBack({ 165, 121, 9, 70 });
	hookShot.PushBack({ 176, 119, 9, 72 });
	hookShot.PushBack({ 187, 117, 9, 74 });
	hookShot.PushBack({ 198, 114, 9, 77 });
	hookShot.PushBack({ 209, 112, 9, 79 });
	hookShot.PushBack({ 220, 110, 9, 81 });
	hookShot.PushBack({ 231, 108, 9, 81 });
	hookShot.PushBack({ 242, 105, 9, 86 });
	hookShot.PushBack({ 252, 101, 9, 88 });
	hookShot.PushBack({ 264, 101, 9, 90 });
	hookShot.PushBack({ 275, 99, 9, 92 });
	hookShot.PushBack({ 286, 96, 9, 95 });
	hookShot.PushBack({ 297, 94, 9, 97 });
	hookShot.PushBack({ 308, 92, 9, 99 });
	hookShot.PushBack({ 319, 90, 9, 101 });
	hookShot.PushBack({ 330, 87, 9, 104 });
	hookShot.PushBack({ 341, 85, 9, 106 });
	hookShot.PushBack({ 352, 83, 9, 108 });
	hookShot.PushBack({ 363, 81, 9, 110 });
	hookShot.PushBack({ 374, 78, 9, 113 });
	hookShot.PushBack({ 385, 76, 9, 115 });
	hookShot.PushBack({ 396, 75, 9, 116 });
	hookShot.PushBack({ 407, 73, 9, 118 });
	hookShot.PushBack({ 418, 70, 9, 121 });
	hookShot.PushBack({ 429, 68, 9, 123 });
	hookShot.PushBack({ 440, 66, 9, 125 });
	hookShot.PushBack({ 451, 64, 9, 127 });
	hookShot.PushBack({ 462, 61, 9, 130 });
	hookShot.PushBack({ 473, 59, 9, 132 });
	hookShot.PushBack({ 484, 57, 9, 134 });
	hookShot.PushBack({ 495, 55, 9, 136 });
	hookShot.PushBack({ 506, 52, 9, 139 });
	hookShot.PushBack({ 517, 50, 9, 141 });
	hookShot.PushBack({ 528, 48, 9, 143 });
	hookShot.PushBack({ 539, 46, 9, 145 });
	hookShot.PushBack({ 550, 43, 9, 148 });
	hookShot.PushBack({ 561, 41, 9, 150 });
	hookShot.PushBack({ 572, 39, 9, 152 });
	hookShot.PushBack({ 583, 37, 9, 154 });
	hookShot.PushBack({ 594, 34, 9, 157 });
	hookShot.PushBack({ 605, 32, 9, 159 });
	hookShot.PushBack({ 616, 30, 9, 161 });
	hookShot.PushBack({ 627, 28, 9, 163 });
	hookShot.PushBack({ 638, 25, 9, 166 });
	hookShot.PushBack({ 649, 23, 9, 168 });
	hookShot.PushBack({ 660, 21, 9, 170 });
	hookShot.PushBack({ 671, 19, 9, 172 });
	hookShot.PushBack({ 682, 16, 9, 175 });
	hookShot.PushBack({ 693, 15, 9, 176 });
	hookShot.PushBack({ 704, 12, 9, 179 });
	hookShot.PushBack({ 715, 10, 9, 181 });
	hookShot.PushBack({ 726, 7, 9, 184 });
	hookShot.PushBack({ 737, 5, 9, 186 });
	hookShot.PushBack({ 748, 3, 9, 188 });
	hookShot.loop = false;
	hookShot.speed = 0.9f;

	idleHookShot.PushBack({ 759, 1, 9, 190 });
	idleHookShot.PushBack({ 770, 0, 9, 191 });
	idleHookShot.PushBack({ 781, 0, 9, 191 });
	idleHookShot.loop = false;
	idleHookShot.speed = 0.009f;

	hookShotParticle.anim.PushBack({ 62, 13, 16, 6 });
	hookShotParticle.anim.PushBack({ 76, 8, 16, 11 });
	hookShotParticle.anim.PushBack({ 95, 9, 16, 10 });
	hookShotParticle.anim.PushBack({ 119, 5, 16, 14 });
	hookShotParticle.anim.loop = false;
	hookShotParticle.anim.speed = 0.3f;
}

ModuleHookShot::~ModuleHookShot()
{
	if (colliderH != nullptr)
		colliderH->pendingToDelete = true;
}

bool ModuleHookShot::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	texture = App->textures->Load("Assets/Items&Weapons/HookShot.png");
	++totalTextures;

	HarpoonFx = App->audio->LoadFx("Assets/Sound/FX/NormalShoot.wav");
	++totalFx;

	x = App->player->position.x;
	y = App->player->position.y - speed;

	time = 5;
	count = 0;

	return true;
}

update_status ModuleHookShot::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;


	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && destroyed == true && App->player->destroyed == false && App->player->currWeapon == 1)
	{

		App->audio->PlayFx(HarpoonFx);
		++activeFx;

		currentAnimation = &hookShot;

		h = 34;
		x = App->player->position.x + 10;
		y = App->player->position.y - 2;
		destroyed = false;

		colliderH = App->collisions->AddCollider({ (int)x, (int)y, 9, (int)h }, Collider::Type::PLAYER_SHOT, (Module*)App->hookShot);
		++activeColliders; ++totalColliders;

		App->particles->AddParticle(hookShotParticle, x - 3, y - 6, Collider::Type::NONE, 0);
		increment = true;

		++activeTextures;
	}

	if (increment == true) {
		y -= speed;
		h += speed;
		currentAnimation = &hookShot;
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
		
		hookShot.Reset();
		idleHookShot.Reset();
	}

	if (time == 0)
	{
		if (colliderH != nullptr) {
			this->colliderH->pendingToDelete = true;
		}
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		hookShot.Reset();
		idleHookShot.Reset();
		time = 5;
		count = 0;
		--activeTextures;
	}

	return ret;
}

update_status ModuleHookShot::PostUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	if (App->player->destroyed == false && destroyed == false)
	{
		App->render->Blit(texture, x, y, &(currentAnimation->GetCurrentFrame()), 1.0f);
	}

	return ret;
}

void ModuleHookShot::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::UNBREAKABLE_BLOCK)
	{
		increment = false;
		currentAnimation = &idleHookShot;
		hookShot.Reset();
		currentAnimation->Update();
		count++;
		if (count % 60 == 0 && time > 0 && App->enemies->balloon.balloonsOnScene > 0 && destroyed == false) {
			time--;
		}
		y = 8;
	}

	if (c2->type == Collider::Type::WALL)
	{
		increment = false;
		currentAnimation = &idleHookShot;
		hookShot.Reset();
		currentAnimation->Update();
		count++;
		if (count % 60 == 0 && time > 0 && App->enemies->balloon.balloonsOnScene > 0 && destroyed == false) {
			time--;
		}
		y = 8;
	}

	if (c2->type == Collider::Type::BREAKABLE_BLOCK) 
	{
		
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		hookShot.Reset();
		idleHookShot.Reset();
		time = 5;
		count = 0;
		--activeTextures;
		LOG("\n\n\nHARPOON HIT UPPER WALL\n\n\n");
	}

	if (c2->type == Collider::Type::BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		hookShot.Reset();
		idleHookShot.Reset();
		time = 5;
		count = 0;
		--activeTextures;
		LOG("\n\n\nHARPOON HIT VERY BIG BALLOON\n\n");
	}

	--activeFx;
}

bool ModuleHookShot::CleanUp()
{
	if (destroyed == true)
	{
		App->textures->Unload(texture);
		totalTextures--;
		activeTextures = 0;
		App->audio->UnloadFx(HarpoonFx);

		if (!destroyed)
		{

			App->collisions->RemoveCollider(colliderH);
			totalColliders--;
			activeColliders = 0;
		}

	}

	return true;
}