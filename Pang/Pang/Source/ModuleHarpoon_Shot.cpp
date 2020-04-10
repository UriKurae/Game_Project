#include "ModuleHarpoon_Shot.h"

#include "ModulePlayer.h"
#include"Application.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"


ModuleHarpoon::ModuleHarpoon()
{
	harpoonShot[0].PushBack({ 4, 53, 9, 34 });
	harpoonShot[1].PushBack({ 21, 51, 9, 36 });
	harpoonShot[2].PushBack({ 38, 49, 9, 38 });
	harpoonShot[3].PushBack({ 55, 46, 9, 41 });
	harpoonShot[4].PushBack({ 72, 44, 9, 43 });
	harpoonShot[5].PushBack({ 89, 42, 9, 45 });
	harpoonShot[6].PushBack({ 106, 40, 9, 47 });
	harpoonShot[7].PushBack({ 123, 37, 9, 50 });
	harpoonShot[8].PushBack({ 140, 35, 9, 52 });
	harpoonShot[9].PushBack({ 157, 33, 9, 54 });
	harpoonShot[10].PushBack({ 174, 31, 9, 56 });
	harpoonShot[11].PushBack({ 191, 28, 9, 59 });
	harpoonShot[12].PushBack({ 208, 26, 9, 61 });
	harpoonShot[13].PushBack({ 225, 24, 9, 63 });
	harpoonShot[14].PushBack({ 242, 22, 9, 65 });
	harpoonShot[15].PushBack({ 259, 19, 9, 68 });
	harpoonShot[16].PushBack({ 276, 17, 9, 70 });
	harpoonShot[17].PushBack({ 293, 15, 9, 72 });
	harpoonShot[18].PushBack({ 310, 13, 9, 74 });
	harpoonShot[19].PushBack({ 327, 10, 9, 77 });
	harpoonShot[20].PushBack({ 344, 8, 9, 79 });
	harpoonShot[21].PushBack({ 361, 6, 9, 81 });
	harpoonShot[22].PushBack({ 378, 4, 9, 83 });
	harpoonShot->speed = 0.1f;

}

ModuleHarpoon::~ModuleHarpoon()
{

}

bool ModuleHarpoon::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	texture = App->textures->Load("Assets/Items&Weapons/Harpoon4.png");

	currentAnimation = harpoonShot;
	
	x = App->player->position.x;
	y = App->player->position.y;


	collider = App->collisions->AddCollider({ x, y+10, 9, h }, Collider::Type::PLAYER_SHOT, (Module*)App->harpoon);
	

	return true;
}

update_status ModuleHarpoon::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	

	y -= 1;
	h += 1;
	
	collider->SetH(h);
	collider->SetPos(x, y);

	return ret;
}

update_status ModuleHarpoon::PostUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	if (App->player->destroyed == false)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, x, y, &rect);
	}

	return ret;
}

void OnCollision(Collider* c1, Collider* c2)
{




}