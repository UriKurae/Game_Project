#include "WinScene.h"

#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include <stdio.h>

#include "SDL\include\SDL.h"

#include <SDL\include\SDL_scancode.h>

WinScene::WinScene(bool startEnabled) : Module(startEnabled)
{
	name = "WIN SCENE";

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			winAnim.PushBack({ 192 * j, 98 * i, 192, 98 });
		}
	}
	winAnim.speed = 0.1f;
	winAnim.loop = true;


	winAnim2.PushBack({ 384, 98, 192, 98 });
	winAnim2.speed = 0.1f;
	winAnim2.loop = true;


	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			winAnim3.PushBack({ j * 384, i * 245, 384, 245 });
		}
	}
	winAnim3.speed = 0.6f;
	winAnim3.loop = false;



	winAnim4.PushBack({ 0, 0, 192, 98 });
	winAnim4.PushBack({ 192, 0, 192, 98 });
	winAnim4.PushBack({ 0, 98, 192, 98 });
	winAnim4.PushBack({ 192, 98, 192, 98 });
	winAnim4.speed = 0.1f;
	winAnim4.loop = true;

	winAnim5.PushBack({ 384, 0, 192, 98 });
	winAnim5.speed = 0.1f;
	winAnim5.loop = true;
}

WinScene::~WinScene()
{

}

// Load assets
bool WinScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	winTexture1 = App->textures->Load("Assets/UI/WinScene1.png");
	++activeTextures; ++totalTextures;
	winTexture245 = App->textures->Load("Assets/UI/WinScene245.png");
	++activeTextures; ++totalTextures;
	winFx = App->audio->LoadFx("Assets/Sound/Sounds_Gameplay/Level_Complete.ogg");
	++activeFx; ++totalFx;

	if (App->player->scene3 == true) {
		planeFx = App->audio->LoadFx("Assets/Sound/Sounds_Gameplay/PlaneFx.ogg");
		++activeFx; ++totalFx;
	}

	winScene3 = App->textures->Load("Assets/UI/AnimPlaneScene3.png");
	++activeTextures; ++totalTextures;

	char lookupTable2[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!✕-:©✕ " };
	winIndex = App->fonts->Load("Assets/UI/Fonts/Pang_font.png", lookupTable2, 1);
	++activeFonts; ++totalFx;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	countScene3 = 0;
	timeScene3 = 2;
	
	App->player->score += App->player->timeBonus;

	App->input->Enable();
	
	count = 0;

	return ret;
}

update_status WinScene::Update()
{
	GamePad& pad = App->input->pads[0];
	if ((App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || pad.a) && App->player->scene1 == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene2, 90);
	}

	else if ((App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || pad.a) && App->player->scene2 == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene3, 90);
	}

	else if ((App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || pad.a) && App->player->scene4 == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene5, 90);
	}

	else if ((App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || pad.a) && App->player->scene5 == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene6, 90);
	}

	else if ((App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || pad.a) && App->player->scene6 == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	
	if (App->player->scene3 == true) {
		countScene3++;
	}


	if (countScene3 % 60 == 0) {
		timeScene3--;
	}

	if (timeScene3 == 0) {
		App->fade->FadeToBlack(this, (Module*)App->scene4, 90);
	}

	winAnim.Update();
	winAnim3.Update();
	winAnim4.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status WinScene::PostUpdate()
{
	// Draw everything --------------------------------------
	sprintf_s(bonusText, 6, "%d", App->player->timeBonus);
	if (App->player->scene1 == true) {
		App->render->Blit(winTexture1, 97, 32, &(winAnim.GetCurrentFrame()), 0.2f);
		App->fonts->BlitText(168, 145, winIndex, "1STAGE");
		if (count == 0)
		{
			App->audio->PlayFx(winFx);
			count++;
		}
	}
	else if (App->player->scene2 == true) {
		App->render->Blit(winTexture245, 97, 32, &(winAnim2.GetCurrentFrame()), 0.2f);
		App->fonts->BlitText(168, 145, winIndex, "2STAGE");
		if (count == 0)
		{
			App->audio->PlayFx(winFx);
			count++;
		}
	}
	else if (App->player->scene3 == true) {
		App->render->Blit(winScene3, 0, 0, &(winAnim3.GetCurrentFrame()), 0.2f);
		if (count == 0)
		{
			App->audio->PlayFx(planeFx);
			count++;
		}
	}
	else if (App->player->scene4 == true) {
		App->render->Blit(winTexture245, 97, 32, &(winAnim4.GetCurrentFrame()), 0.2f);
		App->fonts->BlitText(168, 145, winIndex, "4STAGE");
		if (count == 0)
		{
			App->audio->PlayFx(winFx);
			count++;
		}
	}
	else if (App->player->scene5 == true) {
		App->render->Blit(winTexture245, 97, 32, &(winAnim5.GetCurrentFrame()), 0.2f);
		App->fonts->BlitText(168, 145, winIndex, "5STAGE");
		if (count == 0)
		{
			App->audio->PlayFx(winFx);
			count++;
		}
	}
	else if (App->player->scene6 == true) {
		App->render->Blit(winScene3, 0, 0, &(winAnim3.GetCurrentFrame()), 0.2f);
	}

	if (App->player->scene1 == true || App->player->scene2 == true || App->player->scene4 == true || App->player->scene5 == true) {
		App->fonts->BlitText(102, 170, winIndex, "TIME BONUS");
		App->fonts->BlitText(214, 170, winIndex, bonusText);
		App->fonts->BlitText(263, 170, winIndex, "PTS.");
		App->fonts->BlitText(102, 186, winIndex, "NEXT EXTEND");
		App->fonts->BlitText(214, 186, winIndex, "20000");
		App->fonts->BlitText(263, 186, winIndex, "PTS.");
	}

	return update_status::UPDATE_CONTINUE;
}

bool WinScene::CleanUp()
{
	activeFx = activeColliders = activeFonts = activeTextures = 0;

	App->textures->Unload(winTexture1);
	--totalTextures;
	App->textures->Unload(winTexture245);
	--totalTextures;
	App->textures->Unload(winScene3);
	--totalTextures;
	
	App->fonts->UnLoad(winIndex);
	--totalFonts;
	App->audio->UnloadFx(winFx);
	--totalFx;
	if (App->player->scene3 == true) {
		App->audio->UnloadFx(planeFx);
		--totalFx;
	}

	winAnim.Reset();
	winAnim2.Reset();
	winAnim3.Reset();
	winAnim4.Reset();
	winAnim5.Reset();
	winAnim6.Reset();


	return true;
}