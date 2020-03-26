#pragma once

#include "Module.h"
#include "External_Libraries/SDL/include/SDL_Rect.h"

struct SDL_Texture;
struct SDL_Renderer;

class ModuleRender : public Module
{
public:
	//Constructor
	ModuleRender();

	//Destructor
	~ModuleRender();

	// Called on application start.
	// Creates the rendering context using the program's window.
	bool Init() override;

	// Called at the beginning of the application loop
	// Clears the rendering context to a background color
	update_status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles camera movement
	update_status Update() override;

	// Called at the end of the application loop.
	// Displays a rectangle in the rendering context
	// Updates the screen with the rendered content
	update_status PostUpdate() override;

	// Called on application exit.
	// Destroys the rendering context
	bool CleanUp() override;

	// Prints a texture to the rendering context.
	// Param texture	- A valid SDL Texture, validation checks are not performed
	// Param x,y		- Position x,y in the screen (upper left axis)
	// Param section	- The portion of the texture we want to copy. nullptr for the entire texture
	// Param speed		- The amount of effect that is applied to the sprite depending on the camera
	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section = nullptr, float speed = 1.0f);

public:

};