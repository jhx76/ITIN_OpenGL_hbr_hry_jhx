#include "Node3D.h"
#include <SFML/System/Randomizer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
//==================================================================//
Node3D::Node3D():mPosition_ParentSpace(),mRotationXYZ_ParentSpace()
{

}
//==================================================================//
Node3D::~Node3D()
{

}
//==================================================================//
glm::mat4x4 Node3D::getTransformation_ParentSpace()
{
	glm::mat4x4 lCurrent;
	lCurrent = glm::translate(lCurrent, mPosition_ParentSpace );
	lCurrent = glm::rotate(lCurrent, mRotationXYZ_ParentSpace.x, glm::vec3(1,0,0) );
	lCurrent = glm::rotate(lCurrent, mRotationXYZ_ParentSpace.y, glm::vec3(0,1,0) );
	lCurrent = glm::rotate(lCurrent, mRotationXYZ_ParentSpace.z, glm::vec3(0,0,1) );

	return lCurrent;
}
//==================================================================//
bool Node3D::isOutOfGame (sf::Window& pWindow)
{
	int maxH = pWindow.GetHeight() +15;
	int maxW = pWindow.GetWidth() +15;
	int minH = -15;
	int minW = -15;

	return (mPosition_ParentSpace.x >= maxW
		|| mPosition_ParentSpace.x <= minW 
		|| mPosition_ParentSpace.y >= maxH
		|| mPosition_ParentSpace.y <= minH);

}
//==================================================================//
