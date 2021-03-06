#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	//Constructor
	SceneIntro(bool startEnabled);

	//Destructor
	~SceneIntro();

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
	SDL_Texture* bgTexture = nullptr;
	Animation intro;
	Animation map;
	Animation selectAnim;
	Animation* currentAnimation = nullptr;
	SDL_Texture* intro_1 = nullptr;
	SDL_Texture* intro_2 = nullptr;
	SDL_Texture* intro_3 = nullptr;
	SDL_Texture* mapTexture = nullptr;
	SDL_Texture* mapAnimTexture = nullptr;
	SDL_Texture* selectTexture = nullptr;

	uint introFx = 0;
	uint mapFx = 0;

	int countdown = 1260;
	int countMap = 0;
	int countdownMap = 9;

	bool mapBool = false;
	bool stage1 = false;
	bool stage2 = false;


	int introIndex;
	int countdownIndex;
	char scoreText[10] = { "\0" };
	char mapText[2] = { "\0" };

};

#endif