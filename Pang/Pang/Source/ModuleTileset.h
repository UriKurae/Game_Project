#pragma once

#include "Module.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;
class ModuleTileset : public Module
{
public:
	enum class TileType
	{
		NONE = -1,
		EMPTY,
		WALL,
		BREAKABLE,
		UNBREAKABLE,
		STAIRS,
		TOP_STAIRS,
	};

	struct Tile
	{
		TileType id;
		SDL_Rect tileRect;
	};

	ModuleTileset(bool startEnabled);
	~ModuleTileset();

	bool Init() override;

	bool Start() override;

	update_status PostUpdate() override;

	bool CleanUp() override;

	//getter
	Tile getTileLevel(int y, int x);

private:
	SDL_Texture* foreground = nullptr;

	int(*level)[48] = nullptr;
	Tile levelToTile[26][48] = {};
};
