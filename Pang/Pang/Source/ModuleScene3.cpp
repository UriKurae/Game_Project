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
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "ModuleTextures.h"
#include "IntroScene.h"
#include "ModuleHarpoon_HookShot.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModuleScene3::ModuleScene3(bool startEnabled) : Module(startEnabled)
{
	name = "LEVEL 3";
}

ModuleScene3::~ModuleScene3()
{
}

bool ModuleScene3::Start()
{
	LOG("Loading background assets");
	bool ret = true;


	countDownToFade = 300;

	fgTexture = App->textures->Load("Assets/Items&Weapons/Blocks Sprites.png"); //fg on 3st Level is invisible
	++activeTextures; ++totalTextures;

	blockDestroy.PushBack({ 48, 158, 32, 8 });
	blockDestroy.PushBack({ 88, 158, 32, 8 });

	block.PushBack({ 8, 158, 32, 8 });

	bgTexture = App->textures->Load("Assets/Backgrounds/Mt.Fuji(Night).png");
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

	//Colliders for blocks
	leftUnDestroyablePlatform = App->collisions->AddCollider({ 72,80,31,6 }, Collider::Type::BREAKABLE_BLOCK);
	++activeColliders; ++totalColliders;

	rightUnDestroyablePlatform = App->collisions->AddCollider({ 278,81,31,6 }, Collider::Type::BREAKABLE_BLOCK);
	++activeColliders; ++totalColliders;

	topDestroyablePlatform = App->collisions->AddCollider({ 175,81,31,6 }, Collider::Type::BREAKABLE_BLOCK);
	++activeColliders; ++totalColliders;

	bottomDestroyablePlatform = App->collisions->AddCollider({ 175,130,31,6 }, Collider::Type::BREAKABLE_BLOCK);
	++activeColliders; ++totalColliders;

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->harpoon->Enable();
	//App->input->Enable();

	//ADD ENEMIES
	App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, 50, 20);

	App->player->uiIndex = 0;

	balloonsOnScene = 1;

	App->player->scene1 = false;
	App->player->scene2 = false;
	App->player->scene3 = true;
	App->player->scene4 = false;
	App->player->scene5 = false;
	App->player->scene6 = false;

	App->enemies->touchWall = false;

	return ret;

}

update_status ModuleScene3::Update()
{
	return update_status();
}

update_status ModuleScene3::PostUpdate()
{
	return update_status();
}

bool ModuleScene3::CleanUp()
{
	return false;
}
