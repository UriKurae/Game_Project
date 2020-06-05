#pragma once

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class ModuleScene2 : public Module
{
public: 
	
	ModuleScene2(bool startEnabled);

	~ModuleScene2();


		// Called when the module is activated
		// Loads the necessary textures for the map background
		bool Start() override;

		update_status Update() override;

		// Called at the end of the application loop.
		// Performs the render call of all the parts of the scene's background
		update_status PostUpdate() override;

		bool CleanUp();

	public:

		uint countDownToFade = 180;
		int toFade = 5;

		bool destroyedBlockLeft = false;
		bool destroyedBlockRight = false;

		// The background sprite sheet loaded into an SDL_Texture
		SDL_Texture* bgTexture = nullptr;

		//The foreground sprite sheet loaded into an SDL_Texture
		SDL_Texture* fgTexture = nullptr;

		Animation block;

		Animation blockDestroy;

		Animation* currentAnim = nullptr;

		//Foregrounds when dying
		SDL_Texture* deathTexture1 = nullptr;
		SDL_Texture* deathTexture2 = nullptr;

		// The sprite rectangle for the ground

		Collider* collider = nullptr;
		Collider* rightWall = nullptr;
		Collider* leftWall = nullptr;
		Collider* upperWall = nullptr;
		Collider* lowerWall = nullptr;

		//Colliders for each block platform
		Collider* leftPlatform = nullptr;
		Collider* rightPlatform = nullptr;

		uint balloonsOnScene;

		//Change the music
		bool musicBool1 = false;
		bool musicBool2 = false;
	};

