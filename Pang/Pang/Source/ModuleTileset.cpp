#include "ModuleTileset.h"

#include "Globals.h"
#include "Application.h"

#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleScene3.h"
#include "ModuleScene4.h"

#include "Tileset.h"

ModuleTileset::ModuleTileset(bool startEnabled) : Module(startEnabled)
{
	name = "TILESET";
}

ModuleTileset::~ModuleTileset()
{

}

bool ModuleTileset::Init()
{
	return true;
}

bool ModuleTileset::Start()
{
	if (App->scene->IsEnabled() == true)
	{
		level = level1;
		foreground = App->scene->fgTexture;
	}
	else if (App->scene2->IsEnabled() == true)
	{
		level = level2;
		foreground = App->scene2->fgTexture;
	}
	else { return false; }


	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < 48; ++j)
		{
			switch (level[i][j])
			{
			case 0:
				levelToTile[i][j] =
				{
					TileType::EMPTY,
					{i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,TILE_SIZE}
				};
				break;

			case 1:
				levelToTile[i][j] =
				{
					TileType::WALL,
					{i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,TILE_SIZE}
				};
				break;

			case 2:
				levelToTile[i][j] =
				{
					TileType::BREAKABLE,
					{i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,TILE_SIZE}
				};
				break;

			case 3:
				levelToTile[i][j] =
				{
					TileType::UNBREAKABLE,
					{i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,TILE_SIZE}
				};
				break;

			case 4: 
				levelToTile[i][j] =
				{
					TileType::STAIRS,
					{i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,TILE_SIZE}
				};
				break;
			}
		}
	}

	return false;
}

update_status ModuleTileset::PostUpdate()
{
	for (int i = 0; i < 26; ++i)//filas
	{
		for (int j = 0; j < 48; ++j)//columnas
		{
			if (level[i][j] > 1)
			{
				SDL_Rect tileRec = { i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE,TILE_SIZE };
				App->render->Blit(foreground, i * TILE_SIZE, j * TILE_SIZE, &tileRec, 0, false);
			}
		}
	}


	return update_status::UPDATE_CONTINUE;
}

bool ModuleTileset::CleanUp()
{
	return true;
}

ModuleTileset::Tile ModuleTileset::getTileLevel(int y, int x)
{
	return levelToTile[y][x];
}

