#include "ModuleDebugInfo.h"

#include "Application.h"
#include "Globals.h"

#include "ModuleFonts.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModuleTextures.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#include <stdio.h>

ModuleDebugInfo::ModuleDebugInfo(bool startEnabled) : Module(startEnabled)
{
	name = "DEBUG";
}

ModuleDebugInfo::~ModuleDebugInfo()
{

}

bool ModuleDebugInfo::Start()
{
	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!✕-:©✕ " };
	debugFont = App->fonts->Load("Assets/UI/Fonts/Pang_font.png", lookupTable, 1);

	return true;
}

bool ModuleDebugInfo::CleanUp()
{
	//TODO: Unload debug font!

	return true;
}

update_status ModuleDebugInfo::Update()
{
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		debugMemLeaks = !debugMemLeaks;

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_DOWN)
		inspectedModule = (Module*)App->player;

	if (App->input->keys[SDL_SCANCODE_F4] == KEY_DOWN)
		inspectedModule = (Module*)App->sceneIntro;

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_DOWN)
		inspectedModule = (Module*)App->scene;

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_DOWN)
		inspectedModule = (Module*)App->harpoon;

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_DOWN)
		inspectedModule = (Module*)App->winScene;

	if (App->input->keys[SDL_SCANCODE_F8] == KEY_DOWN)
		inspectedModule = nullptr;


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleDebugInfo::PostUpdate()
{
	if (!debugMemLeaks)
	{
		App->fonts->BlitText(10, 1, debugFont, "PRESS F2 TO OPEN MEM LEAKS DEBUG INFO");
	}
	else
	{
		App->fonts->BlitText(10, 1, debugFont, "PRESS F2 TO CLOSE MEM LEAKS DEBUG INFO");

		App->fonts->BlitText(10, 20, debugFont, "TOTAL LOADED RESOURCES");

		// Display total textures loaded
		sprintf_s(debugText, 150, "TEXTURES  %i", App->textures->GetTexturesCount());
		App->fonts->BlitText(20, 35, debugFont, debugText);

		// Display total audio files loaded
		sprintf_s(debugText, 150, "AUDIO FX  %i", App->audio->GetFxCount());
		App->fonts->BlitText(20, 50, debugFont, debugText);

		// Display total font files loaded
		sprintf_s(debugText, 150, "FONTS     %i", App->fonts->GetFontsCount());
		App->fonts->BlitText(20, 65, debugFont, debugText);

		// Display total colliders loaded
		sprintf_s(debugText, 150, "COLLIDERS %i", App->collisions->GetColliderCount());
		App->fonts->BlitText(20, 80, debugFont, debugText);

		// Display total particles loaded
		sprintf_s(debugText, 150, "PARTICLES %i", App->particles->GetParticlesCount());
		App->fonts->BlitText(20, 95, debugFont, debugText);

		App->fonts->BlitText(10, 120, debugFont, "PRESS F3 TO F6 TO DISPLAY SPECIFIC MODULES");

		if (inspectedModule != nullptr)
		{
			DrawModuleResources(inspectedModule);
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleDebugInfo::DrawModuleResources(Module* module)
{
	sprintf_s(debugText, 150, "MODULE %s", module->name);
	App->fonts->BlitText(20, 140, debugFont, debugText);

	sprintf_s(debugText, 150, "ACTIVE  TOTAL");
	App->fonts->BlitText(155, 140, debugFont, debugText);

	sprintf_s(debugText, 150, "TEXTURES          %i      %i", module->activeTextures, module->totalTextures);
	App->fonts->BlitText(30, 155, debugFont, debugText);

	sprintf_s(debugText, 150, "AUDIO FX          %i      %i", module->activeFx, module->totalFx);
	App->fonts->BlitText(30, 170, debugFont, debugText);

	sprintf_s(debugText, 150, "FONTS             %i      %i", module->activeFonts, module->totalFonts);
	App->fonts->BlitText(30, 185, debugFont, debugText);

	sprintf_s(debugText, 150, "COLLIDERS         %i      %i", module->activeColliders, module->totalColliders);
	App->fonts->BlitText(30, 200, debugFont, debugText);
}