#include "BadGuy.h"

BadGuy::BadGuy() : Element3D()
{
	mLife = 0;
}

BadGuy::BadGuy(float life) : Element3D()
{
	mLife = life;
	mVitesse.x = -100;
}

void BadGuy::draw()
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
	//AppelsOpenGL::dessinerTir();
	AppelsOpenGL::dessinerEnnemi();
	glLoadMatrixf( &lBeginMatrix[0][0]);
}

bool BadGuy::isAlive()
{
	return (mLife > 0);
}