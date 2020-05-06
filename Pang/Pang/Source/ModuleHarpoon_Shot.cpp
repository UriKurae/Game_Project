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
	name = "HARPOON";

	harpoonShot.PushBack({ 4, 266, 9, 34 });
	harpoonShot.PushBack({ 21, 264, 9, 36 });
	harpoonShot.PushBack({ 38, 262, 9, 38 });
	harpoonShot.PushBack({ 55, 259, 9, 41 });
	harpoonShot.PushBack({ 72, 257, 9, 43 });
	harpoonShot.PushBack({ 89, 255, 9, 45 });
	harpoonShot.PushBack({ 106, 253, 9, 47 });
	harpoonShot.PushBack({ 123, 250, 9, 50 });
	harpoonShot.PushBack({ 140, 248, 9, 52 });
	harpoonShot.PushBack({ 157, 246, 9, 54 });
	harpoonShot.PushBack({ 174, 244, 9, 56 });
	harpoonShot.PushBack({ 191, 241, 9, 59 });
	harpoonShot.PushBack({ 208, 239, 9, 61 });
	harpoonShot.PushBack({ 225, 237, 9, 63 });
	harpoonShot.PushBack({ 242, 235, 9, 65 });
	harpoonShot.PushBack({ 259, 232, 9, 68 });
	harpoonShot.PushBack({ 276, 230, 9, 70 });
	harpoonShot.PushBack({ 293, 228, 9, 72 });
	harpoonShot.PushBack({ 310, 226, 9, 74 });
	harpoonShot.PushBack({ 327, 223, 9, 77 });
	harpoonShot.PushBack({ 344, 221, 9, 79 });
	harpoonShot.PushBack({ 361, 219, 9, 81 });
	harpoonShot.PushBack({ 378, 217, 9, 83 });
	harpoonShot.PushBack({ 395, 214, 9, 86 });
	harpoonShot.PushBack({ 412, 212, 9, 88 });
	harpoonShot.PushBack({ 429, 210, 9, 90 });
	harpoonShot.PushBack({ 446, 208, 9, 92 });
	harpoonShot.PushBack({ 463, 205, 9, 95 });
	harpoonShot.PushBack({ 480, 203, 9, 97 });
	harpoonShot.PushBack({ 497, 201, 9, 99 });
	harpoonShot.PushBack({ 514, 199, 9, 101 });
	harpoonShot.PushBack({ 531, 196, 9, 104 });
	harpoonShot.PushBack({ 548, 194, 9, 106 });
	harpoonShot.PushBack({ 565, 192, 9, 108 });
	harpoonShot.PushBack({ 582, 190, 9, 110 });
	harpoonShot.PushBack({ 599, 187, 9, 113 });
	harpoonShot.PushBack({ 614, 185, 9, 115 });
	harpoonShot.PushBack({ 633, 183, 9, 117 });
	harpoonShot.PushBack({ 650, 181, 9, 119 });
	harpoonShot.PushBack({ 667, 178, 9, 122 });
	harpoonShot.PushBack({ 684, 176, 9, 124 });
	harpoonShot.PushBack({ 701, 174, 9, 126 });
	harpoonShot.PushBack({ 718, 172, 9, 128 });
	harpoonShot.PushBack({ 735, 169, 9, 131 });
	harpoonShot.PushBack({ 752, 167, 9, 133 });
	harpoonShot.PushBack({ 769, 165, 9, 135 });
	harpoonShot.PushBack({ 786, 163, 9, 137 });
	harpoonShot.PushBack({ 803, 160, 9, 140 });
	harpoonShot.PushBack({ 820, 158, 9, 142 });
	harpoonShot.PushBack({ 837, 156, 9, 144 });
	harpoonShot.PushBack({ 854, 154, 9, 146 });
	harpoonShot.PushBack({ 871, 151, 9, 149 });
	harpoonShot.PushBack({ 888, 149, 9, 151 });
	harpoonShot.PushBack({ 905, 147, 9, 153 });
	harpoonShot.PushBack({ 922, 145, 9, 155 });
	harpoonShot.PushBack({ 939, 142, 9, 158 });
	harpoonShot.PushBack({ 956, 140, 9, 160 });
	harpoonShot.PushBack({ 973, 138, 9, 162 });
	harpoonShot.PushBack({ 990, 136, 9, 164 });
	harpoonShot.PushBack({ 1007, 133, 9, 167 });
	harpoonShot.PushBack({ 1024, 131, 9, 169 });
	harpoonShot.PushBack({ 1041, 129, 9, 171 });
	harpoonShot.PushBack({ 1058, 127, 9, 173 });
	harpoonShot.PushBack({ 1075, 124, 9, 176 });
	harpoonShot.PushBack({ 1092, 122, 9, 178 });
	harpoonShot.PushBack({ 1109, 120, 9, 180 });
	harpoonShot.PushBack({ 1126, 118, 9, 182 });
	harpoonShot.PushBack({ 1143, 115, 9, 185 });
	harpoonShot.PushBack({ 1160, 113, 9, 187 });
	harpoonShot.PushBack({ 1177, 111, 9, 189 });
	harpoonShot.loop = false;
	harpoonShot.speed = 0.9f;

	harpoonShotParticle.anim.PushBack({ 62, 13, 16, 6 });
	harpoonShotParticle.anim.PushBack({ 76, 8, 16, 11 });
	harpoonShotParticle.anim.PushBack({ 95, 9, 16, 10 });
	harpoonShotParticle.anim.PushBack({ 119, 5, 16, 14 });
	harpoonShotParticle.anim.loop = false;
	harpoonShotParticle.anim.speed = 0.3f;


}

ModuleHarpoon::~ModuleHarpoon()
{
	if (colliderH != nullptr)
		colliderH->pendingToDelete = true;
}

bool ModuleHarpoon::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	texture = App->textures->Load("Assets/Items&Weapons/Harpoon.png");
	++activeTextures; ++totalTextures;
	HarpoonFx = App->audio->LoadFx("Assets/Sound/FX/NormalShoot.wav");
	++activeFx; ++totalFx;

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
		currentAnimation = &harpoonShot;
		h = 34;
		x = App->player->position.x + 10;
		y = App->player->position.y - 2;
		destroyed = false;
		colliderH = App->collisions->AddCollider({ (int)x, (int)y, 9, (int)h }, Collider::Type::PLAYER_SHOT, (Module*)App->harpoon);
		++activeColliders; ++totalColliders;
		App->particles->AddParticle(harpoonShotParticle, x - 3, y - 6, Collider::Type::NONE, 0);
		increment = true;
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
	if (c2->type == Collider::Type::WALL) {
		//delete colliderH;
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		LOG("\n\n\nHARPOON HIT UPPER WALL\n\n\n");
	}

	if (c2->type == Collider::Type::VERY_BIG_BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		LOG("\n\n\nHARPOON HIT VERY BIG BALLOON\n\n");
	}

	if (c2->type == Collider::Type::BIG_BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
		LOG("\n\n\nHARPOON HIT BIG BALLOON\n\n");
	}

	if (c2->type == Collider::Type::SMALL_BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
	}

	if (c2->type == Collider::Type::VERY_SMALL_BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		this->colliderH->pendingToDelete = true;
		--activeColliders; --totalColliders;
		destroyed = true;
		increment = false;
		currentAnimation->Reset();
	}

}