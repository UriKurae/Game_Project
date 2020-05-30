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

	block.PushBack({ 8, 220, 16, 8 });
	unBlock.PushBack({ 26, 220, 16, 8 });
	

	countDownToFade = 300;
	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Keirin(Night).png");
	++activeTextures; ++totalTextures;
	deathTexture1 = App->textures->Load("Assets/Foregrounds/Foreground_Death_1.png");
	++activeTextures; ++totalTextures;
	deathTexture2 = App->textures->Load("Assets/Foregrounds/Foreground_Death_2.png");
	++activeTextures; ++totalTextures;
	lifesTexture1 = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");
	++activeTextures; ++totalTextures;
	lifesTexture2 = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");
	++activeTextures; ++totalTextures;
	lifesTexture3 = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");
	++activeTextures; ++totalTextures;

	App->audio->PlayMusic("Assets/Sound/Soundtracks/MtFuji.ogg", 1.0f);

	//Walls collider
	lowerWall = App->collisions->AddCollider({ 0, 200, 384, 8 }, Collider::Type::WALL);
	++activeColliders; ++totalColliders;
	leftWall = App->collisions->AddCollider({ 0, 0, 8, 208 }, Collider::Type::WALL);
	++activeColliders; ++totalColliders;
	upperWall = App->collisions->AddCollider({ 0, 0, 384, 8 }, Collider::Type::WALL);
	++activeColliders; ++totalColliders;
	rightWall = App->collisions->AddCollider({ 376, 0, 8, 208 }, Collider::Type::WALL);
	++activeColliders; ++totalColliders;

	leftPlatform = App->collisions->AddCollider({ 79,64,16,8 }, Collider::Type::UNBREAKABLE_BLOCK);
	++activeColliders; ++totalColliders;
	rightPlatform = App->collisions->AddCollider({ 296,64,16,8 }, Collider::Type::UNBREAKABLE_BLOCK);
	++activeColliders; ++totalColliders;
	centralPlatform = App->collisions->AddCollider({ 184,64,16,8 }, Collider::Type::BREAKABLE_BLOCK);
	++activeColliders; ++totalColliders;

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->hookShot->Enable();
	App->harpoon->Disable();
	App->tileset->Enable();
	App->boosters->Enable();

	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 184, 17);
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON2, 152, 17);

	App->player->uiIndex = 0;

	App->player->score = 0;

	App->enemies->balloon.balloonsOnScene = 2;

	App->player->scene1 = false;
	App->player->scene2 = false;
	App->player->scene3 = false;
	App->player->scene4 = false;
	App->player->scene5 = false;
	App->player->scene6 = true;


	//Buff=App->collisions->AddCollider({ 20, 190, 10, 10 }, Collider::Type::PLAYER); FOR TESTS DON'T ERASE PLS

	return ret;
}

update_status ModuleScene6::Update()
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
		App->harpoon->Disable();
		App->fade->FadeToBlack((Module*)App->scene6, (Module*)App->winScene, 60);
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleScene6::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);
	
	App->render->Blit(fgTexture, 79, 64, &(unBlock.GetCurrentFrame()), 1.0f);
	App->render->Blit(fgTexture, 296, 64, &(unBlock.GetCurrentFrame()), 1.0f);

	if (destroyedBlockCentral == false)
	{
		App->render->Blit(fgTexture, 184, 64, &(block.GetCurrentFrame()), 1.0f);
	}

	if (App->player->lifes == 0) {
		App->render->Blit(App->player->gameOverTexture, 150, 99, NULL);
	}

	if (App->player->lifes == 3)
	{
		App->render->Blit(lifesTexture1, 25, 227, &lifesTextureRect, 0, false);
		App->render->Blit(lifesTexture2, 41, 227, &lifesTextureRect, 0, false);
		App->render->Blit(lifesTexture3, 57, 227, &lifesTextureRect, 0, false);
	}

	else if (App->player->lifes == 2)
	{
		App->render->Blit(lifesTexture1, 25, 227, &lifesTextureRect, 0, false);
		App->render->Blit(lifesTexture2, 41, 227, &lifesTextureRect, 0, false);
	}

	else if (App->player->lifes == 1)
	{
		App->render->Blit(lifesTexture1, 25, 227, &lifesTextureRect, 0, false);
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

			//App->player->collider->pendingToDelete = true;
			App->collisions->RemoveCollider(App->player->collider);
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
	App->harpoon->Disable();
	App->collisions->Disable();
	App->hookShot->Disable();
	App->tileset->Disable();
	App->doubleShot->Disable();
	App->boosters->Disable();
	App->sceneIntro->countdown = 1;

	//REMOVE HARPOONFX WHEN BALLOON KILLS U AND HARPOON IS ALIVE

	if (App->harpoon->destroyed)
	{
		/*App->audio->UnloadFx(App->harpoon->HarpoonFx);
		App->harpoon->totalFx--;*/
		App->harpoon->activeFx = 0;

		App->textures->Unload(App->harpoon->texture);
		App->harpoon->totalTextures--;
		App->harpoon->activeTextures = 0;

		if (!App->harpoon->destroyed)
		{

			App->collisions->RemoveCollider(App->harpoon->colliderH);
			App->harpoon->totalColliders--;
			App->harpoon->activeColliders = 0;
		}

	}

	//App->harpoon->HarpoonFx = 0;

	App->textures->Unload(App->boosters->texture);
	--totalTextures;

	App->textures->Unload(App->harpoon->texture);
	--totalTextures;
	App->textures->Unload(bgTexture);
	--totalTextures;
	App->textures->Unload(lifesTexture1);
	--totalTextures;
	App->textures->Unload(lifesTexture2);
	--totalTextures;
	App->textures->Unload(lifesTexture3);
	--totalTextures;
	App->textures->Unload(deathTexture1);
	--totalTextures;
	App->textures->Unload(deathTexture2);
	--totalTextures;
	App->textures->Unload(App->boosters->texture);
	--totalTextures;
	App->audio->UnloadFx(App->harpoon->HarpoonFx);
	App->harpoon->totalFx--;

	App->collisions->RemoveCollider(leftWall);
	--totalColliders;
	App->collisions->RemoveCollider(rightWall);
	--totalColliders;
	App->collisions->RemoveCollider(upperWall);
	--totalColliders;
	App->collisions->RemoveCollider(lowerWall);
	--totalColliders;
	App->collisions->RemoveCollider(rightPlatform);
	--totalColliders;
	App->collisions->RemoveCollider(leftPlatform);
	--totalColliders;
	App->collisions->RemoveCollider(centralPlatform);
	--totalColliders;

	App->collisions->RemoveCollider(App->boosters->typeBooster->collider);

	App->textures->Unload(App->enemies->texture);


	return true;
}
