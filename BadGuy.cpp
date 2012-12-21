#include "BadGuy.h"

BadGuy::BadGuy() : Element3D()
{
	mLife = 0;
}

BadGuy::BadGuy(float life) : Element3D()
{
	mLife = life;
}

void BadGuy::draw()
{

}

bool BadGuy::isAlive()
{
	return (mLife > 0);
}