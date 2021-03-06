#include "ModuleScene6.h"

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

ModuleScene6::ModuleScene6(bool startEnabled) : Module(startEnabled)
{
	name = "LEVEL 6";

	block.PushBack({ 8, 220, 16, 8 });
	unBlock.PushBack({ 26, 220, 16, 8 });

	blockDestroy.PushBack({44, 220, 16, 8});
	blockDestroy.PushBack({62, 220, 16, 8});
	blockDestroy.PushBack({80, 220, 16, 8});
	blockDestroy.PushBack({98, 220, 16, 8});
	blockDestroy.speed = 0.1f;
	blockDestroy.loop = false;
}

ModuleScene6::~ModuleScene6()
{

}

bool ModuleScene6::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	fgTexture = App->textures->Load("Assets/Items&Weapons/BlockSprites.png"); //fg on 2st Level is invisible
	++activeTextures; ++totalTextures;

	countDownToFade = 300;
	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Keirin(Night).png");
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
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 184, 17);
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON2, 152, 17);

	App->player->uiIndex = 0;

	App->enemies->balloon.balloonsOnScene = 2;

	App->player->score = 0;

	destroyedBlockCentral = false;

	App->player->scene1 = false;
	App->player->scene2 = false;
	App->player->scene3 = false;
	App->player->scene4 = false;
	App->player->scene5 = false;
	App->player->scene6 = true;

	musicBool1 = true;
	musicBool2 = true;

	//Buff=App->collisions->AddCollider({ 20, 190, 10, 10 }, Collider::Type::PLAYER); FOR TESTS DON'T ERASE PLS

	return ret;
}

update_status ModuleScene6::Update()
{
	if (App->input->keys[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN)
	{
		App->enemies->balloon.balloonsOnScene = 0;
	}


	if (App->enemies->balloon.balloonsOnScene == 0)
	{
		App->fade->FadeToBlack((Module*)App->scene6, (Module*)App->winScene, 60);
	}

	if (App->player->time == 50 && musicBool1 == true) {
		musicBool1 = false;
		App->audio->PlayMusic("Assets/Sound/Soundtracks/GettingLate.ogg", 0.0f);
	}

	if (App->player->time == 20 && musicBool2 == true) {
		musicBool2 = false;
		App->audio->PlayMusic("Assets/Sound/Soundtracks/OutOfTime!.ogg", 0.0f);
	}

	blockDestroy.Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleScene6::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);
	
	App->render->Blit(fgTexture, 79, 63, &(unBlock.GetCurrentFrame()), 1.0f);
	App->render->Blit(fgTexture, 295, 63, &(unBlock.GetCurrentFrame()), 1.0f);

	if (destroyedBlockCentral == false)
	{
		App->render->Blit(fgTexture, 183, 63, &(block.GetCurrentFrame()), 1.0f);
		blockDestroy.Reset();
	}
	else {
		App->render->Blit(fgTexture, 183, 63, &(blockDestroy.GetCurrentFrame()), 1.0f);
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
			App->fade->FadeToBlack((Module*)App->scene6, (Module*)App->scene6, 60);
		}
		else
		{
			App->fade->FadeToBlack((Module*)App->scene6, (Module*)App->sceneIntro, 60);
		}
	}


	return update_status::UPDATE_CONTINUE;

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene6::CleanUp()
{
	LOG("---------------------------------------------- CleanUp ModuleScene ----------------------------------------------")

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

	App->textures->Unload(bgTexture);
	--totalTextures;
	App->textures->Unload(deathTexture1);
	--totalTextures;
	App->textures->Unload(deathTexture2);
	--totalTextures;
	App->textures->Unload(App->boosters->texture);
	--totalTextures;

	App->collisions->RemoveCollider(App->boosters->typeBooster->collider);

	App->textures->Unload(App->enemies->texture);
	App->audio->UnloadFx(App->enemies->balloon.ballonExplosion);

	return true;
}
