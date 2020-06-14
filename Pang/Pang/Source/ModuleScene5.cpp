#include "ModuleScene5.h"

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
#include "ModuleTileset.h"
#include "ModuleBoosters.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModuleScene5::ModuleScene5(bool startEnabled) : Module(startEnabled)
{
	name = "LEVEL 5";

	pushBlocksAnims();
}

ModuleScene5::~ModuleScene5()
{
}

bool ModuleScene5::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	fgTexture = App->textures->Load("Assets/Items&Weapons/BlockSprites.png");
	++activeTextures; ++totalTextures;

	destroyedBlockTopLeft = false;
	destroyedBlockBottomLeft = false;
	destroyedBlockMiddle = false;
	destroyedBlockTopRight = false;
	destroyedBlockBottomRight = false;

	countDownToFade = 300;
	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Keirin(Sunset).png");
	++activeTextures; ++totalTextures;
	deathTexture1 = App->textures->Load("Assets/Foregrounds/Foreground_Death_1.png");
	++activeTextures; ++totalTextures;
	deathTexture2 = App->textures->Load("Assets/Foregrounds/Foreground_Death_2.png");
	++activeTextures; ++totalTextures;


	App->audio->PlayMusic("Assets/Sound/Soundtracks/MtKeirin.ogg", 0.0f);

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->tileset->Enable();
	App->boosters->Enable();

	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 16, 13);
	App->enemies->AddEnemy(ENEMY_TYPE::BIGBALLOON, 200, 58);	

	App->player->uiIndex = 0;

	App->player->score = 0;

	App->player->scene1 = false;
	App->player->scene2 = false;
	App->player->scene3 = false;
	App->player->scene4 = false;
	App->player->scene5 = true;
	App->player->scene6 = false;

	musicBool1 = true;
	musicBool2 = true;

	return ret;
}

update_status ModuleScene5::Update()
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
		App->fade->FadeToBlack((Module*)App->scene5, (Module*)App->winScene, 60);
	}

	if (App->player->time == 50 && musicBool1 == true) {
		musicBool1 = false;
		App->audio->PlayMusic("Assets/Sound/Soundtracks/GettingLate.ogg", 0.0f);
	}

	if (App->player->time == 20 && musicBool2 == true) {
		musicBool2 = false;
		App->audio->PlayMusic("Assets/Sound/Soundtracks/OutOfTime!.ogg", 0.0f);
	}

	
	blockDestroyTopLeft.Update();
	blockDestroyBottomLeft.Update();
	blockDestroyMiddle.Update();
	blockDestroyTopRight.Update();
	blockDestroyBottomRight.Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleScene5::PostUpdate()
{

	//Print the background on the screen.
	App->render->Blit(bgTexture, 0, 0, NULL);

	//Print the blocks on the screen.
	if (destroyedBlockBottomLeft == false)
	{
		App->render->Blit(fgTexture, 96, 80, &(blockVer.GetCurrentFrame()), 1.0f);
		blockDestroyBottomLeft.Reset();
	}
	else
	{
		App->render->Blit(fgTexture, 96, 80, &(blockDestroyBottomLeft.GetCurrentFrame()), 1.0f);
	}

	if (destroyedBlockTopLeft == false)
	{
		App->render->Blit(fgTexture, 96, 56, &(blockVer.GetCurrentFrame()), 1.0f);
		blockDestroyTopLeft.Reset();
	}
	else
	{
		App->render->Blit(fgTexture, 96, 56, &(blockDestroyTopLeft.GetCurrentFrame()), 1.0f);
	}

	if (destroyedBlockMiddle == false)
	{
		App->render->Blit(fgTexture, 192, 56, &(blockVer.GetCurrentFrame()), 1.0f);
		blockDestroyMiddle.Reset();
	}
	else
	{
		App->render->Blit(fgTexture, 192, 56, &(blockDestroyMiddle.GetCurrentFrame()), 1.0f);
	}

	if (destroyedBlockTopRight == false)
	{
		App->render->Blit(fgTexture, 288, 56, &(blockVer.GetCurrentFrame()), 1.0f);
		blockDestroyTopRight.Reset();
	}
	else
	{

		App->render->Blit(fgTexture, 288, 56, &(blockDestroyTopRight.GetCurrentFrame()), 1.0f);
	}
	if (destroyedBlockBottomRight == false)
	{
		App->render->Blit(fgTexture, 288, 80, &(blockVer.GetCurrentFrame()), 1.0f);
		blockDestroyBottomRight.Reset();
	}
	else
	{
		App->render->Blit(fgTexture, 288, 80, &(blockDestroyBottomRight.GetCurrentFrame()), 1.0f);
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
			App->fade->FadeToBlack((Module*)App->scene5, (Module*)App->scene5, 60);
		}
		else
		{
			App->fade->FadeToBlack((Module*)App->scene5, (Module*)App->sceneIntro, 60);
		}
	}


	return update_status::UPDATE_CONTINUE;
}

void ModuleScene5::pushBlocksAnims()
{

	blockVer.PushBack({ 8, 14, 8, 24 });

	blockDestroyTopLeft.PushBack({ 40, 14, 8, 24 });
	blockDestroyTopLeft.PushBack({ 56, 14, 8, 24 });
	blockDestroyTopLeft.PushBack({ 71, 14, 8, 24 });
	blockDestroyTopLeft.PushBack({ 143, 51, 8, 24 });
	blockDestroyTopLeft.speed = 0.1f;
	blockDestroyTopLeft.loop = false;

	blockDestroyBottomLeft.PushBack({ 40, 14, 8, 24 });
	blockDestroyBottomLeft.PushBack({ 56, 14, 8, 24 });
	blockDestroyBottomLeft.PushBack({ 71, 14, 8, 24 });
	blockDestroyBottomLeft.PushBack({ 143, 51, 8, 24 });
	blockDestroyBottomLeft.speed = 0.1f;
	blockDestroyBottomLeft.loop = false;

	blockDestroyMiddle.PushBack({ 40, 14, 8, 24 });
	blockDestroyMiddle.PushBack({ 56, 14, 8, 24 });
	blockDestroyMiddle.PushBack({ 71, 14, 8, 24 });
	blockDestroyMiddle.PushBack({ 143, 51, 8, 24 });
	blockDestroyMiddle.speed = 0.1f;
	blockDestroyMiddle.loop = false;

	blockDestroyTopRight.PushBack({ 40, 14, 8, 24 });
	blockDestroyTopRight.PushBack({ 56, 14, 8, 24 });
	blockDestroyTopRight.PushBack({ 71, 14, 8, 24 });
	blockDestroyTopRight.PushBack({ 143, 51, 8, 24 });
	blockDestroyTopRight.speed = 0.1f;
	blockDestroyTopRight.loop = false;

	blockDestroyBottomRight.PushBack({ 40, 14, 8, 24 });
	blockDestroyBottomRight.PushBack({ 56, 14, 8, 24 });
	blockDestroyBottomRight.PushBack({ 71, 14, 8, 24 });
	blockDestroyBottomRight.PushBack({ 143, 51, 8, 24 });
	blockDestroyBottomRight.speed = 0.1f;
	blockDestroyBottomRight.loop = false;

}

bool ModuleScene5::CleanUp()
{
	LOG("---------------------------------------------- CleanUp ModuleScene5 ----------------------------------------------")

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
