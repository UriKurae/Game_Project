#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene(bool startEnabled);

	//Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	bool CleanUp();

public:
	
	// The background sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;

	//The foreground sprite sheet loaded into an SDL_Texture
	SDL_Texture* fgTexture = nullptr;
	
	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;

	SDL_Texture* balloon = nullptr;
	//Enemy_Balloon* enemy1 = nullptr; Esto da errores 

	Collider* collider = nullptr;
	Collider* rightWall = nullptr;
	Collider* leftWall = nullptr;
	Collider* upperWall = nullptr;
	Collider* lowerWall = nullptr;

	int deadballoons = 0;
	int count = 0;
};

#endif