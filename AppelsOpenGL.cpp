#include "AppelsOpenGL.h"
#include <glm/gtc/matrix_transform.hpp>
#include "UnModele3D.h"

//-------------------------------------------------------------------//
glm::mat4 AppelsOpenGL::obtenirLaMatriceModelViewCourante()
{
	/// la fonction glGetXXX (XXX etant Floatv/Integerv/Booleanv) permet de recuperer des informations
	/// grace a un pointeur vers une zone deja allouee (ici lResult et lCurrentMatrixMode).
	/// la constante decrit le type d'information que l'on demande a OpenGL.

	// la doc complete de cette fonction : http://www.opengl.org/sdk/docs/man/xhtml/glGet.xml

	int lCurrentMatrixMode = 0;
	glGetIntegerv(GL_MATRIX_MODE, &lCurrentMatrixMode);

	glMatrixMode( GL_MODELVIEW );

	// la documentation du glGetFloatv de GL_MODELVIEW_MATRIX indique qu'il prend le top de la pile.
	// comme je ne suis pas sûr que la pile contient au moins 1 element,
	// je l'ajoute pour la requete, puis je l'enleve.
	glPushMatrix();
	
	glm::mat4 lResult;
	glGetFloatv(GL_MODELVIEW_MATRIX, &lResult[0][0]);
	
	glPopMatrix();

	// je reviens a mon mode de depart.
	glMatrixMode( lCurrentMatrixMode );

	return lResult;
}
//-------------------------------------------------------------------//
glm::mat4 AppelsOpenGL::obtenirLaMatriceProjectionCourante()
{
	/// la fonction glGetXXX (XXX etant Floatv/Integerv/Booleanv) permet de recuperer des informations
	/// grace a un pointeur vers une zone deja allouee (ici lResult et lCurrentMatrixMode).
	/// la constante decrit le type d'information que l'on demande a OpenGL.

	// la doc complete de cette fonction : http://www.opengl.org/sdk/docs/man/xhtml/glGet.xml

	int lCurrentMatrixMode = 0;
	glGetIntegerv(GL_MATRIX_MODE, &lCurrentMatrixMode);

	glMatrixMode( GL_PROJECTION );

	// la documentation du glGetFloatv de GL_PROJECTION_MATRIX indique qu'il prend le dessus sur la pile.
	// comme je ne suis pas sûr que la pile contient au moins 1 element,
	// je l'ajoute pour la requete, puis je l'enleve.
	glPushMatrix();
	
	glm::mat4 lResult;
	glGetFloatv(GL_PROJECTION_MATRIX, &lResult[0][0]);
	
	glPopMatrix(); // revient a la normale

	// je reviens a mon mode de depart.
	glMatrixMode( lCurrentMatrixMode );

	return lResult;
}

//-------------------------------------------------------------------//

// rappel : n'oubliez pas le "AppelsOpenGL::" dans le nom de vos fonctions,
// sinon vous aurez des erreurs de linker (LNK...).
void AppelsOpenGL::dessinerPyramide()
{
	//TODO
	glBegin(GL_TRIANGLES);
		glColor3f(1.0,0,0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(0.0,1.0,0.0);
		glVertex3d(1.0,1.0,0.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(1.0,1.0,0.0);
		glVertex3d(0.0,1.0,0.0);
	glEnd();
}

//------------------------------------------------------------------//
void AppelsOpenGL::dessinerTir(glm::vec4 parametresQuelconques)
{
	//TODO
	/*
	glBegin(GL_QUADS);
		glColor3ub(255,255,255);
		glVertex2d(-0.10f,0.10f);//A
		glVertex2d(0.10f,-0.10f);//D
		glVertex2d(0.10f,0.10f);//C
		glVertex2d(-0.10f,0.10f);//A
		glVertex2d(-0.10f,0.10f);//B		
    glEnd();*/
	glBegin(GL_LINES);
		glColor3ub(255,255,255);
		glVertex2d(1.0f, 0);
		glVertex2d(0, 0);
		

	glEnd();
}
//------------------------------------------------------------------//
void AppelsOpenGL::dessinerTriangleInfini()
{
	//TODO
	
}
//------------------------------------------------------------------//
void AppelsOpenGL::drawBackground(float decallageTotal, GLuint idTexture)
{
	//TODO
}

//------------------------------------------------------------------//
GLuint AppelsOpenGL::loadTexture(std::string pNameFile)
{
	//TODO

	// 1. lire l'image avec SFML.
	// 2. creer la texture avec les bons parametres
	// 3. renvoie l'identifiant de la texture cree.

	MBOX("pas de chargement implemente pour "<<pNameFile);
	return 0;
}

//------------------------------------------------------------------//
void AppelsOpenGL::dessinerEnnemi()
{
	//TODO
}
//------------------------------------------------------------------//
