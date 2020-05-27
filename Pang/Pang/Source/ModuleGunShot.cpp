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
	shotGun.anim.PushBack({ 155, 11, 12, 8 });
	shotGun.anim.PushBack({ 155, 11, 12, 8 });
	shotGun.anim.PushBack({ 169, 11, 12, 8 });
	shotGun.anim.PushBack({ 169, 11, 12, 8 });
	shotGun.anim.PushBack({ 187, 11, 12, 8 });
	shotGun.anim.PushBack({ 187, 11, 12, 8 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });
	shotGun.anim.PushBack({ 207, 12, 16, 7 });
	shotGun.anim.PushBack({ 231, 10, 14, 9 });

	shotGun.anim.loop = true;
	shotGun.anim.speed = 0.1f;


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

	//texture = App->textures->Load("Assets/Items&Weapons/Mini explosion.png");
	//++totalTextures;

	gunShotFx = App->audio->LoadFx("Assets/Sound/FX/GunShoot.wav");
	++totalFx;

	x = App->player->position.x;
	y = App->player->position.y - speed;

	return true;
}

update_status ModuleGunShot::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;


	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && App->player->destroyed == false)
	{

		App->audio->PlayFx(gunShotFx);
		++activeFx;

		x = App->player->position.x + 10;
		y = App->player->position.y - 2;

		App->particles->AddParticle(gunShotParticle, x - 3, y - 6, Collider::Type::NONE, 0);

		shotGun.speed.y = -2.0f;
		App->particles->AddParticle(shotGun, x - 3, y + 2, Collider::Type::PLAYER_SHOT, 0);
		
	}
		
	return ret;
}

update_status ModuleGunShot::PostUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	//SDL_Rect rect;

	//rect = shotGun.anim.GetCurrentFrame();
	App->render->Blit(texture, shotGun.position.x, shotGun.position.y, &(shotGun.anim.GetCurrentFrame()));

	return ret;
}

void ModuleGunShot::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == Collider::Type::UNBREAKABLE_BLOCK)
	{
		
	}

	if (c2->type == Collider::Type::WALL)
	{
		
	}

	if (c2->type == Collider::Type::BREAKABLE_BLOCK) 
	{
		
	}

	if (c2->type == Collider::Type::BALLOON && c1->type == Collider::Type::PLAYER_SHOT)
	{
		
	}

	--activeFx;
}