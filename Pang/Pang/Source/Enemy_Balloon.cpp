#include "Enemy_Balloon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Balloon::Enemy_Balloon(int x, int y) : Enemy(x,y)
{
	texture = App->textures->Load("Assets/Balloons/Red Balloons.png");

	balloonAnim = 

}

void Enemy_Balloon::Update()
{
	

	Enemy::Update();
}