#include "ModuleHarpoon_DoubleShot.h"

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
#include "ModuleTileset.h"
#include "Enemy_Balloon.h"


#include <SDL\include\SDL_scancode.h>

ModuleDoubleShot::ModuleDoubleShot(bool startEnabled) : Module(startEnabled)
{
	harpoon[0].DoubleShot.PushBack({ 4, 266, 9, 34 });
	harpoon[0].DoubleShot.PushBack({ 21, 264, 9, 36 });
	harpoon[0].DoubleShot.PushBack({ 38, 262, 9, 38 });
	harpoon[0].DoubleShot.PushBack({ 55, 259, 9, 41 });
	harpoon[0].DoubleShot.PushBack({ 72, 257, 9, 43 });
	harpoon[0].DoubleShot.PushBack({ 89, 255, 9, 45 });
	harpoon[0].DoubleShot.PushBack({ 106, 253, 9, 47 });
	harpoon[0].DoubleShot.PushBack({ 123, 250, 9, 50 });
	harpoon[0].DoubleShot.PushBack({ 140, 248, 9, 52 });
	harpoon[0].DoubleShot.PushBack({ 157, 246, 9, 54 });
	harpoon[0].DoubleShot.PushBack({ 174, 244, 9, 56 });
	harpoon[0].DoubleShot.PushBack({ 191, 241, 9, 59 });
	harpoon[0].DoubleShot.PushBack({ 208, 239, 9, 61 });
	harpoon[0].DoubleShot.PushBack({ 225, 237, 9, 63 });
	harpoon[0].DoubleShot.PushBack({ 242, 235, 9, 65 });
	harpoon[0].DoubleShot.PushBack({ 259, 232, 9, 68 });
	harpoon[0].DoubleShot.PushBack({ 276, 230, 9, 70 });
	harpoon[0].DoubleShot.PushBack({ 293, 228, 9, 72 });
	harpoon[0].DoubleShot.PushBack({ 310, 226, 9, 74 });
	harpoon[0].DoubleShot.PushBack({ 327, 223, 9, 77 });
	harpoon[0].DoubleShot.PushBack({ 344, 221, 9, 79 });
	harpoon[0].DoubleShot.PushBack({ 361, 219, 9, 81 });
	harpoon[0].DoubleShot.PushBack({ 378, 217, 9, 83 });
	harpoon[0].DoubleShot.PushBack({ 395, 214, 9, 86 });
	harpoon[0].DoubleShot.PushBack({ 412, 212, 9, 88 });
	harpoon[0].DoubleShot.PushBack({ 429, 210, 9, 90 });
	harpoon[0].DoubleShot.PushBack({ 446, 208, 9, 92 });
	harpoon[0].DoubleShot.PushBack({ 463, 205, 9, 95 });
	harpoon[0].DoubleShot.PushBack({ 480, 203, 9, 97 });
	harpoon[0].DoubleShot.PushBack({ 497, 201, 9, 99 });
	harpoon[0].DoubleShot.PushBack({ 514, 199, 9, 101 });
	harpoon[0].DoubleShot.PushBack({ 531, 196, 9, 104 });
	harpoon[0].DoubleShot.PushBack({ 548, 194, 9, 106 });
	harpoon[0].DoubleShot.PushBack({ 565, 192, 9, 108 });
	harpoon[0].DoubleShot.PushBack({ 582, 190, 9, 110 });
	harpoon[0].DoubleShot.PushBack({ 599, 187, 9, 113 });
	harpoon[0].DoubleShot.PushBack({ 614, 185, 9, 115 });
	harpoon[0].DoubleShot.PushBack({ 633, 183, 9, 117 });
	harpoon[0].DoubleShot.PushBack({ 650, 181, 9, 119 });
	harpoon[0].DoubleShot.PushBack({ 667, 178, 9, 122 });
	harpoon[0].DoubleShot.PushBack({ 684, 176, 9, 124 });
	harpoon[0].DoubleShot.PushBack({ 701, 174, 9, 126 });
	harpoon[0].DoubleShot.PushBack({ 718, 172, 9, 128 });
	harpoon[0].DoubleShot.PushBack({ 735, 169, 9, 131 });
	harpoon[0].DoubleShot.PushBack({ 752, 167, 9, 133 });
	harpoon[0].DoubleShot.PushBack({ 769, 165, 9, 135 });
	harpoon[0].DoubleShot.PushBack({ 786, 163, 9, 137 });
	harpoon[0].DoubleShot.PushBack({ 803, 160, 9, 140 });
	harpoon[0].DoubleShot.PushBack({ 820, 158, 9, 142 });
	harpoon[0].DoubleShot.PushBack({ 837, 156, 9, 144 });
	harpoon[0].DoubleShot.PushBack({ 854, 154, 9, 146 });
	harpoon[0].DoubleShot.PushBack({ 871, 151, 9, 149 });
	harpoon[0].DoubleShot.PushBack({ 888, 149, 9, 151 });
	harpoon[0].DoubleShot.PushBack({ 905, 147, 9, 153 });
	harpoon[0].DoubleShot.PushBack({ 922, 145, 9, 155 });
	harpoon[0].DoubleShot.PushBack({ 939, 142, 9, 158 });
	harpoon[0].DoubleShot.PushBack({ 956, 140, 9, 160 });
	harpoon[0].DoubleShot.PushBack({ 973, 138, 9, 162 });
	harpoon[0].DoubleShot.PushBack({ 990, 136, 9, 164 });
	harpoon[0].DoubleShot.PushBack({ 1007, 133, 9, 167 });
	harpoon[0].DoubleShot.PushBack({ 1024, 131, 9, 169 });
	harpoon[0].DoubleShot.PushBack({ 1041, 129, 9, 171 });
	harpoon[0].DoubleShot.PushBack({ 1058, 127, 9, 173 });
	harpoon[0].DoubleShot.PushBack({ 1075, 124, 9, 176 });
	harpoon[0].DoubleShot.PushBack({ 1092, 122, 9, 178 });
	harpoon[0].DoubleShot.PushBack({ 1109, 120, 9, 180 });
	harpoon[0].DoubleShot.PushBack({ 1126, 118, 9, 182 });
	harpoon[0].DoubleShot.PushBack({ 1143, 115, 9, 185 });
	harpoon[0].DoubleShot.PushBack({ 1160, 113, 9, 187 });
	harpoon[0].DoubleShot.PushBack({ 1177, 111, 9, 189 });
	harpoon[0].DoubleShot.loop = false;
	harpoon[0].DoubleShot.speed = 0.9f;

	harpoon[1].DoubleShot.PushBack({ 4, 266, 9, 34 });
	harpoon[1].DoubleShot.PushBack({ 21, 264, 9, 36 });
	harpoon[1].DoubleShot.PushBack({ 38, 262, 9, 38 });
	harpoon[1].DoubleShot.PushBack({ 55, 259, 9, 41 });
	harpoon[1].DoubleShot.PushBack({ 72, 257, 9, 43 });
	harpoon[1].DoubleShot.PushBack({ 89, 255, 9, 45 });
	harpoon[1].DoubleShot.PushBack({ 106, 253, 9, 47 });
	harpoon[1].DoubleShot.PushBack({ 123, 250, 9, 50 });
	harpoon[1].DoubleShot.PushBack({ 140, 248, 9, 52 });
	harpoon[1].DoubleShot.PushBack({ 157, 246, 9, 54 });
	harpoon[1].DoubleShot.PushBack({ 174, 244, 9, 56 });
	harpoon[1].DoubleShot.PushBack({ 191, 241, 9, 59 });
	harpoon[1].DoubleShot.PushBack({ 208, 239, 9, 61 });
	harpoon[1].DoubleShot.PushBack({ 225, 237, 9, 63 });
	harpoon[1].DoubleShot.PushBack({ 242, 235, 9, 65 });
	harpoon[1].DoubleShot.PushBack({ 259, 232, 9, 68 });
	harpoon[1].DoubleShot.PushBack({ 276, 230, 9, 70 });
	harpoon[1].DoubleShot.PushBack({ 293, 228, 9, 72 });
	harpoon[1].DoubleShot.PushBack({ 310, 226, 9, 74 });
	harpoon[1].DoubleShot.PushBack({ 327, 223, 9, 77 });
	harpoon[1].DoubleShot.PushBack({ 344, 221, 9, 79 });
	harpoon[1].DoubleShot.PushBack({ 361, 219, 9, 81 });
	harpoon[1].DoubleShot.PushBack({ 378, 217, 9, 83 });
	harpoon[1].DoubleShot.PushBack({ 395, 214, 9, 86 });
	harpoon[1].DoubleShot.PushBack({ 412, 212, 9, 88 });
	harpoon[1].DoubleShot.PushBack({ 429, 210, 9, 90 });
	harpoon[1].DoubleShot.PushBack({ 446, 208, 9, 92 });
	harpoon[1].DoubleShot.PushBack({ 463, 205, 9, 95 });
	harpoon[1].DoubleShot.PushBack({ 480, 203, 9, 97 });
	harpoon[1].DoubleShot.PushBack({ 497, 201, 9, 99 });
	harpoon[1].DoubleShot.PushBack({ 514, 199, 9, 101 });
	harpoon[1].DoubleShot.PushBack({ 531, 196, 9, 104 });
	harpoon[1].DoubleShot.PushBack({ 548, 194, 9, 106 });
	harpoon[1].DoubleShot.PushBack({ 565, 192, 9, 108 });
	harpoon[1].DoubleShot.PushBack({ 582, 190, 9, 110 });
	harpoon[1].DoubleShot.PushBack({ 599, 187, 9, 113 });
	harpoon[1].DoubleShot.PushBack({ 614, 185, 9, 115 });
	harpoon[1].DoubleShot.PushBack({ 633, 183, 9, 117 });
	harpoon[1].DoubleShot.PushBack({ 650, 181, 9, 119 });
	harpoon[1].DoubleShot.PushBack({ 667, 178, 9, 122 });
	harpoon[1].DoubleShot.PushBack({ 684, 176, 9, 124 });
	harpoon[1].DoubleShot.PushBack({ 701, 174, 9, 126 });
	harpoon[1].DoubleShot.PushBack({ 718, 172, 9, 128 });
	harpoon[1].DoubleShot.PushBack({ 735, 169, 9, 131 });
	harpoon[1].DoubleShot.PushBack({ 752, 167, 9, 133 });
	harpoon[1].DoubleShot.PushBack({ 769, 165, 9, 135 });
	harpoon[1].DoubleShot.PushBack({ 786, 163, 9, 137 });
	harpoon[1].DoubleShot.PushBack({ 803, 160, 9, 140 });
	harpoon[1].DoubleShot.PushBack({ 820, 158, 9, 142 });
	harpoon[1].DoubleShot.PushBack({ 837, 156, 9, 144 });
	harpoon[1].DoubleShot.PushBack({ 854, 154, 9, 146 });
	harpoon[1].DoubleShot.PushBack({ 871, 151, 9, 149 });
	harpoon[1].DoubleShot.PushBack({ 888, 149, 9, 151 });
	harpoon[1].DoubleShot.PushBack({ 905, 147, 9, 153 });
	harpoon[1].DoubleShot.PushBack({ 922, 145, 9, 155 });
	harpoon[1].DoubleShot.PushBack({ 939, 142, 9, 158 });
	harpoon[1].DoubleShot.PushBack({ 956, 140, 9, 160 });
	harpoon[1].DoubleShot.PushBack({ 973, 138, 9, 162 });
	harpoon[1].DoubleShot.PushBack({ 990, 136, 9, 164 });
	harpoon[1].DoubleShot.PushBack({ 1007, 133, 9, 167 });
	harpoon[1].DoubleShot.PushBack({ 1024, 131, 9, 169 });
	harpoon[1].DoubleShot.PushBack({ 1041, 129, 9, 171 });
	harpoon[1].DoubleShot.PushBack({ 1058, 127, 9, 173 });
	harpoon[1].DoubleShot.PushBack({ 1075, 124, 9, 176 });
	harpoon[1].DoubleShot.PushBack({ 1092, 122, 9, 178 });
	harpoon[1].DoubleShot.PushBack({ 1109, 120, 9, 180 });
	harpoon[1].DoubleShot.PushBack({ 1126, 118, 9, 182 });
	harpoon[1].DoubleShot.PushBack({ 1143, 115, 9, 185 });
	harpoon[1].DoubleShot.PushBack({ 1160, 113, 9, 187 });
	harpoon[1].DoubleShot.PushBack({ 1177, 111, 9, 189 });
	harpoon[1].DoubleShot.loop = false;
	harpoon[1].DoubleShot.speed = 0.9f;

	harpoonShotParticle.anim.PushBack({ 62, 13, 16, 6 });
	harpoonShotParticle.anim.PushBack({ 76, 8, 16, 11 });
	harpoonShotParticle.anim.PushBack({ 95, 9, 16, 10 });
	harpoonShotParticle.anim.PushBack({ 119, 5, 16, 14 });
	harpoonShotParticle.anim.loop = false;
	harpoonShotParticle.anim.speed = 0.3f;
}

