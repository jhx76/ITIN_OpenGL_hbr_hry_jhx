#include "Element3D.h"

#include "Node3D.h"
#include "AppelsOpenGL.h"

int Element3D::mCounter = 0;
//--------------------------------------//
Element3D::Element3D()
	: mNode(new Node3D()), mVitesse(), mVitesseRotation()
{
	mId = mCounter;
	++mCounter;
}
//--------------------------------------//
Element3D::~Element3D() {
	delete mNode;
	mNode = NULL;
}
//--------------------------------------//
void Element3D::draw()
{
	// 1/ recuperer la matrice courante.
	// 2/ recuperer la matrice dans le repere parent.
	// 3/ multiplier les deux, charger le resultat dans opengl
	// 4/ dessiner l'element (par exemple en appelant une fonction de AppelsOpenGL)
	// 5/ revenir a l'invariant (c'est a dire a l'etat d'entree dans la fonction)
	auto lBeginMatrix = AppelsOpenGL::obtenirLaMatriceModelViewCourante();
	glMatrixMode(GL_MODELVIEW);
	auto lNewMatrix =  lBeginMatrix* mNode->getTransformation_ParentSpace();
	glLoadMatrixf( &lNewMatrix[0][0]);
	AppelsOpenGL::dessinerPyramide();
	glLoadMatrixf( &lBeginMatrix[0][0]);
}
//--------------------------------------//
void Element3D::update(float dt)
{	// ici on peut mettre a jour des informations sur l'element:
	// sa position, grace a la vitesse notamment.
	mNode->mPosition_ParentSpace += (mVitesse*dt);
	//sa position, grace a la vitesse de rotation.
	mNode->mRotationXYZ_ParentSpace +=(mVitesseRotation *dt);
}
//--------------------------------------//
