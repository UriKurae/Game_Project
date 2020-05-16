#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 23

class Module;
class ModuleFadeToBlack;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneIntro;
class ModuleScene;
class ModuleScene2;
class ModuleScene3;
class ModuleScene4;
class ModuleScene5;
class ModuleScene6;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleRender;
class ModuleHarpoon;
class ModuleHookShot;
class ModuleFonts;
class WinScene;
class ModuleDebugInfo;
class ModulePlatforms;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	SceneIntro* sceneIntro = nullptr;
	ModuleScene* scene = nullptr;
	ModuleScene2* scene2 = nullptr;
	ModuleScene3* scene3 = nullptr;
	ModuleScene4* scene4 = nullptr;
	ModuleScene5* scene5 = nullptr;
	ModuleScene6* scene6 = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleHarpoon* harpoon = nullptr;
	ModuleHookShot* hookShot = nullptr;
	ModulePlatforms* platforms = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;
	ModuleDebugInfo* debugInfo = nullptr;
	WinScene* winScene = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__