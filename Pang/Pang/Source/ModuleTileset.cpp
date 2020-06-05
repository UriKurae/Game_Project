#include "ModuleTileset.h"

#include "Globals.h"
#include "Application.h"

#include "ModuleCollisions.h"
#include "ModuleRender.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleScene3.h"
#include "ModuleScene4.h"
#include "ModuleScene5.h"
#include "ModuleScene6.h"

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

	}
	else if (App->scene2->IsEnabled() == true)
	{
		level = level2;

	}
	else if (App->scene3-> IsEnabled() == true)
	{
		level = level3;

	}
	else if (App->scene4->IsEnabled() == true)
	{
		level = level4;
	}
	else if (App->scene5->IsEnabled() == true)
	{
		level = level5;
	}
	else if (App->scene6->IsEnabled() == true)
	{
		level = level6;
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

			case 5:
				levelToTile[i][j] =
				{
					TileType::TOP_STAIRS,
					{i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE}
				};
				break;
			}
		}
	}

	return false;
}

bool ModuleTileset::CleanUp()
{
	return true;
}

ModuleTileset::Tile ModuleTileset::getTileLevel(int y, int x)
{
	return levelToTile[y][x]; //SCENE 4 CRASHES BECAUSE TILE LEVEL IS OUTSIDE THE ARRAY, SINCE THE BALL GOES UNDERGROUND
							 //DEIBID KNOWS HOW TO FIX IT.
}

