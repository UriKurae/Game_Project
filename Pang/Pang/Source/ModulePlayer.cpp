#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleHarpoon_Shot.h"
#include "ModuleHarpoon_HookShot.h"
#include "ModuleFadeToBlack.h"

#include "Enemy.h"
#include "ModuleEnemies.h"

#include "ModuleFonts.h"

#include "IntroScene.h"

#include "SDL/include/SDL.h"
#include "SDL/include/SDL_scancode.h"


#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	name = "PLAYER";

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
	timeTexture = App->textures->Load("Assets/UI/Time.png");
	++activeTextures; ++totalTextures;
	currentAnimation = &idleAnim;
	
	//SET SPAWN POSITION FOR PLAYER
	position.x = (SCREEN_WIDTH / 2) - 20;
	position.y = SCREEN_HEIGHT - 77;

	
	collider = App->collisions->AddCollider({ position.x, position.y, 26, 32 }, Collider::Type::PLAYER, this);
	++activeColliders; ++totalColliders;
	destroyed = false;
	time = 100;

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!✕-:©✕ " };
	uiIndex = App->fonts->Load("Assets/UI/Fonts/Pang_font.png", lookupTable, 1);
	char timeTable[] = { "0123456789" };
	timeIndex = App->fonts->Load("Assets/UI/CountdownNumbers.png", timeTable, 1);
	++activeFonts; ++totalFonts;

	return ret;
}

update_status ModulePlayer::Update()
{
	GamePad& pad = App->input->pads[0];

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
	{
		App->input->ShakeController(0, 12, 0.33f);
	}

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
	{
		App->input->ShakeController(0, 36, 0.66f);
	}

	//Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 1.0f);
	}

	count++;
	if (count % 60 == 0 && time > 0 && App->scene->balloonsOnScene > 0 && destroyed == false || count % 60 == 0 && time > 0 && App->scene2->balloonsOnScene > 0 && destroyed == false) {
		time--;
	}

	if (App->scene->balloonsOnScene == 0 || App->scene2->balloonsOnScene == 0) {
		timeBonus = time * 100;
	}

	//Detect inputs
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
			if (App->scene->balloonsOnScene == 0)
			{
				idleAnim.Reset();
				currentAnimation = &idleAnim;
			}
			else
			{
				shotAnim.Reset();
				currentAnimation = &shotAnim;
			}
		}
	}

	if (pad.l_x > 0 && !destroyed)
	{
		position.x += speed;

		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (pad.l_x < 0 && !destroyed)
	{
		position.x -= speed;

		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (pad.a == true)
	{
		if (currentAnimation != &shotAnim && App->harpoon->destroyed == true)
		{
			if (App->scene->balloonsOnScene == 0)
			{
				idleAnim.Reset();
				currentAnimation = &idleAnim;
			}
			else
			{
				shotAnim.Reset();
				currentAnimation = &shotAnim;
			}
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
	
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		collider->SetPos(position.x, position.y);
	}
	else
	{
		collider->SetPos(position.x, position.y);
	}

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
	
	if (App->input->keys[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN)
	{
		destroyed = true;
		lifes--;

		App->collisions->Disable();
		App->sceneIntro->countdown = 1;
		
	}

	if (destroyed == true) //Blit the dead animation
	{
		
		currentAnimation = &deadAnimLeft;

		rect = currentAnimation->GetCurrentFrame();
		
		App->render->Blit(texture, position.x, position.y, &rect);

		//App->fade->FadeToBlack((Module*)App->scene, (Module*)App->sceneIntro, 60);

	}
	
	sprintf_s(scoreText, 10, "%d", score);
	sprintf_s(timeText, 5, "%d", time);

	App->fonts->BlitText(81, 216, uiIndex, scoreText);
	App->fonts->BlitText(25, 208, uiIndex, "PLAYER-1");
	App->fonts->BlitText(158, 208, uiIndex, "MT.FUJI");
	if (scene1 == true) 
	{
		App->fonts->BlitText(161, 228, uiIndex, "1-1 STAGE");
	}
	if (scene2 == true)
	{
		App->fonts->BlitText(161, 228, uiIndex, "1-2 STAGE");
	}
	App->fonts->BlitText(151, 236, uiIndex, "HI: 100000");
	App->fonts->BlitText(272, 208, uiIndex, "PLAYER-2");
	App->render->Blit(timeTexture, 272, 9, NULL);
	App->fonts->BlitText(337, 9, timeIndex, timeText);

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	/*if (c2->type == Collider::Type::PLAYER)
	{
		App->harpoon->Disable();
		App->hookShot->Enable();
	}*/

	if (c1->type == Collider::Type::PLAYER) //player collider
	{
		if (c2 == App->scene->leftWall || c2 == App->scene2->leftWall) {
			position.x = 6;
		}

		if (c2 == App->scene->rightWall || c2 == App->scene2->rightWall) {
			position.x = SCREEN_WIDTH - 33;
		}

		if (c2->type == Collider::Type::VERY_BIG_BALLOON)
		{
			destroyed = true;
			//App->collisions->RemoveCollider(c1);
			//App->collisions->RemoveCollider(c2);
			c1->pendingToDelete = true;
			c2->pendingToDelete = true;
			lifes--;

			App->scene->leftWall->pendingToDelete = true;
			App->scene->rightWall->pendingToDelete = true;
			App->scene->upperWall->pendingToDelete = true;
			App->scene->lowerWall->pendingToDelete = true;
			//App->collisions->RemoveCollider(App->scene->leftWall);
			//App->collisions->RemoveCollider(App->scene->rightWall);
			//App->collisions->RemoveCollider(App->scene->upperWall);
			//App->collisions->RemoveCollider(App->scene->lowerWall);
		}

		if (c2->type == Collider::Type::BIG_BALLOON)
		{
			destroyed = true;
			c1->pendingToDelete = true;
			c2->pendingToDelete = true;
			lifes--;

			App->scene->leftWall->pendingToDelete = true;
			App->scene->rightWall->pendingToDelete = true;
			App->scene->upperWall->pendingToDelete = true;
			App->scene->lowerWall->pendingToDelete = true;
		}

		if (c2->type == Collider::Type::SMALL_BALLOON)
		{
			destroyed = true;
			c1->pendingToDelete = true;
			c2->pendingToDelete = true;
			lifes--;

			App->scene->leftWall->pendingToDelete = true;
			App->scene->rightWall->pendingToDelete = true;
			App->scene->upperWall->pendingToDelete = true;
			App->scene->lowerWall->pendingToDelete = true;
		}

		if (c2->type == Collider::Type::VERY_SMALL_BALLOON)
		{
			destroyed = true;
			c1->pendingToDelete = true;
			c2->pendingToDelete = true;
			lifes--;

			App->scene->leftWall->pendingToDelete = true;
			App->scene->rightWall->pendingToDelete = true;
			App->scene->upperWall->pendingToDelete = true;
			App->scene->lowerWall->pendingToDelete = true;
		}
	}
}

bool ModulePlayer::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	App->fonts->UnLoad(uiIndex);
	--totalFonts;
	//SDL_DestroyTexture(texture);
	App->textures->Unload(texture);
	--totalTextures;
	App->collisions->RemoveCollider(collider);
	--totalColliders;

	return true;
}