#include "ModuleScene3.h"

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
#include "Module.h"
#include "ModuleTileset.h"
#include "ModuleBoosters.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModuleScene3::ModuleScene3(bool startEnabled) : Module(startEnabled)
{
	name = "LEVEL 3";

	blockDestroyBottom.PushBack({ 76, 172, 32, 8 });
	blockDestroyBottom.PushBack({ 110, 172, 32, 8 });
	blockDestroyBottom.PushBack({ 144, 172, 32, 8 });
	blockDestroyBottom.PushBack({ 115, 139, 32, 8 });
	blockDestroyBottom.speed = 0.1f;
	blockDestroyBottom.loop = false;

	blockDestroyTop.PushBack({ 76, 172, 32, 8 });
	blockDestroyTop.PushBack({ 110, 172, 32, 8 });
	blockDestroyTop.PushBack({ 144, 172, 32, 8 });
	blockDestroyTop.PushBack({ 115, 139, 32, 8 });
	blockDestroyTop.speed = 0.1f;
	blockDestroyTop.loop = false;

	redBlock.PushBack({ 8, 172, 32, 8 });
	redUnBlock.PushBack({ 42, 172, 32, 8 });
}

ModuleScene3::~ModuleScene3()
{
}

bool ModuleScene3::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	countDownToFade = 300;

	fgTexture = App->textures->Load("Assets/Items&Weapons/BlockSprites.png"); //fg on 3st Level is invisible
	++activeTextures; ++totalTextures;

	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Fuji(Night).png");
	++activeTextures; ++totalTextures;

	deathTexture1 = App->textures->Load("Assets/Foregrounds/Foreground_Death_1.png");
	++activeTextures; ++totalTextures;

	deathTexture2 = App->textures->Load("Assets/Foregrounds/Foreground_Death_2.png");
	++activeTextures; ++totalTextures;

	App->audio->PlayMusic("Assets/Sound/Soundtracks/MtFuji.ogg", 1.0f);

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->tileset->Enable();
	App->boosters->Enable();

	destroyedBlockTop = false;
	destroyedBlockBottom = false;
	destroyedBlockRight = false;
	destroyedBlockLeft = false;

	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 50, 20);
	App->enemies->AddEnemy(ENEMY_TYPE::SMALLBALLOON2, 207, 113);

	App->player->uiIndex = 0;

	App->player->scene1 = false;
	App->player->scene2 = false;
	App->player->scene3 = true;
	App->player->scene4 = false;
	App->player->scene5 = false;
	App->player->scene6 = false;

	musicBool1 = true;
	musicBool2 = true;

	return ret;

}

update_status ModuleScene3::Update()
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
		App->fade->FadeToBlack((Module*)App->scene3, (Module*)App->winScene, 60);
	}

	if (App->player->time == 50 && musicBool1 == true) {
		musicBool1 = false;
		App->audio->PlayMusic("Assets/Sound/Soundtracks/GettingLate.ogg", 0.0f);
	}

	if (App->player->time == 20 && musicBool2 == true) {
		musicBool2 = false;
		App->audio->PlayMusic("Assets/Sound/Soundtracks/OutOfTime!.ogg", 0.0f);
	}

	blockDestroyBottom.Update();
	blockDestroyTop.Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleScene3::PostUpdate()
{

	//Print the background on the screen.
	App->render->Blit(bgTexture, 0, 0, NULL);

	//Print the blocks on the screen, the ones without if are like this because they're not supposed to break and stay always.
	App->render->Blit(fgTexture, 72, 80, &(redUnBlock.GetCurrentFrame()), 1.0f);
	App->render->Blit(fgTexture, 280, 80, &(redUnBlock.GetCurrentFrame()), 1.0f);


	if (destroyedBlockTop == false)
	{
		App->render->Blit(fgTexture, 176, 80, &(redBlock.GetCurrentFrame()), 1.0f);
		blockDestroyTop.Reset();
	}
	else {
		App->render->Blit(fgTexture, 176, 80, &(blockDestroyTop.GetCurrentFrame()), 1.0f);
	}

	if (destroyedBlockBottom == false)
	{
		App->render->Blit(fgTexture, 176, 128, &(redBlock.GetCurrentFrame()), 1.0f);
		blockDestroyBottom.Reset();
	}
	else {
		App->render->Blit(fgTexture, 176, 128, &(blockDestroyBottom.GetCurrentFrame()), 1.0f);
	}


	//Print lifes of the players on the screen.
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
			App->fade->FadeToBlack((Module*)App->scene3, (Module*)App->scene3, 60);
		}
		else
		{
			App->fade->FadeToBlack((Module*)App->scene3, (Module*)App->sceneIntro, 60);
		}
	}


	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene3::CleanUp()
{
	LOG("---------------------------------------------- CleanUp ModuleScene3 ----------------------------------------------")

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
