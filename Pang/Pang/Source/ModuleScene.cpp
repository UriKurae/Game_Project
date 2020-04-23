#include "ModuleScene.h"

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
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"
#include "IntroScene.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL_mixer/include/SDL_mixer.h"



ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{
	
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	countDownToFade = 300;
	fgTexture = App->textures->Load("Assets/Foregrounds/Foreground Mt.Fuji(Day).png"); //fg on 1st Level is invisible
	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Fuji(Day).png");
	deathTexture1 = App->textures->Load("Assets/Foregrounds/Foreground_Death_1.png");
	deathTexture2 = App->textures->Load("Assets/Foregrounds/Foreground_Death_2.png");
	lifesTexture1 = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");
	lifesTexture2 = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");
	lifesTexture3 = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");


	App->audio->PlayMusic("Assets/Sound/Soundtracks/MtFuji.ogg", 1.0f);

	//Walls collider
	lowerWall = App->collisions->AddCollider({ 0, 200, 384, 8 }, Collider::Type::WALL);
	leftWall = App->collisions->AddCollider({ 0, 0, 8, 208 }, Collider::Type::WALL);
	upperWall = App->collisions->AddCollider({ 0, 0, 384, 8 }, Collider::Type::WALL);
	rightWall = App->collisions->AddCollider({ 376, 0, 8, 208 }, Collider::Type::WALL);


	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->harpoon->Enable();
	App->input->Enable();

	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 50, 20);
	
	App->player->uiIndex = 0;
	
	App->player->score = 0;

	App->scene->balloonsOnScene = 1;


	App->enemies->touchWall = false;

	return ret;
}

update_status ModuleScene::Update()
{
	//LOG("Balloons On Stage %d", App->scene->balloonsOnScene);
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		balloonsOnScene = 0;
		App->scene->leftWall->pendingToDelete = true;
		App->scene->rightWall->pendingToDelete = true;
		App->scene->upperWall->pendingToDelete = true;
		App->scene->lowerWall->pendingToDelete = true;
	}


	if (balloonsOnScene == 0)
	{
		App->harpoon->Disable();
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->winScene, 60);
	}

//	LOG("enemyOnStage == %d", balloonsOnScene);
	//LOG("Lifes: ---------%d---------", App->player->lifes);

	return update_status::UPDATE_CONTINUE;
}
// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	
	
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(fgTexture, 0, 0, NULL);

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
			App->fade->FadeToBlack((Module*)App->scene, (Module*)App->scene, 60);
			App->player->collider->pendingToDelete = true;
		}
		else
		{
			App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneIntro, 60);
		}
	}



	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	LOG("---------------------------------------------- CleanUp ModuleScene ----------------------------------------------")
	App->player->Disable();
	App->enemies->Disable();
	App->harpoon->Disable();
	App->collisions->Disable();
	App->input->Disable();
	App->sceneIntro->countdown = 1;
	
	SDL_DestroyTexture(App->harpoon->texture);
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(fgTexture);
	SDL_DestroyTexture(lifesTexture1);
	SDL_DestroyTexture(lifesTexture2);
	SDL_DestroyTexture(lifesTexture3);
	SDL_DestroyTexture(deathTexture1);
	SDL_DestroyTexture(deathTexture2);
	SDL_DestroyTexture(balloon);

	App->harpoon->HarpoonFx = 0;
	
	
	return true;

}