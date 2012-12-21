#ifndef ELEMENT3D_H
#define ELEMENT3D_H

#include <glm/glm.hpp>

class Node3D;

class Element3D
{
public:
	/// en parametre : la node sur laquelle l'element 
	/// doit s'accrocher
	Element3D();

	/// ce destructeur
	virtual ~Element3D();
	virtual void draw();
	virtual void update(float dt);

	/// vitesse de notre element 3D.
	glm::vec3 mVitesse;

	///vitesse de rotation element 3D
	glm::vec3 mVitesseRotation;

	/// la node parent de notre element
	/// pour le positionner.
	///
	/// aggregation.
	Node3D* mNode;

private:
	int mId;
	static int mCounter;

};

#endif

