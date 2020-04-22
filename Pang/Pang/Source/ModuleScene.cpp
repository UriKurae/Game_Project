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


#include "SDL/include/SDL_scancode.h"



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

	countDownToFade = 500;
	fgTexture = App->textures->Load("Assets/Foregrounds/Foreground Mt.Fuji(Day).png"); //fg on 1st Level is invisible
	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Fuji(Day).png");
	deathTexture1 = App->textures->Load("Assets/Foregrounds/Foreground_Death_1.png");
	deathTexture2 = App->textures->Load("Assets/Foregrounds/Foreground_Death_2.png");

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

	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 50, 20);
	
	App->player->uiIndex = 0;
	
	App->player->score = 0;

	App->scene->balloonsOnScene = 1;
	return ret;
}

update_status ModuleScene::Update()
{
	LOG("Balloons On Stage %d", App->scene->balloonsOnScene);
	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		balloonsOnScene = 0;
	}


	if (balloonsOnScene == 0)
	{
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->winScene, 60);
	}

//	LOG("enemyOnStage == %d", balloonsOnScene);


	return update_status::UPDATE_CONTINUE;
}
// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	
	
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(fgTexture, 0, 0, NULL);

	//This could be more clean 
	//Animation to stop the scene with the death 

	/*if (App->player->destroyed)
	{
		countDownToFade--;
	}
	if (countDownToFade < 500)
	{
		countDownToFade--;
	}
	if (countDownToFade > 440 && countDownToFade < 460)
	{
		App->render->Blit(deathTexture1, 0, 0, NULL);
		
	}
	else if (countDownToFade > 435 && countDownToFade < 440)
	{
		App->render->Blit(deathTexture2, 0, 0, NULL);
	
	}
	else if (countDownToFade <= 0)
	{
		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneIntro, 60);
	}*/
	
	

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{

	App->player->Disable();
	App->enemies->Disable();
	App->harpoon->Disable();
	App->collisions->Disable();
	//App->fonts->UnLoad(App->player->uiIndex);
	//App->audio->CleanUp();
	return true;

}