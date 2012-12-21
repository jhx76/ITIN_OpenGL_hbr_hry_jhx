#ifndef BADGUY_H
#define BADGUY_H
#include "Element3D.h"
#include "Node3D.h"
#include "AppelsOpenGL.h"


class BadGuy : public Element3D
{

public:
	BadGuy();
	BadGuy(float life);
	virtual void draw ();
	bool isOutOfGame(sf::Window& pWindow) { return this->mNode->isOutOfGame(pWindow); }


	float mLife;
	bool isAlive();
};








#endif