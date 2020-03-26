#pragma once

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene();

	//Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate();

public:

};