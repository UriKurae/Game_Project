#pragma once

#include "ModuleScene2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "Enemy_Balloon.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleHarpoon_Shot.h"
#include "ModuleHarpoon_HookShot.h"
#include "ModuleGunShot.h"
#include "ModuleHarpoon_DoubleShot.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"
#include "IntroScene.h"
#include "ModuleHarpoon_HookShot.h"
#include "ModuleTileset.h"
#include "ModuleBoosters.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{
	name = "LEVEL 2";

	blockDestroyLeft.PushBack({ 88, 158, 32, 8 });
	blockDestroyLeft.PushBack({ 122, 158, 32, 8 });
	blockDestroyLeft.PushBack({ 156, 158, 32, 8 });
	blockDestroyLeft.PushBack({ 123, 142, 32, 8 });
	blockDestroyLeft.speed = 0.1f;
	blockDestroyLeft.loop = false;

	blockDestroyRight.PushBack({ 88, 158, 32, 8 });
	blockDestroyRight.PushBack({ 122, 158, 32, 8 });
	blockDestroyRight.PushBack({ 156, 158, 32, 8 });
	blockDestroyRight.PushBack({ 123, 142, 32, 8 });
	blockDestroyRight.speed = 0.1f;
	blockDestroyRight.loop = false;
}

ModuleScene2::~ModuleScene2()
{

	
}

bool ModuleScene2::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	destroyedBlockLeft = false;
	destroyedBlockRight = false;

	countDownToFade = 300;

	fgTexture = App->textures->Load("Assets/Items&Weapons/BlockSprites.png"); //fg on 2st Level is invisible
	++activeTextures; ++totalTextures;

	block.PushBack({8, 158, 32, 8});

	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Fuji(Sunset).png");
	++activeTextures; ++totalTextures;

	deathTexture1 = App->textures->Load("Assets/Foregrounds/Foreground_Death_1.png");
	++activeTextures; ++totalTextures;

	deathTexture2 = App->textures->Load("Assets/Foregrounds/Foreground_Death_2.png");
	++activeTextures; ++totalTextures;

	App->audio->PlayMusic("Assets/Sound/Soundtracks/MtFuji.ogg", 0.0f);

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->tileset->Enable();
	App->boosters->Enable();

	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 119, 20);

	App->player->uiIndex = 0;

	App->player->scene1 = false;
	App->player->scene2 = true;
	App->player->scene3 = false;
	App->player->scene4 = false;
	App->player->scene5 = false;
	App->player->scene6 = false;

	musicBool1 = true;
	musicBool2 = true;

	return ret; 
}

update_status ModuleScene2::Update()
{
	if (App->input->keys[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN)
	{
		App->enemies->balloon.balloonsOnScene = 0;
		App->collisions->RemoveCollider(leftWall);
		App->collisions->RemoveCollider(rightWall);
		App->collisions->RemoveCollider(upperWall);
		App->collisions->RemoveCollider(lowerWall);
		--activeColliders; --totalColliders;
		--activeColliders; --totalColliders;
		--activeColliders; --totalColliders;
		--activeColliders; --totalColliders;
	}


	if (App->enemies->balloon.balloonsOnScene == 0)
	{
		App->fade->FadeToBlack((Module*)App->scene2, (Module*)App->winScene, 60);
	}

	if (App->player->time == 50 && musicBool1 == true) {
		musicBool1 = false;
		App->audio->PlayMusic("Assets/Sound/Soundtracks/GettingLate.ogg", 0.0f);
	}

	if (App->player->time == 20 && musicBool2 == true) {
		musicBool2 = false;
		App->audio->PlayMusic("Assets/Sound/Soundtracks/OutOfTime!.ogg", 0.0f);
	}

	blockDestroyLeft.Update();
	blockDestroyRight.Update();

	return update_status::UPDATE_CONTINUE; 
}

update_status ModuleScene2::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);
	if (destroyedBlockLeft == false) 
	{
		App->render->Blit(fgTexture, 160, 80, &(block.GetCurrentFrame()), 1.0f);
		blockDestroyLeft.Reset();
	}
	else {
		App->render->Blit(fgTexture, 160, 80, &(blockDestroyLeft.GetCurrentFrame()), 1.0f);
	}
	
	if (destroyedBlockRight == false)
	{
		App->render->Blit(fgTexture, 192, 80, &(block.GetCurrentFrame()), 1.0f);
		blockDestroyRight.Reset();
	}
	else {
		App->render->Blit(fgTexture, 192, 80, &(blockDestroyRight.GetCurrentFrame()), 1.0f);
	}
	
	if (App->player->lifes == 0) {
		App->render->Blit(App->player->gameOverTexture, 150, 99, NULL);
	}

	
	//This could be more clean 
	//Animation to stop the scene with the death 

	if (App->player->destroyed || App->player->time == 0)
	{
		countDownToFade--;
	}
	if (countDownToFade > 220 && countDownToFade < 230)
	{
		App->render->Blit(deathTexture1, 0, 0, NULL);
	}
	else if (countDownToFade > 215 && countDownToFade < 220)
	{
		App->render->Blit(deathTexture2, 0, 0, NULL);

	}
	else if (countDownToFade == 180)
	{
		if (App->player->lifes > 0)
		{
			App->fade->FadeToBlack((Module*)App->scene2, (Module*)App->scene2, 60);
		}
		else
		{
			App->fade->FadeToBlack((Module*)App->scene2, (Module*)App->sceneIntro, 60);
		}
	}


	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene2::CleanUp()
{

	LOG("---------------------------------------------- CleanUp ModuleScene2 ----------------------------------------------")

		activeTextures = activeColliders = activeFonts = activeFx = 0;


	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->tileset->Disable();
	App->boosters->Disable();
	App->harpoon->Disable();
	App->doubleShot->Disable();
	App->gunShot->Disable();
	App->hookShot->Disable();

	App->sceneIntro->countdown = 1;

	App->textures->Unload(App->boosters->texture);
	--totalTextures;

	App->textures->Unload(App->harpoon->texture);
	--totalTextures;
	App->textures->Unload(bgTexture);
	--totalTextures;
	App->textures->Unload(fgTexture);
	--totalTextures;
	App->textures->Unload(deathTexture1);
	--totalTextures;
	App->textures->Unload(deathTexture2);
	--totalTextures;
	App->textures->Unload(App->boosters->texture);
	--totalTextures;
	App->audio->UnloadFx(App->harpoon->HarpoonFx);
	App->harpoon->totalFx--;

	App->collisions->RemoveCollider(App->boosters->typeBooster->collider);


	App->textures->Unload(App->enemies->texture);

	return true;
}
