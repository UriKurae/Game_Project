#pragma once

#include "Enemy.h"
#include "Path.h"

class Enemy_Mech : public Enemy
{
public:

	Enemy_Mech(int x, int y);

	void Update() override;

private: 
	Animation forw;
	Animation backw;

	Path path;

	Step forwards;
	Step backwards;

};
