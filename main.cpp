#include "CommonDefines.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Tir.h"
#include "BadGuy.h"
#include "Node3D.h"
#include "Element3D.h"
#include "AppelsOpenGL.h"

// si vous avez des problemes de linker avec glewinit :
// error LNK2019: symbole externe non résolu __imp__glewInit référencé dans la fonction _main
// alors commentez/décommentez cette ligne.
#pragma comment(lib, "glew32.lib") // recherche automatique de glew32.lib


// Indique si la distance entre pElem1 et pElem2 est inferieur à theshold
static bool isContact (Node3D& pElem1, Node3D& pElem2, float threshold)
{
	double distY = pElem1.mPosition_ParentSpace.y - pElem2.mPosition_ParentSpace.y;
	double distX = pElem1.mPosition_ParentSpace.x - pElem2.mPosition_ParentSpace.x;
    distY = distY * distY;
	distX = distX * distX;

	double distXY = distX + distY;

	return (distXY < (threshold * threshold));

}


int main()
{	
	// Create the main window
	std::string lTitre("SFML OpenGL");
	sf::Window App(sf::VideoMode(800, 600, 32), lTitre);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		MBOX("erreur lors init glew");
		return 1;
	}

	// etat opengl de depart
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(TRUE);
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFFFFFFFF);
	glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClearColor(1.0, 0.0, 1.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DITHER);

	glClearColor(1.0, 0.0, 1.0, 0.0);
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);

	// choisir la matrice projection.
	glMatrixMode(GL_PROJECTION);

	// construit une matrice de projection
	glm::mat4 lProjMatrix = 
		glm::perspective(45.f, // angle en degree FOV
		800.0f/600.0f, // ratio de la zone de dessin
		1.f,			// nearclip de la camera
		500.f);			// far clip de la camera

	//charge la matrice dans opengl
	glLoadMatrixf(&lProjMatrix[0][0]);

	// TODO charger la texture de background en memoire.
	// GLuint textureBg = AppelsOpenGL::loadTexture( "../../data/bg.bmp");

	// creation de mes elements de la scene.
	Element3D *lPlayer = new Element3D();
	lPlayer->mNode->mPosition_ParentSpace.x = -6.0f;

	//Creation du conteneur pour les elements Tir
	std::vector<Tir*> *ListMissile = new std::vector<Tir*>();

	//Creation du conteneur pour les elements BadGuy
	std::vector<BadGuy*> *ListBadGuy = new std::vector<BadGuy*>();

	// pour connaitre le temps total
	sf::Clock lClock;

	// Start game loop
	while (App.IsOpened())
	{
		float lTotalTime_s = lClock.GetElapsedTime();
		float lTimeSinceLastFrame_s = App.GetFrameTime();
		// Process events
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
			{
				App.Close();
			}

			// Escape key : exit
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
			{
				App.Close();
			}

			// Retaillage de la fenetre
			if (Event.Type == sf::Event::Resized)
			{
				// on retaille la zone de dessin
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
			}

			/*
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space))
			{
				// TODO : ajouter un tir.
				Tir* tmpTir = new Tir();
				ListMissile.push_back(tmpTir);
				//ListMissile.push_back(&Tir());
			}
			*/
		}

		// si j'appuie sur la touche haut
		if( App.GetInput().IsKeyDown( sf::Key::Up ) )
		{
			lPlayer->mNode->mPosition_ParentSpace.y += 1.8f * lTimeSinceLastFrame_s;
		}

		// si j'appuie sur la touche bas
		if( App.GetInput().IsKeyDown( sf::Key::Down ) )
		{
			lPlayer->mNode->mPosition_ParentSpace.y -= 1.8f * lTimeSinceLastFrame_s;
		}
		// si j'appuie sur la touche espace
		if( App.GetInput().IsKeyDown( sf::Key::Space ) )
		{
			Tir* tmpTir = new Tir();
			ListMissile->push_back(tmpTir);
		}

		// Set the active window before using OpenGL commands
		// It's useless here because active window is always the same,
		// but don't forget it if you use multiple windows or controls
		App.SetActive();

		//---------------------------------------------------------------//
		//-------------- mettre a jour la logique du jeu. ---------------//

		lPlayer->update(lTimeSinceLastFrame_s);

		// TODO : chaque seconde on cree un nouvel ennemi



		//MAJ position tirs
		for(auto lTir = ListMissile->begin(); lTir != ListMissile->end(); )
		{
			(*lTir)->update( App.GetFrameTime() );
			if((*lTir)->isOutOfGame(App))
			{
				lTir = ListMissile->erase(lTir); //appel du destructeur de l'objet enlevé de la liste ???
			}
			else
			{
				++lTir;
			}
		}

		//-- TODO MAJ position ennemis
		for(auto lBadGuy = ListBadGuy->begin(); lBadGuy != ListBadGuy->end(); )
		{
			(*lBadGuy)->update(App.GetFrameTime());
			if( (*lBadGuy)->isOutOfGame(App) )
				lBadGuy = ListBadGuy->erase(lBadGuy);
			else
				++lBadGuy;
		}

		// -- TODO TEST collisions

		//--------------------dessin opengl------------------------------//

		// nettoyer le framebuffer et le zbuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// creons un point de vue.
		glMatrixMode(GL_MODELVIEW);
		glm::mat4 lPointOfView;
		lPointOfView = glm::translate( lPointOfView, glm::vec3(0,0,-11 ) );
		glLoadMatrixf( &lPointOfView[0][0] );
		
		// TODO dessin du fond.
		
		
		// dessinons notre objet.
		lPlayer->draw();
		
		// TODO dessiner les tirs
		for(auto lTir = ListMissile->begin(); lTir != ListMissile->end(); )
		{
			(*lTir)->draw();
		}
		
		// TODO dessiner les ennemis
		for(auto lBadGuy = ListBadGuy->begin(); lBadGuy != ListBadGuy->end(); )
			(*lBadGuy)->draw();
		
		
		// attend que la carte graphique ait termine.
		glFlush();
		Sleep(10); // pour eviter de surcharger le processeur.
		App.Display();
	}



	// TODO nettoyer la memoire.
	//nettoie et supprime le conteneur pour les elements Tir
	while(ListMissile->size() > 0) {
		ListMissile->pop_back(); //pop_back() appelle aussi le destructeur de l'element a supprimer !
	}
	delete ListMissile;

	//nettoie et supprime le conteneur pour les elements BadGuy
	while(ListBadGuy->size() > 0) {
		ListBadGuy->pop_back();
	}
	delete ListBadGuy;



	return EXIT_SUCCESS;
}
