#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER,
		PLAYER_SHOT,
		ENEMY,
		/*VERY_SMALL_BALLOON,
		SMALL_BALLOON,
		BIG_BALLOON,
		VERY_BIG_BALLOON,*/

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
};


#endif // !__COLLIDER_H__

