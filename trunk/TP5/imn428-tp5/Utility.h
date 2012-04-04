#ifndef UTILITY_H
#define UTILITY_H

typedef struct
{
	double X;
	double Y;
	double Z;
} Position;

typedef struct 
{
	int button;
	int buttonState;
	int x;
	int y;
} MouseEvent;

typedef struct
{
	GLenum	lightID;		//GL_LIGHT0, GL_LIGHT1, etc.
	GLfloat	ambient[4]; 	//Couleur pour la composante ambiante
	GLfloat	diffuse[4];		//Couleur pour la composante diffuse
	GLfloat	specular[4];	//Couleur pour la composante speculaire
	GLfloat	position[4];	//Position

	GLfloat Kc;	//Facteur d'attenuation constante
	GLfloat Kl;	//Facteur d'attenuation linaire
	GLfloat Kq;	//Facteur d'attenuation quadratique

	bool	on; // allumée ou fermée

} Light;

#endif // UTILITY_H
