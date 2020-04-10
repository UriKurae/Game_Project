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
	harpoonShot[0].PushBack({ 1, 264, 16, 36 });
	harpoonShot[1].PushBack({ 18, 261, 14, 39 });
	harpoonShot[2].PushBack({ 34, 257, 17, 43 });
	harpoonShot[3].PushBack({ 51, 256, 15, 44 });
	harpoonShot[4].PushBack({ 68, 254, 16, 46 });
	harpoonShot[5].PushBack({ 85, 251, 17, 49 });
	harpoonShot[6].PushBack({ 103, 250, 15, 50 });
	harpoonShot[7].PushBack({ 119, 248, 15, 52 });
	harpoonShot[8].PushBack({ 135, 246, 16, 54 });
	harpoonShot[9].PushBack({ 153, 244, 16, 56 });
	harpoonShot[10].PushBack({ 171, 241, 15, 59 });
	harpoonShot[11].PushBack({ 187, 238, 15, 62 });
	harpoonShot[12].PushBack({ 205, 238, 14, 62 });
	harpoonShot[13].PushBack({ 220, 235, 16, 65 });
	harpoonShot[14].PushBack({ 238, 234, 16, 66 });
	harpoonShot[15].PushBack({ 255, 231, 16, 69 });
	harpoonShot[16].PushBack({ 272, 228, 17, 72 });
	harpoonShot[17].PushBack({ 290, 226, 15, 74 });
	harpoonShot[18].PushBack({ 306, 223, 16, 77 });
	harpoonShot[19].PushBack({ 324, 221, 16, 79 });
	harpoonShot[20].PushBack({ 341, 218, 15, 82 });
	harpoonShot[21].PushBack({ 357, 217, 16, 83 });
	harpoonShot[22].PushBack({ 375, 214, 15, 86 });
	harpoonShot[23].PushBack({ 391, 211, 16, 89 });
	harpoonShot[24].PushBack({ 409, 208, 15, 92 });
	harpoonShot[25].PushBack({ 426, 206, 14, 94 });
	harpoonShot[26].PushBack({ 441, 205, 18, 95 });
	harpoonShot[27].PushBack({ 460, 202, 15, 98 });
	harpoonShot[28].PushBack({ 476, 201, 15, 99 });
	harpoonShot[29].PushBack({ 492, 199, 17, 101 });
	harpoonShot[30].PushBack({ 510, 197, 16, 103 });
	harpoonShot[31].PushBack({ 527, 195, 17, 105 });
	harpoonShot[32].PushBack({ 544, 192, 16, 108 });
	harpoonShot[33].PushBack({ 561, 189, 16, 111 });
	harpoonShot[34].PushBack({ 578, 187, 17, 113 });
	harpoonShot[35].PushBack({ 595, 184, 16, 116 });
	harpoonShot[36].PushBack({ 611, 181, 17, 119 });
	harpoonShot[37].PushBack({ 629, 180, 16, 120 });
	harpoonShot[38].PushBack({ 646, 178, 15, 122 });
	harpoonShot[39].PushBack({ 662, 176, 18, 124 });
	harpoonShot[40].PushBack({ 680, 175, 15, 125 });
	harpoonShot[41].PushBack({ 697, 172, 15, 128 });
	harpoonShot[42].PushBack({ 714, 171, 16, 129 });
	harpoonShot[43].PushBack({ 732, 168, 15, 132 });
	harpoonShot[44].PushBack({ 749, 165, 15, 135 });
	harpoonShot[45].PushBack({ 766, 163, 15, 137 });
	harpoonShot[46].PushBack({ 782, 160, 16, 140 });
	harpoonShot[47].PushBack({ 798, 156, 17, 144 });
	harpoonShot[48].PushBack({ 816, 155, 16, 145 });
	harpoonShot[49].PushBack({ 833, 154, 17, 146 });
	harpoonShot[50].PushBack({ 851, 152, 15, 148 });
	harpoonShot[51].PushBack({ 867, 149, 17, 151 });
	harpoonShot[52].PushBack({ 885, 148, 14, 152 });
	harpoonShot[53].PushBack({ 902, 145, 15, 155 });
	harpoonShot[54].PushBack({ 918, 143, 16, 157 });
	harpoonShot[55].PushBack({ 936, 140, 15, 160 });
	harpoonShot[56].PushBack({ 952, 138, 17, 162 });
	harpoonShot[57].PushBack({ 970, 136, 15, 164 });
	harpoonShot[58].PushBack({ 986, 134, 15, 166 });
	harpoonShot[59].PushBack({ 1003, 131, 17, 169 });
	harpoonShot[60].PushBack({ 1021, 129, 15, 171 });
	harpoonShot[61].PushBack({ 1037, 126, 17, 174 });
	harpoonShot[62].PushBack({ 1054, 124, 15, 176 });
	harpoonShot[63].PushBack({ 1070, 121, 18, 179 });
	harpoonShot[64].PushBack({ 1088, 119, 16, 181 });
	harpoonShot[65].PushBack({ 1105, 117, 16, 183 });
	harpoonShot[66].PushBack({ 1122, 116, 16, 184 });
	harpoonShot[67].PushBack({ 1140, 113, 15, 187 });
	harpoonShot[68].PushBack({ 1157, 111, 15, 189 });
	harpoonShot[69].PushBack({ 1174, 109, 15, 191 });

	harpoonShot->speed = 0.1f;

}

ModuleHarpoon::~ModuleHarpoon()
{

}

bool ModuleHarpoon::Start()
{
	LOG("LOADING HARPOON TEXTURE");

	texture = App->textures->Load("Assets/Items&Weapons/Harpoon.png");

	currentAnimation = &harpoonShot[0];
	
	x = App->player->position.x;
	y = App->player->position.y;


	collider = App->collisions->AddCollider({ x, y+10, 9, h }, Collider::Type::PLAYER_SHOT, (Module*)App->harpoon);
	

	return true;
}

update_status ModuleHarpoon::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < 70; i++) {
		if (i == 0) {
			currentAnimation = &harpoonShot[0];
		}
		if (i != 0) {
			currentAnimation = &harpoonShot[i];
		}
	}

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