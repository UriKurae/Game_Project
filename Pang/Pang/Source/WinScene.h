#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class WinScene : public Module
{
public:
	//Constructor
	WinScene(bool startEnabled);

	//Destructor
	~WinScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	bool CleanUp() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* winTexture1 = nullptr;
	SDL_Texture* winTexture245 = nullptr;
	SDL_Texture* winScene3 = nullptr;

	Animation winAnim;
	Animation winAnim2;
	Animation winAnim3;
	Animation winAnim4;
	Animation winAnim5;
	Animation winAnim6;

	Animation* currentAnimation = nullptr;

	char bonusText[5] = { "\0" };
	int winIndex;

	uint winFx = 0;
	uint planeFx = 0;

	int timeScene3;
	int countScene3;

	int winCountdown = 340;

	int count = 0;
};

#endif
