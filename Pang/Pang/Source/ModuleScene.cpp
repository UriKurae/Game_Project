#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "Enemy_Balloon.h"


ModuleScene::ModuleScene() :Module(true)
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
	lowerWall = App->collisions->AddCollider({ 0, 200, 384, 8 }, Collider::Type::WALL);
	leftWall = App->collisions->AddCollider({ 0, 0, 8, 308 }, Collider::Type::WALL);
	upperWall = App->collisions->AddCollider({ 0, 0, 384, 8 }, Collider::Type::WALL);
	rightWall = App->collisions->AddCollider({ 376, 0, 8, 308 }, Collider::Type::WALL);

	//ADD COLLIDERS
	//collider = App->collisions->AddCollider({0, 0, 48, 40 }, Collider::Type::VERY_BIG_BALLOON, (Module*)App->enemies);

	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 50, 20);
	


	//TODO BALLOON crear dos balloons petits com el balon normal i cada un amb un velocitat inicial diferent.

	

	return ret;
}

update_status ModuleScene::Update()
{
	
	return update_status::UPDATE_CONTINUE;
}
// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(fgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}