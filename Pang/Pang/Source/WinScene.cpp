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


#include <SDL\include\SDL_scancode.h>

WinScene::WinScene(bool startEnabled) : Module(startEnabled)
{

}

WinScene::~WinScene()
{

}

// Load assets
bool WinScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/UI/PangScene1.png");
	App->audio->PlayMusic("Assets/Sound/Sounds_Gameplay/Level_Complete.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	App->input->Enable();

	return ret;
}

update_status WinScene::Update()
{
	if (App->input->keys[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status WinScene::PostUpdate()
{
	// Draw everything --------------------------------------
	sprintf_s(bonusText, 6, "%d", App->player->timeBonus);

	App->render->Blit(bgTexture, 0, 0, NULL);
	App->fonts->BlitText(168, 145, App->player->uiIndex, "1STAGE");
	App->fonts->BlitText(102, 170, App->player->uiIndex, "TIME BONUS");
	App->fonts->BlitText(214, 170, App->player->uiIndex, bonusText);
	App->fonts->BlitText(263, 170, App->player->uiIndex, "PTS.");
	App->fonts->BlitText(102, 186, App->player->uiIndex, "NEXT EXTEND");
	App->fonts->BlitText(214, 186, App->player->uiIndex, "20000");
	App->fonts->BlitText(263, 186, App->player->uiIndex, "PTS.");

	return update_status::UPDATE_CONTINUE;
}