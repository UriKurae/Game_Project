#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"

#include "Enemy.h"

#include "Enemy_Balloon.h"

#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "ModuleScene3.h"
#include "ModuleScene4.h"
#include "ModuleScene5.h"
#include "ModuleScene6.h"

#include "SDL/include/SDL.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	name = "ENEMIES";

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/Balloons/Balloons.png");


	return true;
}

update_status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	SDL_DestroyTexture(texture);

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		//App->enemies[i].touchWall = false;

		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			//if (App->player->scene1 == true) 
			//{
			//	App->scene->balloonsOnScene++;
			//}
			//else if (App->player->scene2 == true) 
			//{
			//	App->scene2->balloonsOnScene++;
			//}
			//else if (App->player->scene3 == true)
			//{
			//	App->scene3->balloonsOnScene++;
			//}
			//else if (App->player->scene4 == true)
			//{
			//	App->scene4->balloonsOnScene++;
			//}
			//else if (App->player->scene5 == true)
			//{
			//	App->scene5->balloonsOnScene++;
			//}
			//else if (App->player->scene6 == true)
			//{
			//	App->scene6->balloonsOnScene++;
			//}

			App->enemies->balloon.balloonsOnScene++;

			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				
				case ENEMY_TYPE::VERYBIGBALLOON:
					enemies[i] = new Enemy_Balloon(info.x, info.y, ENEMY_TYPE::VERYBIGBALLOON);
					break;
				case ENEMY_TYPE::VERYBIGBALLOON2:
					enemies[i] = new Enemy_Balloon(info.x, info.y, ENEMY_TYPE::VERYBIGBALLOON2);
					break;
				case ENEMY_TYPE::BIGBALLOON:
					enemies[i] = new Enemy_Balloon(info.x, info.y, ENEMY_TYPE::BIGBALLOON);
					break;
				case ENEMY_TYPE::BIGBALLOON2:
					enemies[i] = new Enemy_Balloon(info.x, info.y, ENEMY_TYPE::BIGBALLOON2);
					break;
				case ENEMY_TYPE::SMALLBALLOON:
					enemies[i] = new Enemy_Balloon(info.x, info.y, ENEMY_TYPE::SMALLBALLOON);
					break;
				case ENEMY_TYPE::SMALLBALLOON2:
					enemies[i] = new Enemy_Balloon(info.x, info.y, ENEMY_TYPE::SMALLBALLOON2);
					break;
				case ENEMY_TYPE::VERYSMALLBALLOON:
					enemies[i] = new Enemy_Balloon(info.x, info.y, ENEMY_TYPE::VERYSMALLBALLOON);
					break;
				case ENEMY_TYPE::VERYSMALLBALLOON2:
					enemies[i] = new Enemy_Balloon(info.x, info.y, ENEMY_TYPE::VERYSMALLBALLOON2);
					break;
			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}


void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision

			if (c2->type != Collider::Type::WALL && c2->type != Collider::Type::BREAKABLE_BLOCK) {
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}