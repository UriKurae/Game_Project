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

void ModuleTileset::changeTile(iPoint tile)
{
	if (level == level2)
	{
		if (tile.x <= 23) {
			levelToTile[tile.y][20].id = TileType::EMPTY;
			levelToTile[tile.y][21].id = TileType::EMPTY;
			levelToTile[tile.y][22].id = TileType::EMPTY;
			levelToTile[tile.y][23].id = TileType::EMPTY;
			App->scene2->destroyedBlockLeft = true;
		}
		if (tile.x > 23 && tile.x <= 27) {
			levelToTile[tile.y][24].id = TileType::EMPTY;
			levelToTile[tile.y][25].id = TileType::EMPTY;
			levelToTile[tile.y][26].id = TileType::EMPTY;
			levelToTile[tile.y][27].id = TileType::EMPTY;
			App->scene2->destroyedBlockRight = true;
		}
	}

	else if (level == level3)
	{
		if (tile.x >= 8 && tile.x <= 13) {
			levelToTile[tile.y][9].id = TileType::EMPTY;
			levelToTile[tile.y][10].id = TileType::EMPTY;
			levelToTile[tile.y][11].id = TileType::EMPTY;
			levelToTile[tile.y][12].id = TileType::EMPTY;
			App->scene3->destroyedBlockLeft = true;
		}
		if (tile.x >= 21 && tile.x <= 26) {
			levelToTile[tile.y][22].id = TileType::EMPTY;
			levelToTile[tile.y][23].id = TileType::EMPTY;
			levelToTile[tile.y][24].id = TileType::EMPTY;
			levelToTile[tile.y][25].id = TileType::EMPTY;
			if (tile.y == 10) {
				App->scene3->destroyedBlockTop = true;
			}
			else if (tile.y == 16) {
				App->scene3->destroyedBlockBottom = true;
			}
		}
		if (tile.x >= 34 && tile.x <= 39) {
			levelToTile[tile.y][35].id = TileType::EMPTY;
			levelToTile[tile.y][36].id = TileType::EMPTY;
			levelToTile[tile.y][37].id = TileType::EMPTY;
			levelToTile[tile.y][38].id = TileType::EMPTY;
			App->scene3->destroyedBlockRight = true;
		}
	}

	else if (level == level5) {

		if (tile.x == 11 || tile.x == 12 || tile.x == 13) {
			if (tile.y == 9) {
				levelToTile[7][12].id = TileType::EMPTY;
				levelToTile[8][12].id = TileType::EMPTY;
				levelToTile[9][12].id = TileType::EMPTY;
				App->scene5->destroyedBlockTopLeft = true;
			}

			else if (tile.y == 12) {
				levelToTile[10][12].id = TileType::EMPTY;
				levelToTile[11][12].id = TileType::EMPTY;
				levelToTile[12][12].id = TileType::EMPTY;
				App->scene5->destroyedBlockBottomLeft = true;
				
			}
			
		}

		if (tile.x == 23 || tile.x == 24 || tile.x == 25) {
			if (tile.y == 9) {
				levelToTile[7][24].id = TileType::EMPTY;
				levelToTile[8][24].id = TileType::EMPTY;
				levelToTile[9][24].id = TileType::EMPTY;
				App->scene5->destroyedBlockMiddle = true;
		
			}
		}

		if (tile.x == 35 || tile.x == 36 || tile.x == 37) {
			if (tile.y == 9) {
				levelToTile[7][36].id = TileType::EMPTY;
				levelToTile[8][36].id = TileType::EMPTY;
				levelToTile[9][36].id = TileType::EMPTY;
				App->scene5->destroyedBlockTopRight = true;
			}

			else if (tile.y == 12) {
				levelToTile[10][36].id = TileType::EMPTY;
				levelToTile[11][36].id = TileType::EMPTY;
				levelToTile[12][36].id = TileType::EMPTY;
				App->scene5->destroyedBlockBottomRight = true;
				
			}
		}
		
	}

	if (level == level6) {
		if (tile.x >= 22 && tile.x <=25) {
			levelToTile[tile.y][23].id = TileType::EMPTY;
			levelToTile[tile.y][24].id = TileType::EMPTY;
			App->scene6->destroyedBlockCentral = true;
		}
	}
}

bool ModuleTileset::CleanUp()
{
	if (level == level5)
	{
		levelToTile[7][12].id = TileType::BREAKABLE;
		levelToTile[8][12].id = TileType::BREAKABLE;
		levelToTile[9][12].id = TileType::BREAKABLE;
		levelToTile[10][12].id = TileType::BREAKABLE;
		levelToTile[11][12].id = TileType::BREAKABLE;
		levelToTile[12][12].id = TileType::BREAKABLE;
		levelToTile[7][36].id = TileType::BREAKABLE;
		levelToTile[8][36].id = TileType::BREAKABLE;
		levelToTile[9][36].id = TileType::BREAKABLE;
		levelToTile[10][36].id = TileType::BREAKABLE;
		levelToTile[11][36].id = TileType::BREAKABLE;
		levelToTile[12][36].id = TileType::BREAKABLE;
	}
	return true;
}

ModuleTileset::Tile ModuleTileset::getTileLevel(int y, int x)
{
	return levelToTile[y][x]; //SCENE 4 CRASHES BECAUSE TILE LEVEL IS OUTSIDE THE ARRAY, SINCE THE BALL GOES UNDERGROUND
							 //DEIBID KNOWS HOW TO FIX IT.
}

