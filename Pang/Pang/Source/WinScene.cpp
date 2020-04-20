#include "WinScene.h"

#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"

#include "ModuleCollisions.h"


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
	//App->audio->PlayMusic("Assets/Sound/Sounds_Gameplay/Title.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

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
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}