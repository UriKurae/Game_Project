#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleScene.h"
#include "ModuleHarpoon_Shot.h"
#include "ModuleFadeToBlack.h"

#include "Enemy.h"
#include "ModuleEnemies.h"

#include "ModuleFonts.h"

#include "SDL/include/SDL_scancode.h"


#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 0, 110, 26, 32 });

	// move left
	leftAnim.PushBack({379, 0, 30, 31});
	leftAnim.PushBack({416, 0, 28, 31});
	leftAnim.PushBack({448, 0, 30, 32});
	leftAnim.PushBack({482, 0, 30, 31});
	leftAnim.PushBack({516, 0, 30, 32});
	leftAnim.speed = 0.3f;

	//move right
	rightAnim.PushBack({0, 0, 30, 32});
	rightAnim.PushBack({33, 0, 30, 32});
	rightAnim.PushBack({68, 0, 30, 32});
	rightAnim.PushBack({102, 0, 28, 32});
	rightAnim.PushBack({136, 0, 30, 32});
	rightAnim.speed = 0.3f;

	//left death animation
	deadAnimLeft.PushBack({ 69, 110 ,41, 30 });

	//right death animation
	deadAnimRight.PushBack({ 120, 110, 41, 30 });

	//shot animation
	shotAnim.PushBack({ 32, 113, 27, 33 });
	
	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");
	currentAnimation = &idleAnim;
	
	//SET SPAWN POSITION FOR PLAYER
	position.x = (SCREEN_WIDTH / 2) - 20;
	position.y = SCREEN_HEIGHT - 77;

	
	collider = App->collisions->AddCollider({ position.x, position.y, 26, 32 }, Collider::Type::PLAYER, this);
	destroyed = false;
	time = 100;

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!✕-:©✕ " };
	uiIndex = App->fonts->Load("Assets/UI/Fonts/Pang_font.png", lookupTable, 1);

	return ret;
}

update_status ModulePlayer::Update()
{
	count++;
	if (count % 60 == 0 && time > 0 && App->scene->balloonsOnScene > 0) {
		time--;
	}

	if (App->scene->balloonsOnScene == 0) {
		timeBonus = time * 100;
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !destroyed)
	{
		position.x -= speed;

		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !destroyed)
	{
		position.x += speed;

		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}

	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		if (currentAnimation != &shotAnim && App->harpoon->destroyed == true)
		{
			shotAnim.Reset();
			currentAnimation = &shotAnim;
		
		}
	}

	//Detect when A and D are pressed at the same time and set the current animation to idle
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
		App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		//idleAnim.Reset();
		currentAnimation = &idleAnim;
		position.x = position.x;
	}
	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_IDLE)
	{
		currentAnimation = &idleAnim;
	}
		
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	/*if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
		
	}*/

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	
	if (!destroyed)
	{
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		destroyed = true;
	}

	if (destroyed == true) //Blit the dead animation
	{
		//destroyed = false; //in case f2 is pressed
		
		currentAnimation = &deadAnimLeft;

		rect = currentAnimation->GetCurrentFrame();
		
		App->render->Blit(texture, position.x, position.y, &rect);

		App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneIntro, 60);

	}
	
	sprintf_s(scoreText, 10, "%d", score);
	sprintf_s(timeText, 5, "%d", time);

	App->fonts->BlitText(81, 215, uiIndex, scoreText);
	App->fonts->BlitText(25, 207, uiIndex, "PLAYER-1");
	App->fonts->BlitText(158, 207, uiIndex, "MT.FUJI");
	App->fonts->BlitText(161, 228, uiIndex, "1-1 STAGE");
	App->fonts->BlitText(151, 236, uiIndex, "HI: 100000");
	App->fonts->BlitText(272, 207, uiIndex, "PLAYER-2");
	App->fonts->BlitText(264, 9, uiIndex, "TIME:");
	App->fonts->BlitText(351, 9, uiIndex, timeText);


	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER) //player collider
	{
		if (c2 == App->scene->leftWall) {
			position.x = 6;
		}

		if (c2 == App->scene->rightWall) {
			position.x = SCREEN_WIDTH - 33;
		}

		if (c2->type == Collider::Type::VERY_BIG_BALLOON)
		{
			destroyed = true;
			c1->pendingToDelete = true;
			c2->pendingToDelete = true;
		}

		if (c2->type == Collider::Type::BIG_BALLOON)
		{
			destroyed = true;
			c1->pendingToDelete = true;
			c2->pendingToDelete = true;
		}

		if (c2->type == Collider::Type::SMALL_BALLOON)
		{
			destroyed = true;
			c1->pendingToDelete = true;
			c2->pendingToDelete = true;
		}

		if (c2->type == Collider::Type::VERY_SMALL_BALLOON)
		{
			destroyed = true;
			c1->pendingToDelete = true;
			c2->pendingToDelete = true;
		}
	}
}