ModuleDoubleShot::~ModuleDoubleShot()
{

}

bool ModuleDoubleShot::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	texture = App->textures->Load("Assets/Items&Weapons/Harpoon.png");
	++totalTextures;

	HarpoonFx = App->audio->LoadFx("Assets/Sound/FX/NormalShoot.wav");
	++totalFx;

	x = App->player->position.x;
	y = App->player->position.y - speed;



	return true;
}

update_status ModuleDoubleShot::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;


	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->player->destroyed == false && shotsOnScreen < 3 && App->player->currWeapon == 3)
	{

		App->audio->PlayFx(HarpoonFx);
		++activeFx;

		x = App->player->position.x + 10;
		y = App->player->position.y - 2;

		for (uint i = 0; i < SHOTS; i++)
		{
			if (harpoon[i].colliderH == nullptr)
			{
				harpoon[i].h = 34;
				harpoon[i].x = App->player->position.x + 10;
				harpoon[i].y = App->player->position.y - 2;
				harpoon[i].colliderH = App->collisions->AddCollider({ (int)harpoon[i].x, (int)harpoon[i].y, 9, (int)harpoon[i].h }, Collider::Type::PLAYER_SHOT, (Module*)App->doubleShot);
				++activeColliders; ++totalColliders;
				harpoon[i].increment = true;
				harpoon[i].destroyed = false;

				break;
			}
		}

		shotsOnScreen++;
		

		App->particles->AddParticle(harpoonShotParticle, x - 3, y - 6, Collider::Type::NONE, 0);
		++activeTextures;
	}

	for (uint i = 0; i < SHOTS; i++)
	{
		if (harpoon[i].increment == true) {
			harpoon[i].y -= speed;
			harpoon[i].h += speed;
			harpoon[i].colliderH->SetH(harpoon[i].h);
			harpoon[i].colliderH->SetPos(harpoon[i].x, harpoon[i].y);
			harpoon[i].DoubleShot.Update();
		}
	}
	
	if (App->player->destroyed == true)
	{
		for (uint i = 0; i < SHOTS; i++)
		{
			if (harpoon[i].colliderH != nullptr) {
				harpoon[i].colliderH->pendingToDelete = true;
			}
			harpoon[i].increment = false;
			harpoon[i].destroyed = true;
			harpoon[i].DoubleShot.Reset();
		}
	}
	return ret;
}

