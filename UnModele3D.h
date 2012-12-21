#ifndef UNMODELE3D_H
#define UNMODELE3D_H

#include "CommonDefines.h"

// il s'agit d'un modele 3D exporte depuis 3DSMAX.
// Ses tableaux de sommets, indices et couleurs sont stockes directement en C/C++.
// D'habitude on lit un fichier (xml/obj/mesh/fbx...) pour effectuer cette operation.
//
// Pour information : j'ai utilise l'exporteur OgreMax en cochant l'export vers xml dedans.
// Ensuite, j'ai utilise un editeur de texte avec quelques macro pour extraire la liste des valeurs.
// Enfin, j'ai copie/colle le resultat dans les tableaux ci dessous.
// Pour ne pas surcharger le code du devoir (et avoir un chargement plus rapide), je n'ai pas fait la lecture du xml.
class UnModele3D
{
public:
	static GLuint faces[];	// liste de triangles. 316 triplets.
	static GLdouble sommets[];  // x,y,z, x2,y2,z2, ...  324 triplets.
	static GLdouble couleurs[]; // 4 composantes.  324 quadruplets.
};

#endif