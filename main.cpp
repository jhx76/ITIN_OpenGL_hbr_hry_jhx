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
//#pragma comment(lib, "glew32.lib") // recherche automatique de glew32.lib


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

//Surcharge pour pouvoir passer en argument les Element3D (et classes qui en héritent)
static bool isContact (Element3D& pElem1, Element3D& pElem2, float threshold)
{
	isContact(*(pElem1.mNode), *(pElem2.mNode), threshold);
}

static float RandomFloat(float min, float max)
{
    assert(max > min); 
    float random = ((float) rand()) / (float) RAND_MAX;

    // generate() a float between 0 and (4.5-.78)
    // then add .78, giving you a float between .78 and 4.5
    float range = max - min;  
    return (random*range) + min;
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
	float lLastEnnemyCreation	=	0;
	float lTotalTime_s			=	lClock.GetElapsedTime();
	float lTimeSinceLastFrame_s =	App.GetFrameTime();
	float speedModificator		=	1;
	// Start game loop
	while (App.IsOpened())
	{
		lTotalTime_s			=	lClock.GetElapsedTime();
		lTimeSinceLastFrame_s	=	App.GetFrameTime();
		lTimeSinceLastFrame_s	=	lTimeSinceLastFrame_s * speedModificator;
		// Process events
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed) {
				App.Close();
			}

			// Escape key : exit
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
			{
				App.Close();
			}

			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Add))
			{
				speedModificator	+=	0.1f;
				std::cout<<"Increasing game speed..."<<std::endl;
				std::cout<<"Game is now speed: "<<speedModificator<<std::endl;
			}

			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Subtract))
			{
				speedModificator	-=	0.1;
				std::cout<<"Decreasing game speed..."<<std::endl;
				std::cout<<"Game is now speed: "<<speedModificator<<std::endl;
			}

			// Retaillage de la fenetre
			if (Event.Type == sf::Event::Resized)
			{
				// on retaille la zone de dessin
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
			}

			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space))
			{
				// TODO : ajouter un tir.
				std::cout<<"Nouveau tir"<<std::endl;
				Tir* tmpTir = new Tir();
				tmpTir->mNode->mPosition_ParentSpace.x = lPlayer->mNode->mPosition_ParentSpace.x;
				tmpTir->mNode->mPosition_ParentSpace.y = lPlayer->mNode->mPosition_ParentSpace.y;
				tmpTir->mNode->mPosition_ParentSpace.z = lPlayer->mNode->mPosition_ParentSpace.z;
				ListMissile->push_back(tmpTir);
			}
		}

		// si j'appuie sur la touche haut
		if( App.GetInput().IsKeyDown( sf::Key::Up ) ) {
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
			tmpTir->mNode->mPosition_ParentSpace.x = lPlayer->mNode->mPosition_ParentSpace.x;
			tmpTir->mNode->mPosition_ParentSpace.y = lPlayer->mNode->mPosition_ParentSpace.y;
			tmpTir->mNode->mPosition_ParentSpace.z = lPlayer->mNode->mPosition_ParentSpace.z;
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
		if(lLastEnnemyCreation+1 < lTotalTime_s)
		{
			
			lLastEnnemyCreation	= lTotalTime_s;
			BadGuy* badGuy		= new BadGuy(100);
			badGuy->mNode->mPosition_ParentSpace.y = RandomFloat(0, App.GetWidth() );
			badGuy->mNode->mPosition_ParentSpace.x = App.GetWidth() - 1.0f;
			std::cout<<"INCOMING BadGuy!! ( " <<badGuy->mNode->mPosition_ParentSpace.x<<"; "<<badGuy->mNode->mPosition_ParentSpace.y<<")"<<std::endl;
			ListBadGuy->push_back(badGuy);
		}

		//MAJ position tirs
		for(auto lTir = ListMissile->begin(); lTir != ListMissile->end(); )
		{
			(*lTir)->update( App.GetFrameTime() );
			if((*lTir)->isOutOfGame(App))
			{
				std::cout<<"Suppression d'un tir car hors de l'écran"<<std::endl;
				Tir* ptrTir = *lTir;
				lTir = ListMissile->erase(lTir); //appel du destructeur de l'objet enlevé de la liste ???
												// Si c'est pas le cas, possible fuite mémoire !	
				if(ptrTir)
					delete ptrTir;
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
			{
				BadGuy* ptrBadGuy = *lBadGuy;
				lBadGuy = ListBadGuy->erase(lBadGuy);
				if(ptrBadGuy) 
					delete ptrBadGuy;
			}
			else
				++lBadGuy;
		}

		// -- TODO TEST collisions
		/*for(auto lTir = ListMissile->begin(); lTir != ListMissile->end(); ) {
			bool collision = false;
			Node3D* nodeTir = (*lTir)->mNode;
			for(auto lBadGuy = ListBadGuy->begin(); lBadGuy != ListBadGuy->end(); ) {
				Node3D* nodeBadGuy = (*lBadGuy)->mNode;
				
				
				
				//Test de collision: Tir / BadGuy
				//Les deux objets se sont rencontrés, reste maintenant a supprimer le tir et enlever les pv
				// + test des pv apres avoir décrémenté
				if(isContact(*nodeTir, *nodeBadGuy, 50)) {
					collision = true; //Permet de ne pas incrementer l'iterateur de ListTir car l'objet a été supprimé 
							          //et l'itérateur déja décalé avec l'appel de erase()
					lTir = ListMissile->erase(lTir); //appel du destructeur de l'objet enlevé de la liste ???
													 // Si c'est pas le cas, possible fuite mémoire !	
					(*lBadGuy)->mLife -= 1; // lors de la collision, on decrement la vie du bad guy !
					if( !(*lBadGuy)->isAlive() ) {
						lBadGuy = ListBadGuy->erase(lBadGuy); //meme interrogation sur la gestion memoire du bad guy a supprimer!
						break; //On sort du parcours de ListBadGuy
					}
				}

				lBadGuy++;
			}
			if(!collision) //S'il n'y a pas eu de collision, test un autre tir
				lTir++;
		}*/

		for (auto lBadGuy = ListBadGuy->begin(); lBadGuy != ListBadGuy->end(); ) {
			
			Node3D* nodeBadGuy = (*lBadGuy)->mNode;
			//Test de collison : Player / BadGuy
			if(isContact(*nodeBadGuy, *(lPlayer->mNode), 50)) {
				BadGuy* ptrBadGuy = *lBadGuy;
				lBadGuy = ListBadGuy->erase(lBadGuy);
				if(ptrBadGuy)
					delete ptrBadGuy;
				continue;
			}

			//Test de collison : Tir / BadGuy
			bool badGuyIsDead = false;
			for(auto lTir = ListMissile->begin(); lTir != ListMissile->end(); ) {
				Node3D* nodeTir = (*lTir)->mNode;
				if(isContact(*nodeTir, *nodeBadGuy, 0.5f)) {
					
					Tir* ptrTir = *lTir;
					lTir = ListMissile->erase(lTir); //appel du destructeur de l'objet enlevé de la liste ???
													 // Si c'est pas le cas, possible fuite mémoire !
					if(ptrTir)
						delete ptrTir;
					(*lBadGuy)->mLife -= 1; // lors de la collision, on decrement la vie du bad guy !
					if( !(*lBadGuy)->isAlive() ) {
						BadGuy* ptrBadGuy = *lBadGuy;
						lBadGuy = ListBadGuy->erase(lBadGuy);
						if(ptrBadGuy)
							delete ptrBadGuy;
						badGuyIsDead = true; //Permet de ne pas incrementer l'iterateur de ListTir car l'objet a été supprimé 
							          //et l'itérateur déja décalé avec l'appel de erase()
						break; //On sort du parcours de ListMissile
					}
				}
				lTir++;
			}
			if(!badGuyIsDead) //Si on a deja supprimé le badGuy de la liste, pas besoin de décalé l'itérateur
				lBadGuy++;    // car l'itérateur a deja été réaffecté par "lBadGuy = ListBadGuy->erase(lBadGuy);"
		}


		//--------------------dessin opengl------------------------------//

		// nettoyer le framebuffer et le zbuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// creons un point de vue.
		glMatrixMode(GL_MODELVIEW);
		glm::mat4 lPointOfView;
		lPointOfView = glm::translate( lPointOfView, glm::vec3(0,0,-11 ) );
		glLoadMatrixf( &lPointOfView[0][0] );
		
		// TODO dessin du fond.
		//GERER LES ARGUMENTS !!!!
//		AppelsOpenGL::drawBackground();
		
		// dessinons notre objet.
		lPlayer->draw();
		
		// TODO dessiner les tirs
		for(auto lTir = ListMissile->begin(); lTir != ListMissile->end(); )
		{
			(*lTir)->draw(); // dessin de l'element
			lTir++; //décalage de l'itérateur
		}
		
		// TODO dessiner les ennemis
		for(auto lBadGuy = ListBadGuy->begin(); lBadGuy != ListBadGuy->end(); )
		{
			(*lBadGuy)->draw(); //dessin de l'element
			lBadGuy++; //décallage de l'itérateur
		}
		
		
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

	delete lPlayer;
	std::cout<<"Temps de jeu: "<<lTotalTime_s<<std::endl;
	return EXIT_SUCCESS;
}
