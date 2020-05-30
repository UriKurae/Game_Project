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
#include "ModuleBoosters.h"

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

	//move upStairs
	upAnim.PushBack({0, 34, 25, 32});
	upAnim.PushBack({37, 34, 24, 32});
	upAnim.PushBack({69, 34, 26, 32});
	upAnim.PushBack({103, 34, 26, 32});
	upAnim.PushBack({4, 75, 24, 31});
	upAnim.PushBack({35, 75, 27, 31});
	upAnim.PushBack({69, 76, 27, 30});
	upAnim.speed = 0.1f;

	//move upStairs
	downAnim.PushBack({ 69, 76, 27, 30 });
	downAnim.PushBack({ 35, 75, 27, 31 });
	downAnim.PushBack({ 4, 75, 24, 31 });
	downAnim.PushBack({ 103, 34, 26, 32 });
	downAnim.PushBack({ 69, 34, 26, 32 });
	downAnim.PushBack({ 37, 34, 24, 32 });
	downAnim.PushBack({ 0, 34, 25, 32 });
	downAnim.speed = 0.1f;

	//move updpwnStairs
	stairsAnim.PushBack({ 104, 81, 28, 26 });
	stairsAnim.speed = 0.1;
	stairsAnim.loop = false;

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

	bool godMode = false;

	ready = 3;

	texture = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");
	timeTexture = App->textures->Load("Assets/UI/Time.png");
	++activeTextures; ++totalTextures;
	currentAnimation = &idleAnim;

	gameOverTexture = App->textures->Load("Assets/UI/GameOver.png");
	++activeTextures; ++totalTextures;
	readyTexture = App->textures->Load("Assets/UI/Ready.png");
	++activeTextures; ++totalTextures;
	
	//SET SPAWN POSITION FOR PLAYER
	//if (scene4 == true) {
	//	position.x = 8;
	//	position.y = 124;
	//}

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

	//TO GET THE MOUSE POSITION, SDL_GETMouseState, MUST FIX THE FOR SOME FUCKING REASON THE BALLS WONT SPAWN.
	if (App->input->keys[SDL_SCANCODE_V] == KEY_STATE::KEY_DOWN)
	{
		
		SDL_GetMouseState(&mouseX, &mouseY);
	

		App->enemies->AddEnemy(ENEMY_TYPE::VERYBIGBALLOON, (mouseX/SCREEN_SIZE), (mouseY/SCREEN_SIZE));
	}

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

	//Press button G for God Mode
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		godMode = !godMode;
	}

	count++;

	if (count % 30 == 0 && ready > 0) {
		ready--;
	}

	if (ready == 0) {
		if (count % 60 == 0 && time > 0 && App->enemies->balloon.balloonsOnScene > 0 && destroyed == false) {
			time--;
		}

		if (App->enemies->balloon.balloonsOnScene == 0) {
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
				if (App->enemies->balloon.balloonsOnScene == 0)
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
				if (App->enemies->balloon.balloonsOnScene == 0)
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
			&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE)
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
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	
	if (ready == 3 || ready == 1) {
		App->render->Blit(App->player->readyTexture, 150, 99, NULL);
	}

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
	sprintf_s(timeText, 5, "%3d", time);

	App->fonts->BlitText(81, 216, uiIndex, scoreText);
	App->fonts->BlitText(25, 208, uiIndex, "PLAYER-1");

	if (scene1 == true) 
	{
		App->fonts->BlitText(161, 228, uiIndex, "1-1 STAGE");
		App->fonts->BlitText(158, 208, uiIndex, "MT.FUJI");
	}
	else if (scene2 == true)
	{
		App->fonts->BlitText(161, 228, uiIndex, "1-2 STAGE");
		App->fonts->BlitText(158, 208, uiIndex, "MT.FUJI");
	}
	else if (scene3 == true)
	{
		App->fonts->BlitText(161, 228, uiIndex, "1-3 STAGE");
		App->fonts->BlitText(158, 208, uiIndex, "MT.FUJI");
	}
	else if (scene4 == true)
	{
		App->fonts->BlitText(161, 228, uiIndex, "2-4 STAGE");
		App->fonts->BlitText(158, 208, uiIndex, "MT.KEIRIN");
	}
	else if (scene5 == true)
	{
		App->fonts->BlitText(161, 228, uiIndex, "2-5 STAGE");
		App->fonts->BlitText(158, 208, uiIndex, "MT.KEIRIN");
	}
	else if (scene6 == true)
	{
		App->fonts->BlitText(161, 228, uiIndex, "2-6 STAGE");
		App->fonts->BlitText(158, 208, uiIndex, "MT.KEIRIN");
	}
	App->fonts->BlitText(151, 236, uiIndex, "HI: 100000");
	App->fonts->BlitText(272, 208, uiIndex, "PLAYER-2");
	App->render->Blit(timeTexture, 269, 9, NULL);
	App->fonts->BlitText(334, 9, timeIndex, timeText);

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	/*if (c2->type == Collider::Type::PLAYER)
	{
		App->harpoon->Disable();
		App->hookShot->Enable();
	}*/

	
	if (c2->type == Collider::Type::WALL || c2->type == Collider::Type::UNBREAKABLE_BLOCK) {
		if (c1->rect.x > c2->rect.x && c1->rect.x < c2->rect.x + c2->rect.w) {
			position.x = position.x + 2;
		}

		if (c1->rect.x + c1->rect.w > c2->rect.x && c1->rect.x + c1->rect.w < c2->rect.x + c2->rect.w) {
			position.x = position.x - 2;
		}
		
		if (c1->rect.y + c1->rect.h > c2->rect.y) {
			position.y = 168;
		}
	}

	if (c2->type == Collider::Type::STAIR) {
		if (c1->rect.y <= c2->rect.y) {
			if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
				position.y -= 0.2f;
				stairsAnim.Reset();
				currentAnimation = &stairsAnim;
			}
		}

		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && !destroyed)
		{
			position.y -= 0.5f;

			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}

		}

		if (c1->rect.y + c1->rect.h >= c2->rect.y) {
			if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
				position.y += 0.2f;
				stairsAnim.Reset();
				currentAnimation = &stairsAnim;
			}
		}

		else if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !destroyed)
		{
			position.y += 1;

			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}

		}
	}

	//if (c2->type == Collider::Type::UNBREAKABLE_BLOCK) {
	//	if (c1->rect.x > c2->rect.x && c1->rect.x < c2->rect.x + c2->rect.w) {
	//		position.x = 30;
	//	}

	//	if (c1->rect.x + c1->rect.w > c2->rect.x && c1->rect.x + c1->rect.w < c2->rect.x + c2->rect.w) {
	//		position.x = 30;
	//	}

	//}

	if (c2->type == Collider::Type::BALLOON && godMode == false)
	{
		destroyed = true;

		c1->pendingToDelete = true;
		c2->pendingToDelete = true;
		lifes--;

		if (App->player->scene1) {
			App->scene->leftWall->pendingToDelete = true;
			App->scene->rightWall->pendingToDelete = true;
			App->scene->upperWall->pendingToDelete = true;
			App->scene->lowerWall->pendingToDelete = true;
		}
		else if (App->player->scene2) {
			App->scene2->leftWall->pendingToDelete = true;
			App->scene2->rightWall->pendingToDelete = true;
			App->scene2->upperWall->pendingToDelete = true;
			App->scene2->lowerWall->pendingToDelete = true;
			App->scene2->leftPlatform->pendingToDelete = true;
			App->scene2->rightPlatform->pendingToDelete = true;
		}
	}
	
	if (c2->type == Collider::Type::BOOSTERS) {
		//if (App->boosters->booster[CLOCK] == true) {
		//	App->boosters->collider[CLOCK]->pendingToDelete = true;
		//	App->boosters->booster[CLOCK] == false;
		//}
		//
		//if (App->boosters->booster[] == true) {
		//	App->boosters->collider[CLOCK]->pendingToDelete = true;
		//	App->boosters->booster[CLOCK] == false;
		//}

		


		for (int i = 0; i < MAX; i++) {
			if (App->boosters->typeBooster[i].booster == true && c2 == App->boosters->typeBooster[i].collider) {
				App->boosters->typeBooster[i].collider->pendingToDelete = true;
				App->boosters->typeBooster[i].booster = false;
				break;
			}
		}
	}
}

bool ModulePlayer::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	App->fonts->UnLoad(uiIndex);
	--totalFonts;
	App->fonts->UnLoad(timeIndex);
	--totalFonts;
	App->textures->Unload(texture);
	--totalTextures;
	App->collisions->RemoveCollider(collider);
	--totalColliders;

	return true;
}