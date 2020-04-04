#include "Enemy_Balloon.h"


#include "ModuleCollisions.h"


Enemy_Balloon::Enemy_Balloon(int x, int y) : Enemy(x, y)
{
	//texture = App->textures->Load("Assets/Movement/Sprite_Sheet_Movement.png");
}

void Enemy_Balloon::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	Enemy::Update();
}