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

#include <stdio.h>


SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	name = "S INTRO";

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			intro.PushBack({ 384 * j, 245 * i, 384, 245 });
		}
	}

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

	selectAnim.PushBack({0, 0, 16, 16});
	selectAnim.PushBack({17, 0, 16, 16});
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
	stage1 = true;

	countdownMap = 9;

	App->player->lifes = 3;

	selectTexture = App->textures->Load("Assets/UI/MapSelection.png");
	++activeTextures; ++totalTextures;
	mapAnimTexture = App->textures->Load("Assets/UI/IntroDown.png");
	++activeTextures; ++totalTextures;
	mapTexture = App->textures->Load("Assets/UI/IntroMap.png");
	++activeTextures; ++totalTextures;
	bgTexture = App->textures->Load("Assets/UI/AnimationPangBalls.png");
	++activeTextures; ++totalTextures;

	intro_1 = App->textures->Load("Assets/UI/Intro_1.png");
	++activeTextures; ++totalTextures;
	intro_2 = App->textures->Load("Assets/UI/Intro_2.png");
	++activeTextures; ++totalTextures;
	intro_3 = App->textures->Load("Assets/UI/Intro_3.png");
	++activeTextures; ++totalTextures;

	introFx = App->audio->LoadFx("Assets/Sound/Sounds_Gameplay/Title.wav");
	++activeFx; ++totalFx;
	mapFx = App->audio->LoadFx("Assets/Sound/FX/CountDownFx.wav");
	++activeFx; ++totalFx;

	char lookupTable1[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!✕-:©✕ " };
	introIndex = App->fonts->Load("Assets/UI/Fonts/Pang_font.png", lookupTable1, 1);
	++activeFonts; ++totalFonts;

	char mapTable[] = { "9876543210" };
	countdownIndex = App->fonts->Load("Assets/UI/Fonts/MapTimer.png", mapTable, 1);
	++activeFonts; ++totalFonts;


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->input->Enable();
	//App->enemies->Disable();

	return ret;
}

update_status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];
	if (countdown != 0)
	{
		countdown--;
	}

	if (mapBool) { countMap++; }

	if (countMap % 60 == 0 && countdownMap > 0 && mapBool == true) {
		App->audio->PlayFx(mapFx);
		countdownMap--;
	}

	if ((App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || pad.start) && mapBool == false)
	{
		if(countdown == 0)
		mapBool = true;
	}
	
	else if ((App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || pad.a) && mapBool == true || mapBool == true && countdownMap == 0)
	{
		if (stage1 == true) {
			App->fade->FadeToBlack(this, (Module*)App->scene, 30);
		}
		else if (stage2 == true) {
			App->fade->FadeToBlack(this, (Module*)App->scene4, 30);
			
		}
	}

	if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || pad.left) && mapBool) {
		
		if (stage1 == true) {
			stage1 = false;
			stage2 = true;
		}
	}

	if ((App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || pad.right) && mapBool) {
			
		if (stage2 == true) {
			stage2 = false;
			stage1 = true;
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
	else 
	{
		if (countdown > 840)
		{
			App->render->Blit(intro_1, 0, 0, NULL);
		}
		else if (countdown > 420 && countdown < 840)
		{
			App->render->Blit(intro_2, 0, 0, NULL);
		}
		else if (countdown > 0 && countdown < 420)
		{
			App->render->Blit(intro_3, 0, 0, NULL);
		}
	}

	if (countdown == 0 && mapBool == false)
	{	
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
		App->audio->PlayFx(introFx);
	}

	sprintf_s(mapText, 2, "%d", countdownMap);

	if (mapBool == true) {
		currentAnimation = &map;
		App->render->Blit(mapTexture, 0, 0, NULL);
		App->render->Blit(mapAnimTexture, 0, 208, &(map.GetCurrentFrame()), 0.2f);
		App->fonts->BlitText(260, 31, countdownIndex, mapText);
		if (stage1 == true) {
			App->render->Blit(selectTexture, 340, 68, &(selectAnim.GetCurrentFrame()), 0.2f);
		}
		else if (stage2 == true) {
			App->render->Blit(selectTexture, 300, 68, &(selectAnim.GetCurrentFrame()), 0.2f);
		}
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	activeTextures = activeColliders = activeFonts = activeFx = 0;

	App->textures->Unload(bgTexture);
	--activeTextures; --totalTextures;

	App->textures->Unload(selectTexture);
	--activeTextures; --totalTextures;

	App->textures->Unload(mapTexture);
	--activeTextures; --totalTextures;

	App->textures->Unload(mapAnimTexture);
	--activeTextures; --totalTextures;

	App->textures->Unload(intro_1);
	--activeTextures; --totalTextures;

	App->textures->Unload(intro_2);
	--activeTextures; --totalTextures;

	App->textures->Unload(intro_3);
	--activeTextures; --totalTextures;

	App->fonts->UnLoad(introIndex);
	--activeFonts; --totalFonts;

	App->fonts->UnLoad(countdownIndex);
	--activeFonts; --totalFonts;

	App->audio->UnloadFx(introFx);
	--activeFx; --totalFx;

	App->audio->UnloadFx(mapFx);
	--activeFx; --totalFx;

	return true;
}