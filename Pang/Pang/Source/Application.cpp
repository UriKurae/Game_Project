#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleScene3.h"
#include "ModuleScene4.h"
#include "ModuleScene5.h"
#include "ModuleScene6.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "IntroScene.h"
#include "ModuleHarpoon_Shot.h"
#include "ModuleHarpoon_HookShot.h"
#include "ModuleGunShot.h"
#include "ModuleHarpoon_DoubleShot.h"
#include "ModuleBoosters.h"
#include "ModuleFadeToBlack.h"
#include "ModuleDebugInfo.h"
#include "Enemy_Balloon.h"
#include "ModuleFonts.h"
#include "WinScene.h"
#include "ModulePlatforms.h"
#include "ModuleTileset.h"


Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = sceneIntro = new SceneIntro(true);
	modules[5] = scene = new ModuleScene(false);
	modules[6] = scene2 = new ModuleScene2(false);
	modules[7] = scene3 = new ModuleScene3(false);
	modules[8] = scene4 = new ModuleScene4(false);
	modules[9] = scene5 = new ModuleScene5(false);
	modules[10] = scene6 = new ModuleScene6(false);

	modules[11] = player = new ModulePlayer(false);
	modules[12] = platforms = new ModulePlatforms(false);
	modules[13] = harpoon = new ModuleHarpoon(false);
	modules[14] = hookShot = new ModuleHookShot(false);
	modules[15] = gunShot = new ModuleGunShot(false);
	modules[16] = doubleShot = new ModuleDoubleShot(false);
	modules[17] = particles = new ModuleParticles(true);
	modules[18] = enemies = new ModuleEnemies(false);
	modules[19] = boosters = new ModuleBoosters(false);
	modules[20] = tileset = new ModuleTileset(false);

	modules[21] = collisions = new ModuleCollisions(true);
	modules[22] = fade = new ModuleFadeToBlack(true);
	modules[23] = fonts = new ModuleFonts(true);
	modules[24] = debugInfo = new ModuleDebugInfo(true);
	modules[25] = winScene = new WinScene(false);

	modules[26] = render = new ModuleRender(true);
	
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	//By now we will consider that all modules are always active
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;
	return ret;
}
