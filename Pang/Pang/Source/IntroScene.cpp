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
	name = "S INTRO";

	intro.PushBack({ 0, 0, 384, 245 });
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
	intro.PushBack({ 5376, 0, 384, 245 });
	intro.PushBack({ 5760, 0, 384, 245 });
	intro.PushBack({ 6144, 0, 384, 245 });
	intro.PushBack({ 6528, 0, 384, 245 });
	intro.PushBack({ 6912, 0, 384, 245 });
	intro.PushBack({ 7296, 0, 384, 245 });
	intro.PushBack({ 7680, 0, 384, 245 });
	intro.PushBack({ 8064, 0, 384, 245 });
	intro.PushBack({ 8448, 0, 384, 245 });
	intro.PushBack({ 8832, 0, 384, 245 });
	intro.PushBack({ 9216, 0, 384, 245 });
	intro.PushBack({ 9600, 0, 384, 245 });
	intro.PushBack({ 9984, 0, 384, 245 });
	intro.PushBack({ 10368, 0, 384, 245 });
	intro.PushBack({ 10752, 0, 384, 245 });
	intro.PushBack({ 11136, 0, 384, 245 });
	intro.PushBack({ 11520, 0, 384, 245 });
	intro.PushBack({ 11904, 0, 384, 245 });
	intro.PushBack({ 0, 245, 384, 245 });
	intro.PushBack({ 384, 245, 384, 245 });
	intro.PushBack({ 768, 245, 384, 245 });
	intro.PushBack({ 1152, 245, 384, 245 });
	intro.PushBack({ 1536, 245, 384, 245 });
	intro.PushBack({ 1920, 245, 384, 245 });
	intro.PushBack({ 2304, 245, 384, 245 });
	intro.PushBack({ 2688, 245, 384, 245 });
	intro.PushBack({ 3072, 245, 384, 245 });
	intro.PushBack({ 3456, 245, 384, 245 });
	intro.PushBack({ 3840, 245, 384, 245 });
	intro.PushBack({ 4224, 245, 384, 245 });
	intro.PushBack({ 4608, 245, 384, 245 });
	intro.PushBack({ 4992, 245, 384, 245 });
	intro.PushBack({ 5376, 245, 384, 245 });
	intro.PushBack({ 5760, 245, 384, 245 });
	intro.PushBack({ 6144, 245, 384, 245 });
	intro.PushBack({ 6528, 245, 384, 245 });
	intro.PushBack({ 6912, 245, 384, 245 });
	intro.PushBack({ 7296, 245, 384, 245 });
	intro.PushBack({ 7680, 245, 384, 245 });
	intro.PushBack({ 8064, 245, 384, 245 });
	intro.PushBack({ 8448, 245, 384, 245 });
	intro.PushBack({ 8832, 245, 384, 245 });
	intro.PushBack({ 9216, 245, 384, 245 });
	intro.PushBack({ 9600, 245, 384, 245 });
	intro.PushBack({ 9984, 245, 384, 245 });
	intro.PushBack({ 10368, 245, 384, 245 });
	intro.PushBack({ 10752, 245, 384, 245 });
	intro.PushBack({ 11136, 245, 384, 245 });
	intro.PushBack({ 11520, 245, 384, 245 });
	intro.PushBack({ 11904, 245, 384, 245 });

	intro.loop = false;
	intro.speed = 0.5f;

	map.PushBack({ 0, 0, 384, 37 });
	map.PushBack({ 384, 0, 384, 37 });
	map.PushBack({ 768, 0, 384, 37 });
	map.PushBack({ 1152, 0, 384, 37 });
	map.PushBack({ 1536, 0, 384, 37 });
	map.PushBack({ 0, 37, 384, 37 });
	map.PushBack({ 384, 37, 384, 37 });
	map.PushBack({ 768, 37, 384, 37 });
	map.PushBack({ 1152, 37, 384, 37 });
	map.PushBack({ 1536, 37, 384, 37 });
	map.PushBack({ 0, 74, 384, 37 });
	map.PushBack({ 384, 74, 384, 37 });
	map.PushBack({ 768, 74, 384, 37 });
	map.PushBack({ 1152, 74, 384, 37 });
	map.PushBack({ 1536, 74, 384, 37 });
	map.PushBack({ 0, 111, 384, 37 });
	map.PushBack({ 384, 111, 384, 37 });
	map.PushBack({ 768, 111, 384, 37 });
	map.PushBack({ 1152, 111, 384, 37 });
	map.PushBack({ 1536, 111, 384, 37 });
	map.PushBack({ 0, 148, 384, 37 });
	map.PushBack({ 384, 148, 384, 37 });
	map.PushBack({ 768, 148, 384, 37 });
	map.PushBack({ 1152, 148, 384, 37 });
	map.PushBack({ 1536, 148, 384, 37 });
	map.PushBack({ 0, 185, 384, 37 });
	map.PushBack({ 384, 185, 384, 37 });
	map.PushBack({ 768, 185, 384, 37 });
	map.PushBack({ 1152, 185, 384, 37 });
	map.PushBack({ 1536, 185, 384, 37 });
	map.speed = 0.1f;
	map.loop = false;

	selectAnim.PushBack({0, 0, 15, 15});
	selectAnim.PushBack({17, 0, 15, 15});
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	mapBool = false;
	sceneOne = true;

	App->player->lifes = 3;

	selectTexture = App->textures->Load("Assets/UI/MapSelection.png");
	mapAnimTexture = App->textures->Load("Assets/UI/IntroDown.png");
	mapTexture = App->textures->Load("Assets/UI/IntroMap.png");
	bgTexture = App->textures->Load("Assets/UI/AnimationPangBalls.png");
	++activeTextures; ++totalTextures;
	intro_1 = App->textures->Load("Assets/UI/Intro_1.png");
	++activeTextures; ++totalTextures;
	intro_2 = App->textures->Load("Assets/UI/Intro_2.png");
	++activeTextures; ++totalTextures;
	intro_3 = App->textures->Load("Assets/UI/Intro_3.png");
	++activeTextures; ++totalTextures;

	char lookupTable1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!✕-:©✕ " };
	introIndex = App->fonts->Load("Assets/UI/Fonts/Pang_font.png", lookupTable1, 1);
	++activeFonts; ++totalFonts;


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
		
		mapBool = true;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		if (sceneOne == true) {
			App->fade->FadeToBlack(this, (Module*)App->scene, 30);
		}

		else if (sceneTwo == true) {
			App->fade->FadeToBlack(this, (Module*)App->scene2, 30);
		}
		else if (sceneThree == true) {
			App->fade->FadeToBlack(this, (Module*)App->scene3, 30);
		}
		else if (sceneFour == true) {
			App->fade->FadeToBlack(this, (Module*)App->scene4, 30);
		}
		else if (sceneFive == true) {
			App->fade->FadeToBlack(this, (Module*)App->scene5, 30);
		}
		else if (sceneSix == true) {
			App->fade->FadeToBlack(this, (Module*)App->scene6, 30);
		}
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN && mapBool == true) {
		if (sceneOne == true) {
			sceneOne = false;
			sceneTwo = true;
		}

		else if (sceneTwo == true) {
			sceneTwo = false;
			sceneThree = true;
		}
		else if (sceneThree == true) {
			sceneThree = false;
			sceneFour = true;
		}
		else if (sceneFour == true) {
			sceneFour = false;
			sceneFive = true;
		}
		else if (sceneFive == true) {
			sceneFive = false;
			sceneSix = true;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN && mapBool == true) {
		if (sceneTwo == true) {
			sceneTwo = false;
			sceneOne = true;
		}
		else if (sceneThree == true) {
			sceneThree = false;
			sceneTwo = true;
		}
		else if (sceneFour == true) {
			sceneFour = false;
			sceneThree = true;
		}
		else if (sceneFive == true) {
			sceneFive = false;
			sceneFour = true;
		}
		else if (sceneSix == true) {
			sceneSix = false;
			sceneFive = true;
		}
	}


	intro.Update();
	if (mapBool == true) {
		map.Update();
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	if (App->input->keys[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN) {
		countdown = 300;
		mapBool = false;
	}
	else {
		if (countdown > 840)
		{
			App->render->Blit(intro_1, 0, 0, NULL);
		}
		else if (countdown > 420 && countdown < 840)
		{
			App->render->Blit(intro_2, 0, 0, NULL);
			//SDL_DestroyTexture(intro_1);
			
		}
		else if (countdown > 0 && countdown < 420)
		{
			App->render->Blit(intro_3, 0, 0, NULL);
			//SDL_DestroyTexture(intro_2);
			
		}
	}

	if (countdown == 0 && mapBool == false)
	{
		//SDL_DestroyTexture(intro_3);
		
		currentAnimation = &intro;
		App->render->Blit(bgTexture, 0, 0, &(intro.GetCurrentFrame()), 0.2f);
		//App->fonts->BlitText(90, 181, introIndex, "©MITCHELL");
		//App->fonts->BlitText(240, 181, introIndex, "1989");

	}
	if (countdown == 1 && mapBool == false) {
		intro.Reset();
		currentAnimation = &intro;
	}
	if (countdown == 140) {
		App->audio->PlayMusic("Assets/Sound/Sounds_Gameplay/Title.ogg", 1.0f);
	}

	if (mapBool == true) {
		currentAnimation = &map;
		App->render->Blit(mapTexture, 0, 0, NULL);
		App->render->Blit(mapAnimTexture, 0, 208, &(map.GetCurrentFrame()), 0.2f);
		if (sceneOne == true) {
			App->render->Blit(selectTexture, 341, 68, &(selectAnim.GetCurrentFrame()), 0.2f);
		}
		else if (sceneTwo == true) {
			App->render->Blit(selectTexture, 301, 68, &(selectAnim.GetCurrentFrame()), 0.2f);
		}
		else if (sceneThree == true) {
			App->render->Blit(selectTexture, 285, 100, &(selectAnim.GetCurrentFrame()), 0.2f);
		}
		else if (sceneFour == true) {
			App->render->Blit(selectTexture, 301, 100, &(selectAnim.GetCurrentFrame()), 0.2f);
		}
		else if (sceneFive == true) {
			App->render->Blit(selectTexture, 329, 161, &(selectAnim.GetCurrentFrame()), 0.2f);
		}
		else if (sceneSix == true) {
			App->render->Blit(selectTexture, 265, 96, &(selectAnim.GetCurrentFrame()), 0.2f);
		}
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	//SDL_DestroyTexture(bgTexture);
	App->textures->Unload(bgTexture);
	--activeTextures; --totalTextures;

	App->textures->Unload(intro_1);
	--activeTextures; --totalTextures;

	App->textures->Unload(intro_2);
	--activeTextures; --totalTextures;

	App->textures->Unload(intro_3);
	--activeTextures; --totalTextures;

	App->fonts->UnLoad(introIndex);
	--activeFonts; --totalFonts;


	/*SDL_DestroyTexture(intro_1);
	SDL_DestroyTexture(intro_2);
	SDL_DestroyTexture(intro_3);*/


	return true;
}