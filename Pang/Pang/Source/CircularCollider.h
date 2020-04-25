#ifndef _CIRCULAR_COLLIDER_H
#define  _CIRCULAR_COLLIDER_H

#include "SDL/include/SDL_Rect.h"

class Module;


struct Circle
{
	int x, y, radius;
};

struct CircularCollider
{
	enum Type
	{
		NONE = -1,
		
		VERY_SMALL_BALLOON,
		SMALL_BALLOON,
		BIG_BALLOON,
		VERY_BIG_BALLOON,

		MAX
	};

	//Methods
	CircularCollider(Circle circle, Type type, Module* listener = nullptr);
	bool CircularIntersection(const SDL_Rect rect) const;

	void SetPos(int x, int y);

	//Variables
	Circle circ;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;

};



#endif

