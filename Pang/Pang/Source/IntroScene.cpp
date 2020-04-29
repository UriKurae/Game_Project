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
	intro.PushBack({0, 0, 384, 245});
	intro.PushBack({ 384, 0, 384, 245 });
	intro.PushBack({ 768, 0, 384, 245 });
	intro.PushBack({ 1152, 0, 384, 245 });
	intro.PushBack({ 1536, 0, 384, 245 });
	intro.PushBack({ 1920, 0, 384, 245 });
	intro.PushBack({ 2304, 0, 384, 245 });
	intro.PushBack({ 2688, 0, 384, 245 });
	intro.PushBack({ 3072, 0, 384, 245 });
	intro.PushBack({ 3456, 0, 384, 245 });
	intro.PushBack({ 3840, 0, 384, 245 });
	intro.PushBack({ 4224, 0, 384, 245 });
	intro.PushBack({ 4608, 0, 384, 245 });
	intro.PushBack({ 4992, 0, 384, 245 });

	intro.loop = false;
	intro.speed = 0.2f;
	/*intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	intro.PushBack({ 0, 0, 384, 245 });
	*/
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
	

	bgTexture = App->textures->Load("Assets/UI/pangAnimationTitleScreen.png");
	/*intro_1 = App->textures->Load("Assets/UI/Intro_1.png");
	intro_2 = App->textures->Load("Assets/UI/Intro_2.png");
	intro_3 = App->textures->Load("Assets/UI/Intro_3.png");*/

	char lookupTable1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!✕-:©✕ " };
	introIndex = App->fonts->Load("Assets/UI/Fonts/Pang_font.png", lookupTable1, 1);


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

	if (countdown == 0) {
		currentAnimation = &intro;
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
	if (App->input->keys[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN) {
		countdown = 1;
	}
	else {
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
	}
	
	
	if (countdown == 0)
	{
		SDL_DestroyTexture(intro_3);
		currentAnimation = &intro;

		App->fonts->BlitText(90, 181, introIndex, "©MITCHELL");
		App->fonts->BlitText(240, 181, introIndex, "1989");
	
	}
	if (countdown == 1){  App->audio->PlayMusic("Assets/Sound/Sounds_Gameplay/Title.ogg", 1.0f);  } 

	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	SDL_DestroyTexture(bgTexture);
	
	App->fonts->UnLoad(introIndex);
	//App->input->Disable();

	/*SDL_DestroyTexture(intro_1);
	SDL_DestroyTexture(intro_2);
	SDL_DestroyTexture(intro_3);*/

	
	return true;
}