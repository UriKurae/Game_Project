#include "IntroScene.h"

#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

#include "ModuleCollisions.h"
#include "ModuleEnemies.h"


#include <SDL\include\SDL_scancode.h>
#include <SDL\include\SDL.h>
#include <SDL_mixer\include\SDL_mixer.h>


SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	App->player->lifes = 3;
	

	bgTexture = App->textures->Load("Assets/UI/Intro.png");
	intro_1 = App->textures->Load("Assets/UI/Intro_1.png");
	intro_2 = App->textures->Load("Assets/UI/Intro_2.png");
	intro_3 = App->textures->Load("Assets/UI/Intro_3.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->input->Enable();
	//App->enemies->Disable();
	
	return ret;
}

update_status SceneIntro::Update()
{
	if (countdown != 0)
	{

	countdown--;
	}

	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN && countdown == 0)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 30);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	if (countdown > 840)
	{
		App->render->Blit(intro_1, 0, 0, NULL);
	}
	else if (countdown > 420 && countdown < 840)
	{
		App->render->Blit(intro_2, 0, 0, NULL);
		SDL_DestroyTexture(intro_1);
	}
	else if (countdown > 0 && countdown < 420)
	{
		App->render->Blit(intro_3, 0, 0, NULL);
		SDL_DestroyTexture(intro_2);
	}
	else if (countdown == 0)
	{
		SDL_DestroyTexture(intro_3);

		App->render->Blit(bgTexture, 0, 0, NULL);
		App->fonts->BlitText(72, 181, App->player->uiIndex, "©MITCHELL");
		App->fonts->BlitText(244, 181, App->player->uiIndex, "1989");
	
	}
	if (countdown == 1){  App->audio->PlayMusic("Assets/Sound/Sounds_Gameplay/Title.ogg", 1.0f);  } 

	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	SDL_DestroyTexture(bgTexture);
	App->input->Disable();
	/*SDL_DestroyTexture(intro_1);
	SDL_DestroyTexture(intro_2);
	SDL_DestroyTexture(intro_3);*/

	
	return true;
}