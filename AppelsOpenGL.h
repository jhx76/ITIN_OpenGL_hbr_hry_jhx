#ifndef APPELSOPENGL_H
#define APPELSOPENGL_H

#include "CommonDefines.h"
#include <string>
#include <glm/glm.hpp>

// ce fichier contient des fonctions statiques,
// appelables de n'importe ou,
// avec vos appels opengl.
//
// Par exemple : dans la classe Tir, vous pouvez appelez dans Tir::draw() la fonction dessinerTir ci-dessous.
class AppelsOpenGL
{
public:

	/// fonction d'aide si vous souhaitez connaitre
	/// la matrice modelview courante.
	static glm::mat4 obtenirLaMatriceModelViewCourante();

	/// fonction d'aide si vous souhaitez connaitre
	/// la matrice de projection courante.
	static glm::mat4 obtenirLaMatriceProjectionCourante();

	//-------------------------EXERCICES-CI DESSOUS---------------------------------//

	/// EXO OpenGL 1
	/// dessine une pyramide a l'endroit courant
	/// il faut donc que la matrice modelview courante soit correctement placee
	/// avant de faire cet appel.
	static void dessinerPyramide();

	/// EXO OpenGL 2
	/// fait le dessin d'un tir a l'endroit courant
	/// il faut donc que la matrice modelview courante soit correctement placee
	/// avant de faire cet appel.
	///
	/// utiliser des lignes successives, multicolores.
	/// vous pouvez utiliser une boucle for et des cos/sinus pour rendre ceci plus joli.
	/// en entree: si vous voulez vous pouvez passer des parametres supplementaires
	/// pour faire un dessin plus joli (ex: utiliser la position comme parametre de la couleur etc..)
	/// mais vous n'etes pas oblige de les utiliser.
	static void dessinerTir(glm::vec4 parametresQuelconques);


	/// EXO OpenGL 3
	/// dessine un triangle dont l'un des sommets est a l'infini a l'endroit courant
	/// il faut donc que la matrice modelview courante soit correctement placee
	/// avant de faire cet appel.
	static void dessinerTriangleInfini();

	/// EXO OpenGL 4
	/// pNameFile : nom de la texture png a charger.
	/// appelle une message box (MBOX("mon message"), dispo dans CommonDefines) si jamais 
	/// la texture n'est pas trouvee, et renvoie 0 dans ce cas.
	static GLuint loadTexture(std::string pNameFile);

	/// EXO OpenGL 5
	/// dessine un fond 2d (a l'aide de glOrtho)
	///
	///    coin1-----------coin2
	///		|				|
	///		|	A----->A	|
	///		|				|
	///	   coin4-----------coin3
	///
	/// En faisant glisser les coordonnees de textures selon x,
	/// faites en sorte de donner le sentiment d'un fond defilant à l'infini.
	/// en parametre : le decalage total du background. 
	/// ex: 0.3 => toutes les texcoords sont decallees de 0.3 selon x.
	///
	/// OPTIONNEL : dessiner plusieurs background en semi transparence qui 
	/// glissent a des vitesses differentes.
	///
	/// OPTIONNEL : desactiver l'ecriture dans le zbuffer.
	/// OPTIONNEL : desactiver le test de zbuffer lors du dessin (bref le pixel n'est jamais rejete par le test).
	static void drawBackground(float decallageTotal, GLuint idTexture);

	/// EXO OpenGL 6
	/// 5.1 utiliser un array de vertex pour dessiner l'element issu de UnModele3D.h
	/// 5.2 utiliser aussi du blending/melange pour le dessin de l'ennemi.
	/// remarque : vous pouvez ajouter les parametres supplementaires que vous voulez,
	///   cependant il n'y a besoin de rien de plus pour repondre correctement.
	static void dessinerEnnemi();
};


#endif