update_status ModuleDoubleShot::PostUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (uint i = 0; i < SHOTS; i++)
	{
		if (App->player->destroyed == false && harpoon[i].destroyed == false)
		{
			App->render->Blit(texture, harpoon[i].x, harpoon[i].y, &(harpoon[i].DoubleShot.GetCurrentFrame()), 1.0f);
		}
	}

	return ret;
}

void ModuleDoubleShot::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::WALL)
	{
		for (uint i = 0; i < SHOTS; i++)
		{
			if (c1 == harpoon[i].colliderH)
			{
				harpoon[i].colliderH->pendingToDelete = true;
				harpoon[i].colliderH = nullptr;
				harpoon[i].destroyed = true;
				harpoon[i].increment = false;
				harpoon[i].DoubleShot.Reset();
				--activeTextures;
				break;
			}
		}

		shotsOnScreen--;
	}

	if (c2->type == Collider::Type::BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		for (uint i = 0; i < SHOTS; i++)
		{
			if (c1 == harpoon[i].colliderH)
			{
				harpoon[i].colliderH->pendingToDelete = true;
				harpoon[i].colliderH = nullptr;
				harpoon[i].destroyed = true;
				harpoon[i].increment = false;
				harpoon[i].DoubleShot.Reset();
				--activeTextures;
				break;
			}
		}

		shotsOnScreen--;
	}


	if (c2->type == Collider::Type::BREAKABLE_BLOCK)
	{
		if (c1->Intersects(App->scene2->leftPlatform->rect))
		{
			for (uint i = 0; i < SHOTS; i++)
			{
				if (c1 == harpoon[i].colliderH)
				{
					harpoon[i].colliderH->pendingToDelete = true;
					harpoon[i].colliderH = nullptr;
					harpoon[i].destroyed = true;
					harpoon[i].increment = false;
					harpoon[i].DoubleShot.Reset();
					--activeTextures;
					break;
				}
			}

			App->scene2->leftPlatform->pendingToDelete = true;
			App->scene2->currentAnim = &App->scene2->blockDestroy;
			App->scene2->destroyedBlockLeft = true;

			shotsOnScreen--;
		}
		if (c1->Intersects(App->scene2->rightPlatform->rect))
		{
			for (uint i = 0; i < SHOTS; i++)
			{
				if (c1 == harpoon[i].colliderH)
				{
					harpoon[i].colliderH->pendingToDelete = true;
					harpoon[i].colliderH = nullptr;
					harpoon[i].destroyed = true;
					harpoon[i].increment = false;
					harpoon[i].DoubleShot.Reset();
					--activeTextures;
					break;
				}
			}

			App->scene2->rightPlatform->pendingToDelete = true;
			App->scene2->currentAnim = &App->scene2->blockDestroy;
			App->scene2->destroyedBlockRight = true;

			shotsOnScreen--;
		}
	}

	if (c2->type == Collider::Type::UNBREAKABLE_BLOCK && c1->type == Collider::Type::PLAYER_SHOT)
	{
		for (uint i = 0; i < SHOTS; i++)
		{
			if (c1 == harpoon[i].colliderH)
			{
				harpoon[i].colliderH->pendingToDelete = true;
				harpoon[i].colliderH = nullptr;
				harpoon[i].destroyed = true;
				harpoon[i].increment = false;
				harpoon[i].DoubleShot.Reset();
				--activeTextures;
				break;
			}
		}

		shotsOnScreen--;
	}

	--activeFx;

}

bool ModuleDoubleShot::CleanUp()
{

	App->textures->Unload(texture);
	totalTextures--;
	activeTextures = 0;
	App->audio->UnloadFx(HarpoonFx);

	for (uint i = 0; i < SHOTS; i++)
	{
		if (harpoon[i].destroyed == true)
		{

			if (!harpoon[i].destroyed)
			{
				App->collisions->RemoveCollider(harpoon[i].colliderH);
				totalColliders--;
				activeColliders = 0;
			}

		}
	}

	return true;
}