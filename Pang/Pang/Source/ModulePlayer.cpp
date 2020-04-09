#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleScene.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
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
	shotAnim.PushBack({ 32, 113, 27, 29 });
	
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

	HarpoonFx = App->audio->LoadFx("Assets/Sound/FX/NormalShoot.wav");

	
	//SET SPAWN POSITION FOR PLAYER
	position.x = (SCREEN_WIDTH / 2) - 20;
	position.y = SCREEN_HEIGHT - 40;

	
	collider = App->collisions->AddCollider({ position.x, position.y, 26, 32 }, Collider::Type::PLAYER, this);
	
	return ret;
}

update_status ModulePlayer::Update()
{

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;

		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;

		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}

	}

	//DO IF AND WHEN STAIRS ARE IMPLEMENTED
	/*if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}*/

	/*if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}*/

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		currentAnimation = &shotAnim;
		App->audio->PlayFx(HarpoonFx);


		int movY = 15;
		int lifeTimeT = 40;
		
		for (int i = 0; i < 23; i++)
		{
			if (i == 0)
			{
				App->particles->harpoonShot[0].lifetime = lifeTimeT; //Was 10 //Clase a part per fer el gancho sencer.
				App->particles->AddParticle(App->particles->harpoonShot[0], position.x + 10, position.y - movY, Collider::Type::PLAYER_SHOT);
			}
			else 
			{

			App->particles->harpoonShot[i].lifetime = lifeTimeT; //Was 10
			App->particles->AddParticle(App->particles->harpoonShot[i-1], position.x + 10, position.y - movY, Collider::Type::PLAYER_SHOT);	
			}
			
			movY += 20;
			lifeTimeT -= 2;
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
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;

		
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider)
	{
		if (c2 == App->scene->leftWall) {
			position.x = 6;
		}

		if (c2 == App->scene->rightWall) {
			position.x = SCREEN_WIDTH-33;
			
		}
		/*
		currentAnimation = &deadAnimLeft;
		destroyed = true;
		*/
		
		

		/*App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);*/


		//App->audio->PlayFx(explosionFx);

		//destroyed = true;
	}
}