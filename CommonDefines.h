#ifndef MBOX_H
#define MBOX_H

#include "GL/glew.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics/Image.hpp>

typedef std::string String;

// ceci est une macro qui affiche une boite de dialogue
// exemple : MBOX("j'ai " << 22 * 364.25<< " jours.");
//			 // affiche : "j'ai 8013.5 jours."
#define MBOX(X) {				\
	std::stringstream mbox_ss;	\
	mbox_ss<<X<<std::endl;		\
	MessageBox(NULL,mbox_ss.str().c_str(), "", MB_OK);}


#endif

