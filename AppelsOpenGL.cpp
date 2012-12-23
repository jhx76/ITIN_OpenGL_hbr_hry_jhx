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
		glColor3ub(255,0,0);
		glVertex2d(1.0f, 0);
		glColor3ub(0,0,255);
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
	auto lBeginMatrix = AppelsOpenGL::obtenirLaMatriceModelViewCourante();
		
	//TODO
	 glOrtho(-1, 1, -1, 1, -1, 1);//Créer une matrice de vue Ortho
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 glDisable(GL_DEPTH_TEST);
	 
	//Enable texturing on all models for now on.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexture);

	glBegin(GL_QUADS);
		glColor4ub(255, 255, 255, 255);
		//Draw our four points, clockwise.
		glTexCoord2f(0, 0); glVertex3f(-0.5, 0.5, 0); //A (-1,1)
		glTexCoord2f(1, 0); glVertex3f(0.5, 0.5, 0);  //B (1,1)
		glTexCoord2f(1, 1); glVertex3f(0.5, -0.5, 0); //C (1, -1)
		glTexCoord2f(0, 1); glVertex3f(-0.5, -0.5, 0); //D (-1, -1)
	glEnd();
	glLoadMatrixf( &lBeginMatrix[0][0]);
	glDisable(GL_TEXTURE_2D);
}

//------------------------------------------------------------------//
GLuint AppelsOpenGL::loadTexture(std::string pNameFile)
{
	//TODO

	// 1. lire l'image avec SFML.
	// 2. creer la texture avec les bons parametres
	// 3. renvoie l'identifiant de la texture cree.


	/*
	if(fileExists(pNameFile))
		return loadTexture("ma_texture.jpg");
	MBOX("file not found: "<<pNameFile);
	return 0;
	*/
	GLuint texture;

	sf::Image img;
	if(!img.LoadFromFile(pNameFile)) {
		MBOX("pas de chargement implemente pour "<<pNameFile);
		return 0;
	}	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.GetPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return texture;
}

//------------------------------------------------------------------//
void AppelsOpenGL::dessinerEnnemi()
{
	//TODO
}
//------------------------------------------------------------------//
bool AppelsOpenGL::fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

