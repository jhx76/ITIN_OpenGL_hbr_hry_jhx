#ifndef NODE3D_H
#define NODE3D_H
#include "CommonDefines.h"
#include <glm/glm.hpp>
#include <vector>

/// represente le necessaire pour positionner un element dans la scene.
class Node3D
{
public:
	// Transformation de cet element dans le repere de son parent.
	glm::vec3 mPosition_ParentSpace;
	glm::vec3 mRotationXYZ_ParentSpace;

public:
	Node3D();

	// libere la memoire.
	~Node3D();

	// calcule la transformation de cet element dans le repere de son parent.
	glm::mat4x4 getTransformation_ParentSpace();

	// si l'objet est trop loin.
	bool isOutOfGame(sf::Window& pWindow);

private:
	// empeche la recopie d'objet.
	explicit Node3D(const Node3D&);
	Node3D& operator=(const Node3D&);
};

#endif

