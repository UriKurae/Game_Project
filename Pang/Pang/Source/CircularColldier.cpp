#include "CircularCollider.h"

CircularCollider::CircularCollider(Circle circle, Type type, Module* listener) : circ(circle), type(type), listener(listener)
{

}

double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;

	return deltaX * deltaX + deltaY * deltaY;
}

bool CircularCollider::CircularIntersection(const SDL_Rect rect) const
{
	int cX, cY;

	if (circ.x < rect.x)
	{
		cX = rect.x;
	}

	else if (circ.x > rect.x + rect.w)
	{
		cX = rect.x + rect.w;
	}

	else
	{
		cX = circ.x;
	}

	if (circ.y < rect.y)
	{
		cY = rect.y;
	}

	else if (circ.y > rect.y + rect.h)
	{
		cY = rect.y + rect.h;
	}

	else
	{
		cY = circ.y;
	}

	//If collision return true
	if (distanceSquared(circ.x, circ.y, cX, cY) < circ.radius * circ.radius)
	{
		return true;
	}
	//If not return false
	else
	{
		return false;
	}

}

void CircularCollider::SetPos(int x, int y)
{
	circ.x = x;
	circ.y = y;
}


