#ifndef BADGUY_H
#define BADGUY_H
#include "Element3D.h"


class BadGuy : public Element3D
{

	public:
	BadGuy();
	BadGuy(float life);
	virtual void draw ();

	float mLife;
	bool isAlive();
};








#endif