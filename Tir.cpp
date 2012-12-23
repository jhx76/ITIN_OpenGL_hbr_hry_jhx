#include "Tir.h"
#include "AppelsOpenGL.h"

Tir::Tir() : Element3D() 
{ 
	mVitesse.x = 1.8f;
	/* nothing todo*/
}

void Tir::draw()
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
	glm::vec4 vecDessin;
	vecDessin.x = mNode->mPosition_ParentSpace.x;
	vecDessin.y = mNode->mPosition_ParentSpace.y;
	vecDessin.z = mNode->mPosition_ParentSpace.z;
	//AppelsOpenGL::dessinerTir(vecDessin);
	AppelsOpenGL::dessinerTir(vecDessin);
	glLoadMatrixf( &lBeginMatrix[0][0]);
}

/*
void Tir::update(float dt)
{
	mNode->mPosition_ParentSpace += (dt*mVitesse);
	//sf::Vector2f tmp = sf::Vector2f(mNode->mPosition_ParentSpace.x, mNode->mPosition_ParentSpace.y);
	//mSprite.SetPosition( tmp );
};
*/

bool Tir::isOutOfGame (sf::Window& pWindow) {
	/*
	int maxH = pWindow.GetHeight() +15;
	int maxW = pWindow.GetWidth() +15;
	int minH = -15;
	int minW = -15;
	return (mNode->mPosition_ParentSpace.x >= maxW
		|| mNode->mPosition_ParentSpace.x <= minW 
		|| mNode->mPosition_ParentSpace.y >= maxH
		|| mNode->mPosition_ParentSpace.y <= minH);
	*/
	std::cout << "isoutofgame ? " << (mNode->isOutOfGame(pWindow) ? "true" : "false") << std::endl;
	return mNode->isOutOfGame(pWindow);
}