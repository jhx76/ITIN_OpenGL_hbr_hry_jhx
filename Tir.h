#ifndef TIR_H
#define TIR_H
#include "Element3D.h"
#include "Node3D.h"
#include <SFML/Graphics/Sprite.hpp>

class Tir: public Element3D
{

public:
	Tir();
	virtual void draw ();
	bool isOutOfGame (sf::Window& pWindow);
	//virtual void update(float dt);	
	/// positionner le tir
	//void setPosition(float x, float y);
	//void setPosition(sf::Vector2f v);
	//attribut
	//sf::Sprite mSprite;
	//glm::vec3 mVitesse;
	//glm::vec3 mPosition;
		
};

#endif