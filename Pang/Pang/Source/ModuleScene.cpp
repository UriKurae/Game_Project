#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
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

	fgTexture = App->textures->Load("Assets/Foregrounds/Foreground Mt.Fuji(Day).png"); //fg on 1st Level is invisible
	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Fuji(Day).png");

	App->audio->PlayMusic("Assets/Sound/Soundtracks/MtFuji.ogg", 1.0f);

	//Walls collider
	App->collisions->AddCollider({ 0, 200, 384, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 0, 8, 308 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 0, 384, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 376, 0, 8, 308 }, Collider::Type::WALL);

	//ADD COLLIDERS


	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::BALLOON, 50, 20);

	

	return ret;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(fgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}