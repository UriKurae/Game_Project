#include "ModuleHarpoon_Shot.h"

#include "ModulePlayer.h"
#include"Application.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleScene.h"


ModuleHarpoon::ModuleHarpoon()
{
	harpoonShot.PushBack({ 1, 264, 16, 36 });
	harpoonShot.PushBack({ 18, 261, 14, 39 });
	harpoonShot.PushBack({ 34, 257, 17, 43 });
	harpoonShot.PushBack({ 51, 256, 15, 44 });
	harpoonShot.PushBack({ 68, 254, 16, 46 });
	harpoonShot.PushBack({ 85, 251, 17, 49 });
	harpoonShot.PushBack({ 103, 250, 15, 50 });
	harpoonShot.PushBack({ 119, 248, 15, 52 });
	harpoonShot.PushBack({ 135, 246, 16, 54 });
	harpoonShot.PushBack({ 153, 244, 16, 56 });
	harpoonShot.PushBack({ 171, 241, 15, 59 });
	harpoonShot.PushBack({ 187, 238, 15, 62 });
	harpoonShot.PushBack({ 205, 238, 14, 62 });
	harpoonShot.PushBack({ 220, 235, 16, 65 });
	harpoonShot.PushBack({ 238, 234, 16, 66 });
	harpoonShot.PushBack({ 255, 231, 16, 69 });
	harpoonShot.PushBack({ 272, 228, 17, 72 });
	harpoonShot.PushBack({ 290, 226, 15, 74 });
	harpoonShot.PushBack({ 306, 223, 16, 77 });
	harpoonShot.PushBack({ 324, 221, 16, 79 });
	harpoonShot.PushBack({ 341, 218, 15, 82 });
	harpoonShot.PushBack({ 357, 217, 16, 83 });
	harpoonShot.PushBack({ 375, 214, 15, 86 });
	harpoonShot.PushBack({ 391, 211, 16, 89 });
	harpoonShot.PushBack({ 409, 208, 15, 92 });
	harpoonShot.PushBack({ 426, 206, 14, 94 });
	harpoonShot.PushBack({ 441, 205, 18, 95 });
	harpoonShot.PushBack({ 460, 202, 15, 98 });
	harpoonShot.PushBack({ 476, 201, 15, 99 });
	harpoonShot.PushBack({ 492, 199, 17, 101 });
	harpoonShot.PushBack({ 510, 197, 16, 103 });
	harpoonShot.PushBack({ 527, 195, 17, 105 });
	harpoonShot.PushBack({ 544, 192, 16, 108 });
	harpoonShot.PushBack({ 561, 189, 16, 111 });
	harpoonShot.PushBack({ 578, 187, 17, 113 });
	harpoonShot.PushBack({ 595, 184, 16, 116 });
	harpoonShot.PushBack({ 611, 181, 17, 119 });
	harpoonShot.PushBack({ 629, 180, 16, 120 });
	harpoonShot.PushBack({ 646, 178, 15, 122 });
	harpoonShot.PushBack({ 662, 176, 18, 124 });
	harpoonShot.PushBack({ 680, 175, 15, 125 });
	harpoonShot.PushBack({ 697, 172, 15, 128 });
	harpoonShot.PushBack({ 714, 171, 16, 129 });
	harpoonShot.PushBack({ 732, 168, 15, 132 });
	harpoonShot.PushBack({ 749, 165, 15, 135 });
	harpoonShot.PushBack({ 766, 163, 15, 137 });
	harpoonShot.PushBack({ 782, 160, 16, 140 });
	harpoonShot.PushBack({ 798, 156, 17, 144 });
	harpoonShot.PushBack({ 816, 155, 16, 145 });
	harpoonShot.PushBack({ 833, 154, 17, 146 });
	harpoonShot.PushBack({ 851, 152, 15, 148 });
	harpoonShot.PushBack({ 867, 149, 17, 151 });
	harpoonShot.PushBack({ 885, 148, 14, 152 });
	harpoonShot.PushBack({ 902, 145, 15, 155 });
	harpoonShot.PushBack({ 918, 143, 16, 157 });
	harpoonShot.PushBack({ 936, 140, 15, 160 });
	harpoonShot.PushBack({ 952, 138, 17, 162 });
	harpoonShot.PushBack({ 970, 136, 15, 164 });
	harpoonShot.PushBack({ 986, 134, 15, 166 });
	harpoonShot.PushBack({ 1003, 131, 17, 169 });
	harpoonShot.PushBack({ 1021, 129, 15, 171 });
	harpoonShot.PushBack({ 1037, 126, 17, 174 });
	harpoonShot.PushBack({ 1054, 124, 15, 176 });
	harpoonShot.PushBack({ 1070, 121, 18, 179 });
	harpoonShot.PushBack({ 1088, 119, 16, 181 });
	harpoonShot.PushBack({ 1105, 117, 16, 183 });
	harpoonShot.PushBack({ 1122, 116, 16, 184 });
	harpoonShot.PushBack({ 1140, 113, 15, 187 });
	harpoonShot.PushBack({ 1157, 111, 15, 189 });
	harpoonShot.PushBack({ 1174, 109, 15, 191 });

	harpoonShot.speed = 0.1f;

}

ModuleHarpoon::~ModuleHarpoon()
{

}

bool ModuleHarpoon::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	texture = App->textures->Load("Assets/Items&Weapons/Harpoon.png");
	
	x = App->player->position.x;
	y = App->player->position.y - 3;


	collider = App->collisions->AddCollider({ x, y, 9, h }, Collider::Type::PLAYER_SHOT, (Module*)App->harpoon);
	

	return true;
}

update_status ModuleHarpoon::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	y -= 1;
	h += 1;

	collider->SetH(h);
	collider->SetPos(x, y);

	harpoonShot.Update();

	return ret;
}

update_status ModuleHarpoon::PostUpdate()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	if (App->player->destroyed == false)
	{
		/*SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, x, y, &rect);*/
		App->render->Blit(texture, x, y, &(harpoonShot.GetCurrentFrame()), 0.5f);
	}

	if (destroyed == true) {

	}

	return ret;
}

void ModuleHarpoon::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider) {
		if (c2 == App->scene->upperWall) {
			destroyed = true;
		}
	}



}